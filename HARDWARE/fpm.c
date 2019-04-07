//#include "stc15f2k60s2.h"
//#include <intrins.h>  
////6指纹模块6脚 GND  3-VCC  5接TXD   4接RXD   通信波特率57600
//#define TRUE 1

//unsigned char 	SaveNumber=0,searchnum=0;
//unsigned int  	SearchNumber=0;		

//unsigned int 	clk0=0;

//sbit relay =P2^4; //继电器引脚
//sbit buzzer=P2^5; //蜂鸣器引脚
//sbit red=   P2^1;//录入模式指示灯 在板子靠近单片机处
//sbit green= P2^0;//识别模式指示灯 在板子远离单片机处


//sbit k1=P3^3; //模式识别
//sbit k2=P3^4; //录入一次指纹
//sbit k3=P3^2; //清除所有指纹（10个指纹清除）

////变量定义:
//unsigned char code tab[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//表：共阳数码管 0-9 
//					
////数码管引脚定义:
//sbit SMG_g = P1^3;	//定义数码管阳级控制脚（个位）
////由于程序中定时器被用 我们用一位数码管显示 且为静太显示 所以推荐大家用1602或者12864液晶 


//bit changeflag=0,modeflag=0,clearallflag=0;  //默认为识别模式，如果为1为录入指纹模式,每录入一次SaveNumber++


////////////////////////////////////////常用指令定义/////////////////////////////

////Verify  Password   ：验证设备握手口令
//unsigned char code VPWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};	 //回送12个

////设置设备握手口令
//unsigned char code STWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x12,0x00,0x00,0x00,0x00,0x00,0x1a};	 //回送12个

////GetImage           ：探测手指并从传感器上读入图像
//unsigned char code GIMG[14]={12, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,1,0x00,0x05};	//回送12个

////Gen Templet1        ：根据原始图像生成指纹特征1
//unsigned char code GENT1[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,1,0x00,0x08};	//回送12个

////Gen Templet2        ：根据原始图像生成指纹特征2
//unsigned char code GENT2[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,2,0x00,0x09}; //回送12个	

//	
////Search Finger      ：以CharBufferA或CharBufferB中的特征文件搜索整个或部分指纹库
//unsigned char code SEAT[18]={17,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,   0,8, 4,1,0,0,    0,0x65,  0x00,0x73};	//回送16个


////Merge Templet      ;将CharBufferA与CharBufferB中的特征文件合并生成模板，结果存于ModelBuffer。
//unsigned char code MERG[14]={12,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,3,5 , 0x00,0x09};//回送12个	

////Store Templet      ：将ModelBuffer中的文件储存到flash指纹库中
//unsigned char code STOR[16]={15,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,6,6,2,     0x00,0x00,     0x00,0x0f}; //回送12个

////Read Note
//unsigned char code RDNT[14]={13,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,4,0x19,  0, 0x00,0x1e};

////Clear Note
//unsigned char code DENT[46]={45,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,36,0x18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x00,0x3d};

////DEL one templet
//unsigned char code DELE_one[16]={16, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,7,  0x0c,0x00,0x00, 0,1, 0x00,0x15};

////DEL templet      ;清空指纹库
//unsigned char code DELE_all[12]={12,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,  0x0d,0x00,0x11};


//////////////////常用指令定义-------结束///////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////宏定义////////////////////////////////////////////////////////////////////////
//#define FALSE 0
//#define TURE  1

////状态定义表
//#define on    	1
//#define off   	0

//#define MAX_NUMBER    63 
//#define _Nop()  _nop_()


////////////////////////////////////////宏定义------------结束////////////////////////////////////////////////////////

//unsigned char 		 FifoNumber=0; 
//unsigned char    FIFO[MAX_NUMBER+1]={0};

///*********1毫秒延时程序**********/
//void delay1ms(unsigned int t)
//{
//	unsigned int i,j;
//	for(i=0;i<t;i++)
//	   for(j=0;j<120;j++)
//	   ;
//}


