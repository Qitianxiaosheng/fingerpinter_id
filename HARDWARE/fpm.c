#include "fpm.h"

sbit WAK = P2^5;
unsigned char   idy_stop_flag=0;
unsigned char 	SaveNumber=0,searchnum=0;
unsigned int  	SearchNumber=0;		
bit changeflag=0,modeflag=0,clearallflag=0;  
//Verify  Password   ：验证设备握手口令
unsigned char  VPWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};	 //回送12个

//设置设备握手口令
unsigned char code STWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x12,0x00,0x00,0x00,0x00,0x00,0x1a};	 //回送12个

//GetImage           ：探测手指并从传感器上读入图像
unsigned char code GIMG[14]={12, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,1,0x00,0x05};	//回送12个

//Gen Templet1        ：根据原始图像生成指纹特征1
unsigned char code GENT1[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,1,0x00,0x08};	//回送12个

//Gen Templet2        ：根据原始图像生成指纹特征2
unsigned char code GENT2[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,2,0x00,0x09}; //回送12个	

	
//Search Finger      ：以CharBufferA或CharBufferB中的特征文件搜索整个或部分指纹库
unsigned char code SEAT[18]={17,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,   0,8, 4,1,0,0,    0,0x65,  0x00,0x73};	//回送16个


//Merge Templet      ;将CharBufferA与CharBufferB中的特征文件合并生成模板，结果存于ModelBuffer。
unsigned char code MERG[14]={12,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,3,5 , 0x00,0x09};//回送12个	

//Store Templet      ：将ModelBuffer中的文件储存到flash指纹库中
unsigned char code STOR[16]={15,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,6,6,2,     0x00,0x00,     0x00,0x0f}; //回送12个

//Read Note
unsigned char code RDNT[14]={13,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,4,0x19,  0, 0x00,0x1e};

//Clear Note
unsigned char code DENT[46]={45,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,36,0x18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x00,0x3d};

//DEL one templet
unsigned char code DELE_one[16]={16, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,7,  0x0c,0x00,0x00, 0,1, 0x00,0x15};

//DEL templet      ;清空指纹库
unsigned char code DELE_all[12]={12,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,  0x0d,0x00,0x11};


////////////////常用指令定义-------结束///////////////////////////////////////////////////////////////////////////////////////
unsigned char 		FifoNumber=0; 
unsigned char   FIFO[MAX_NUMBER+1]={0};
u8 WAK_Check(void)
{
	if(WAK)
		return 1;
	else
		return 0;
}
unsigned char send_command( unsigned char *p)
{
    unsigned char count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;
  	TxdByte(0xef);//数据包包头识别码
	  delay_us(100);
   	TxdByte(0x01);//数据包包头识别码
	  delay_us(100);
  	i=*p;         //数组的第“0”个元素、里面存放了本数组的长度，把这个长度给变量i，方便进行操作
  	p++;
	  p++;
  	for (count=i-1; count!=1;count--)  //Sent command String
    {
	 		temp=*p++;    //取第个“1”个元素的内容，然后发送 
	    TxdByte(temp);//将数据发送出去
			delay_us(100);
	  }  
  	return 1;//发送完成,结果为真 (真为1)   	
}
	
bit Command(unsigned char *p,unsigned char MaxTime) //命令解析,给模块发送一个命令
{
  	unsigned char count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;
  		
	 bit result=0, start=0,stop=0;
   send_command(p);
  	result=TURE;//发送完成,结果为真 (真为1)   	
  	FifoNumber=0;
  	for (count=MAX_NUMBER+1; count!=0; count--)//清空所有FIFO[]数组里面的内容，写入0X00
		 FIFO[count-1]=0x00;  
  	if (result)   
   	{		
     	result=FALSE;
      	start =FALSE;
   		stop  =FALSE;
       	count=0;
       	clk0=0;	//清零CL0计数
		
       	do /////////////////////////////do的内容////////////////////////////////
		{	
			restart0:				
	         	if ((S2CON &0x01)==1)//如果接收到数据
		      	{ 				
			  		tmpdat=S2BUF;//先把接收到的数据放到tmpdat中
	            	S2CON &= ~0x01;
	            	if ((tmpdat==0xef)&&(start==FALSE))//这个数据为第一个传回来的数据，也就是“指令应答”的第一个字节
		            	{ 
							count=0;
					    	FIFO[0]=tmpdat;//读入第一个应答字节(0XEF)，存在第“0”个元素中    
							flag=1;	
							goto 
								restart0;//可以用中断方式进行			
				        	
		             	}
					if(flag==1)//第一个字节已经回来，所以flag==1成立
						{  
							if(tmpdat!=0x01)  //接收数据错误，将重新从缓冲区接收数据
							{  	
								flag=0;//接收应答失败
								result=FALSE;
		      					start =FALSE;
		   						stop=FALSE;
		       					count=0;
								goto 
									restart0;					
							
							}
							//如果成功接收到0xef01，可以开始接收数据
							flag=2;//flag=2;表示应答成功，可以开始接收数据了
							count++;//现在count=1;
							FIFO[count]=tmpdat;//读入第二个应答字节（0X01），存在第“1”个元素中    
							start=TURE;	//应答成功可以开始接收数据
							    goto 
									restart0;	
						}                  
	             	if((flag==2)&&(start==TURE))//flag=2;表示应答成功，可以开始接收数据了
		             	{	   	  					 
					   		count++; //数据元素下标＋＋
				            FIFO[count]=tmpdat;//存入数据
							if(count>=6)
								{
									checksum=FIFO[count]+checksum; //计算校验和
								}
							if(count==8)
								{ 
									package=FIFO[7]*0X100+FIFO[8];	//计算包长度							
									stop= TURE;
								}
							if(stop)
								{						
									if(count==package+8)
									{
										checksum=checksum-FIFO[count-1] - FIFO[count];
										if(checksum != (FIFO[count]&0xff)) 
											result=FALSE; //校验失败,置结果标志为0							
										else 
											result=TURE;
										flag=0;
										break;
									} 
								}
		             	}
	 	       	}
          }/////////////////////////////do的内容----------------结束////////////////////////////////
		   
		while ((clk0 <= MaxTime) && (count <= MAX_NUMBER) && (changeflag==0)); //由定时器以及最大接收数据来控制，保证不会在此一直循环
		  
        FifoNumber=count;	//保存接收到的数据个数
	 }
   return (result);
}