//void TxdByte(unsigned char dat)//串口发送信息,通过查询方式发送一个字符
//{
//    TI = 0;		 //让TI＝0
//    SBUF = dat;	 //读入数据
//    while(!TI);	 //等待发送完毕
//    TI = 0;		 //清零
//}

//bit Command(unsigned char *p,unsigned char MaxTime) //命令解析,给模块发送一个命令
//{
//  	unsigned char count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;
//  		
//	bit result=0, start=0,stop=0;

//  	TxdByte(0xef);//数据包包头识别码
//   	TxdByte(0x01);//数据包包头识别码
//  	i=*p;         //数组的第“0”个元素、里面存放了本数组的长度，把这个长度给变量i，方便进行操作
//  	p++;
//	  p++;
//  	for (count=i-1; count!=1;count--)  //Sent command String
//    {
//	 		temp=*p++;    //取第个“1”个元素的内容，然后发送 
//	    	TxdByte(temp);//将数据发送出去
//	}  
//  	result=TURE;//发送完成,结果为真 (真为1)   	
//  	FifoNumber=0;
//  	for (count=MAX_NUMBER+1; count!=0; count--)//清空所有FIFO[]数组里面的内容，写入0X00
//		 FIFO[count-1]=0x00;  
//  	if (result)   
//   	{		
//     	result=FALSE;
//      	start =FALSE;
//   		stop  =FALSE;
//       	count=0;
//       	clk0=0;	//清零CL0计数
//		
//       	do /////////////////////////////do的内容////////////////////////////////
//		{	
//			restart0:				
//	         	if (RI==1)//如果接收到数据
//		      	{ 				
//			  		tmpdat=SBUF;//先把接收到的数据放到tmpdat中
//	            	RI=0;
//	            	if ((tmpdat==0xef)&&(start==FALSE))//这个数据为第一个传回来的数据，也就是“指令应答”的第一个字节
//		            	{ 
//							count=0;
//					    	FIFO[0]=tmpdat;//读入第一个应答字节(0XEF)，存在第“0”个元素中    
//							flag=1;	
//							goto 
//								restart0;//可以用中断方式进行			
//				        	
//		             	}
//					if(flag==1)//第一个字节已经回来，所以flag==1成立
//						{  
//							if(tmpdat!=0x01)  //接收数据错误，将重新从缓冲区接收数据
//							{  	
//								flag=0;//接收应答失败
//								result=FALSE;
//		      					start =FALSE;
//		   						stop=FALSE;
//		       					count=0;
//								goto 
//									restart0;					
//							
//							}
//							//如果成功接收到0xef01，可以开始接收数据
//							flag=2;//flag=2;表示应答成功，可以开始接收数据了
//							count++;//现在count=1;
//							FIFO[count]=tmpdat;//读入第二个应答字节（0X01），存在第“1”个元素中    
//							start=TURE;	//应答成功可以开始接收数据
//							    goto 
//									restart0;	
//						}                  
//	             	if((flag==2)&&(start==TURE))//flag=2;表示应答成功，可以开始接收数据了
//		             	{	   	  					 
//					   		count++; //数据元素下标＋＋
//				            FIFO[count]=tmpdat;//存入数据
//							if(count>=6)
//								{
//									checksum=FIFO[count]+checksum; //计算校验和
//								}
//							if(count==8)
//								{ 
//									package=FIFO[7]*0X100+FIFO[8];	//计算包长度							
//									stop= TURE;
//								}
//							if(stop)
//								{						
//									if(count==package+8)
//									{
//										checksum=checksum-FIFO[count-1] - FIFO[count];
//										if(checksum != (FIFO[count]&0xff)) 
//											result=FALSE; //校验失败,置结果标志为0							
//										else 
//											result=TURE;
//										flag=0;
//										break;
//									} 
//								}
//		             	}
//	 	       	}
//          }/////////////////////////////do的内容----------------结束////////////////////////////////
//		   
//		while ((clk0 <= MaxTime) && (count <= MAX_NUMBER) && (changeflag==0)); //由定时器以及最大接收数据来控制，保证不会在此一直循环
//		  
//        FifoNumber=count;	//保存接收到的数据个数
//	 }
//   return (result);
//}

//bit VefPSW(void)//验证设备握手口令,成功返回1     
//{
// 	unsigned char  count=0;
//	while (1)
//   	{
//     	if(Command(VPWD,20) && (FifoNumber==11) && (FIFO[9]==0x00))  
//			return(1);
//     	count++;
//   	  	if (count>=2)//如果不成功，再验证一次，如果两次不成功，返回失败
//	        {  
//	            return(0);   
//	 	    }
//	}
//}


//void Clear_All(void) //清空指纹库   
//{				
//      delay1ms(200);
//	  Command(DELE_all,50); //清空指纹库  		
//}

//unsigned char ImgProcess(unsigned char BUFID)  //发获取图像并生成特征文件，存入BUFID中//输入参数为缓冲区号  
//{	
//    if(Command(GIMG,89) && (FifoNumber==11) && (FIFO[9]==0x00))  
//    {
//		if(BUFID==1)      
//		{	   			
//      		if(Command(GENT1,60) && (FifoNumber==11) && (FIFO[9]==0x00))  
//        	{							
//				return 1;
//			}  
//        	else
//        	{
//  				return 0;
//         	}
//		 }
//		else if(BUFID==2)
//		{
//		  	if(Command(GENT2,60) && (FifoNumber==11) && (FIFO[9]==0x00))  
//        	{				
//				return 1;
//			}  
//        	else
//        	{
//  				return 0;
//         	}			
//		}
//    }
//    else
//    {
//      return 0;       
//    } 
//	return 0;            
//}

//bit Searchfinger(void)//搜索指纹(发送搜索命令、以及根据返回值确定是否存在)        
//{		
//   	if(Command(SEAT,60) && (FifoNumber==15) && (FIFO[9]==0x00) )  
//    {
//		SearchNumber=FIFO[10]*0x100+FIFO[11];//搜索到的页码
//		//MatchScore=FIFO[12]*0x100+FIFO[13]   可以在此计算得分，从而进行安全级别设定，本程序忽略
//	   	return 1;
//	}     
//    else             
//    {
//       	return 0;
//    }  
//}


//unsigned char search(void)//搜索指纹 
//{
// 	unsigned char SearchBuf=0,i=0;
//  	while (i<20)
//    {
//     	if (ImgProcess(1)==1)//首先读入一次指纹  
//       	{
//       		SearchBuf=Searchfinger();//进行指纹比对，如果搜索到，返回搜索到的指纹序号
//       		if(SearchBuf==1)
//       		{
//       			return SearchNumber; 
//       		}
//       		else 
//			{
//			   return 255;//表示搜索到的指纹不正确
//			}     
//       	}
//		i++;	
//    }
//   return 0;
//}

//bit savefingure(unsigned char ID)//保存指纹
//{
//	 unsigned char i=0;
//	 //现在开始进行存储指纹模板的操作
//     for (i=0;i<16;i++)	//保存指纹信息
//	 {
//		FIFO[i]=STOR[i];
//	}  

//     FIFO[12]=ID; //把指纹模板存放的PAGE_ID也就是FLASH的位置
//     FIFO[14]=FIFO[14]+ID;	//校验和

//     if (Command(FIFO,70)==1)//此处进行存放指纹模板的命令
//	 {
//	   return(1);
//	 }
//     else
//	 {
//	   return(0);//不成功返回0
//	 } 
//}



//unsigned char enroll(void) //采集两次指纹，生成1个 指纹模板
//{
// 	unsigned char temp=0,count=0;
//  	while(1)
//  	{
//  	 	temp=ImgProcess(1); //生成特征1    
//   		if (temp==1)//生成特征文件成功             
//      	{  		      
//        	//采集第一个特征成功 
//		   	count=0;  
//		  	buzzer=0;
//			delay1ms(100);
//			buzzer=1;
//			break;
//       	}
//     	else                   
//       	{
//        	if (temp==0)//采集指纹没有成功
//          	{ 
//				count++;
//            	if (count>=40)//如果采集了40次，还不成功，直接采集失败，直接退出enroll函数－－－－返回0  
//					return(0);
//            }
//        }
//   	}