bit VefPSW(void)//验证设备握手口令,成功返回1     
{
 	unsigned char  count=0;
	while (1)
   	{
     	if(Command(VPWD,20) && (FifoNumber==11) && (FIFO[9]==0x00))  
			return(1);
     	count++;
   	  	if (count>=2)//如果不成功，再验证一次，如果两次不成功，返回失败
	        {  
	            return(0);   
	 	    }
	}
}


void Clear_All(void) //清空指纹库   
{				
      delay_ms(200);
	  Command(DELE_all,50); //清空指纹库  		
}


unsigned char ImgProcess(unsigned char BUFID)  //发获取图像并生成特征文件，存入BUFID中//输入参数为缓冲区号  
{	
    if(Command(GIMG,89) && (FifoNumber==11) && (FIFO[9]==0x00))  
    {
		if(BUFID==1)      
		{	   			
      		if(Command(GENT1,60) && (FifoNumber==11) && (FIFO[9]==0x00))  
        	{							
				return 1;
			}  
        	else
        	{
  				return 0;
         	}
		 }
		else if(BUFID==2)
		{
		  	if(Command(GENT2,60) && (FifoNumber==11) && (FIFO[9]==0x00))  
        	{				
				return 1;
			}  
        	else
        	{
  				return 0;
         	}			
		}
    }
    else
    {
      return 0;       
    } 
	return 0;            
}

bit Searchfinger(void)//搜索指纹(发送搜索命令、以及根据返回值确定是否存在)        
{		
   	if(Command(SEAT,60) && (FifoNumber==15) && (FIFO[9]==0x00) )  
    {
		SearchNumber=FIFO[10]*0x100+FIFO[11];//搜索到的页码
		//MatchScore=FIFO[12]*0x100+FIFO[13]   可以在此计算得分，从而进行安全级别设定，本程序忽略
	   	return 1;
	}     
    else             
    {
       	return 0;
    }  
}


unsigned char search(void)//搜索指纹 
{
	
 	unsigned char SearchBuf=0,i=0;
  	while (i<20)
    {
     	if (ImgProcess(1)==1)//首先读入一次指纹  
       	{
       		SearchBuf=Searchfinger();//进行指纹比对，如果搜索到，返回搜索到的指纹序号
       		if(SearchBuf==1)
       			return SearchNumber; 
       		else 
						return 255;//表示搜索到的指纹不正确
	     
       	}
		   i++;	
				if(idy_stop_flag)
				{
					idy_stop_flag=0;
					 return 0;
				}
				
    }
   return 0;
}

bit savefingure(unsigned char ID)//保存指纹
{
	 unsigned char i=0;
	 //现在开始进行存储指纹模板的操作
     for (i=0;i<16;i++)	//保存指纹信息
	 {
		FIFO[i]=STOR[i];
	}  

     FIFO[12]=ID; //把指纹模板存放的PAGE_ID也就是FLASH的位置
     FIFO[14]=FIFO[14]+ID;	//校验和

     if (Command(FIFO,70)==1)//此处进行存放指纹模板的命令
	 {
	   return(1);
	 }
     else
	 {
	   return(0);//不成功返回0
	 } 
}



unsigned char enroll(void) //采集两次指纹，生成1个 指纹模板
{
 	unsigned char temp=0,count=0;
  	while(1)
  	{
  	 	temp=ImgProcess(1); //生成特征1    
   		if (temp==1)//生成特征文件成功             
      	{  		      
        	//采集第一个特征成功 
		   	count=0;  
		  	buzzer=0;
			delay_ms(100);
			buzzer=1;
			break;
       	}
     	else                   
       	{
        	if (temp==0)//采集指纹没有成功
          	{ 
				count++;
            	if (count>=40)//如果采集了40次，还不成功，直接采集失败，直接退出enroll函数－－－－返回0  
					return(0);
            }
        }
   	}

	delay_ms(2000);//延时2S开始采集下一个特征

	//开始采集第二个特征 
 	while(1)
  	{
   		temp=ImgProcess(2); //生成特征2    
   		if (temp==1)//生成特征文件2成功
      	{
        	if (  (Command(MERG,40)&& (FifoNumber==11) && (FIFO[9]==0x00))==1  ) //合并成功返回1
			{
			     buzzer=0;
	             delay_ms(1000);
	             buzzer=1;
				 delay_ms(1000);
				 buzzer=0;
	             delay_ms(1000);	//响两声，表示生成一个模板成功
	             buzzer=1; 
				 return(1);
			}
			else
			{
			   return(0);
			}		
        }
      	else      
       	{	
        	if (temp==1)//采集指纹没有成功
        	{
				    count++;
				    if (count>=25) 
				    return(0);
       		}
     	}
   	}
}