//	delay1ms(2000);//延时2S开始采集下一个特征

//	//开始采集第二个特征 
// 	while(1)
//  	{
//   		temp=ImgProcess(2); //生成特征2    
//   		if (temp==1)//生成特征文件2成功
//      	{
//        	if (  (Command(MERG,40)&& (FifoNumber==11) && (FIFO[9]==0x00))==1  ) //合并成功返回1
//			{
//			     buzzer=0;
//	             delay1ms(1000);
//	             buzzer=1;
//				 delay1ms(1000);
//				 buzzer=0;
//	             delay1ms(1000);	//响两声，表示生成一个模板成功
//	             buzzer=1; 
//				 return(1);
//			}
//			else
//			{
//			   return(0);
//			}		
//        }
//      	else      
//       	{	
//        	if (temp==1)//采集指纹没有成功
//        	{
//				count++;
//				
//				if (count>=25) 
//				
//				return(0);
//       		}
//     	}
//   	}
//}


//void UartInit(void)		//57600bps@11.0592MHz
//{
////	PCON |= 0x80;		//使能波特率倍速位SMOD
////	SCON = 0x50;		//8位数据,可变波特率
////	TMOD = 0x21;		//设定定时器1为8位自动重装方式
////	  AUXR=0X40;		 //开启1T模式
////	TL1 = 0xFF;		//设定定时初值
////	TH1 = 0xFF;		//设定定时器重装值
////	ET1 = 0;		//禁止定时器1中断
////	TR1 = 1;		//启动定时器1

//        SCON=0x50;        //REN=1允许串行接受状态，串口工作模式2     	   
//	   TMOD= 0x00;       //定时器1为模式0（16位自动重载）                
//	   AUXR=0X40;		 //开启1T模式
//       TL1=(65535-(11059200/4/57600));    //设置波特率重装值
//	   TH1=(65535-(11059200/4/57600))>>8;

//                        // 如有不明白请查 STC15手册上有详细说明 	 619页
//      
//	   TR1  = 1;        //开启定时器1  
//	//   ES   = 1;        //开串口中断                                                                     
//	  // EA   = 1;        // 开总中断 



//}


//void main(void)//主函数
//{
//	unsigned char i=0;

//	 
//	UartInit();

//	ET0=1;     //定时器0开中断
//	TL0=0x97;  //17ms的初值
//	TH0=0xBD;
//    TR0=1;// 开定时器0
//	
//	IT0=0;//中断0低电平中断
//	IT1=1;//中断1低电平中断
//	EX0=1;//开中断0
//	EX1=1;//开中断1
//    EA=1;

//	SMG_g = 0x01;	 /////0
//	P1 = 0x01;	 /////0
//	P0 = ~tab[0];//显示0	////////加了~改为共阴

//	for(i=0;i<6;i++)//开始握手6次，如果没有一次成功，表示模块通信不正常。只要成功就跳出此循环
//	{
//		if(VefPSW()==1)//与模块握手通过，绿灯亮起。进入识别模式
//		 {
//				green=0;
//				buzzer=0;
//	            delay1ms(300);
//	            buzzer=1;
//				green=1;
//                red=0;
//				break; //成功就退出这个循环
//		}
//	}


//    while(1)
//	{	 //CLK_DIV=0x03;//设置分频03
//		if(k2==0)//录入一个指纹
//		{
//			  	delay1ms(10);	
//			  	if(k2==0)//如果仍为低电平，表示按键有效
//				  	{
//				  	  while(k2==0);//等待松手
//					  if(VefPSW()==1&&modeflag==1&&SaveNumber<10)//与模块握手通过
//						  {
//						  	  if(enroll()==1)//采集两次，生成1个指纹模板成功
//							  	{
//								   if(savefingure(SaveNumber+1)==1)//保存也成功
//								   	{
//										SaveNumber++;//加一次
//										P0=~tab[SaveNumber];	   ////////加了~改为共阴
//										delay1ms(200);
//										P0=0x00;//来一次显示，闪烁一次
//										delay1ms(200);
//										P0=~tab[SaveNumber];	   ////////加了~改为共阴
//									}
//			
//								}
//						  }
//						else
//						{
//								buzzer=0; 
//								for(i=0;i<8;i++)
//								{
//								  delay1ms(100);
//								  red=~red;
//								}
//								red=0;
//								buzzer=1;
//									
//						}  	
//				  	}
//					
//			}

//		if(modeflag==0)//为识别模式
//		{
//			  green=0;
//			  red=1;
//			  searchnum=search();
//			  if(searchnum>=1&&searchnum<=162)//只能存入162个指纹
//			  {
//			  	  	P0=~tab[searchnum];//显示搜索到的指纹模块	  ////////加了~改为共阴
//			       //蜂鸣器响一声 
//				    //继电器打开约3秒钟
//				   relay=0;
//			       buzzer=0;
//			       delay1ms(1000);
//			       buzzer=1;
//				   delay1ms(10000);
//				   relay=1;
//				   
//			  }
//			  if(searchnum==255)//不正确的指纹 蜂鸣器响三声
//			  {
//			  	   P0=~tab[0];//显示0			  ////////加了~改为共阴
//				   buzzer=0;delay1ms(100); buzzer=1;delay1ms(100);
//			       buzzer=0;delay1ms(100); buzzer=1;delay1ms(100);
//			       buzzer=0;delay1ms(100); buzzer=1;delay1ms(100); 
//			  }
//		}

//		if(modeflag==1)//录入模式
//		{
//		  green=1;
//		  red=0;
//		}

//		if(clearallflag==1)
//		{
//			clearallflag=0;
//			Clear_All();
//		    red=0;	     //红色灯亮
//		    green=1;
//			//蜂鸣器长响一次，表示清除所有指纹结束
//			modeflag=1;//进入录入指纹模式
//			P0=~tab[0];//表示没有指纹录入	  ////////加了~改为共阴
//			buzzer=0;
//			delay1ms(1200);
//			buzzer=1;
//			SaveNumber=0;
//		}

//		if(changeflag==1)
//		{
//		    changeflag=0;
//			if(modeflag==0) //识别模式
//			 {
//			 	green=0;
//				red=1;
//				P0=~tab[0];//显示当前有几个 指纹		 ////////加了~改为共阴		   
//			 }
//			 else		   //录入模式
//			 {
//			 	red=0;
//				green=1;
//				P0=~tab[0];//显示0	  ////////加了~改为共阴		   
//			 }
//		}
//	}////////////////////////////while(1)结束////////////////////////////////
//	
//}



//void  Timer0(void) interrupt 1//定时器0中断函数
//{
// 	TL0=0x97;
//	TH0=0xBD;
//	clk0++;   //延时17ms
//}

//void int0(void) interrupt 0//中断0，清除所有指纹
//{
//	if(k3==0) //清除所有指纹
//	{
//		delay1ms(10);
//		if(k3==0)//如果仍为低电平，表示按键有效
//		{
//			while(k3==0);//等待松手	
//			clearallflag=1;
//			changeflag=1;
//		}	
//	}	
//}


//void int1(void) interrupt 2//中断1，模式转换
//{
//	if(k1==0)//模式转换 其中用modeflag 来标志,默认从第1个指纹开始录入
//	{
//	  delay1ms(10);	
//	  if(k1==0)//如果仍为低电平，表示按键有效
//	  	{
//			 while(k1==0);//等待松手
//			 modeflag=~modeflag;//0表示录入指纹  1表示识别指纹
//			 changeflag=1;
//		}	
//	}	
//}