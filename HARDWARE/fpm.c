#include "fpm.h"


unsigned char   idy_stop_flag=0;
unsigned char 	SaveNumber=0,searchnum=0;
unsigned int  	SearchNumber=0;		
bit changeflag=0,modeflag=0,clearallflag=0;  
//Verify  Password   ����֤�豸���ֿ���
unsigned char  VPWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};	 //����12��

//�����豸���ֿ���
unsigned char code STWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x12,0x00,0x00,0x00,0x00,0x00,0x1a};	 //����12��

//GetImage           ��̽����ָ���Ӵ������϶���ͼ��
unsigned char code GIMG[14]={12, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,1,0x00,0x05};	//����12��

//Gen Templet1        ������ԭʼͼ������ָ������1
unsigned char code GENT1[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,1,0x00,0x08};	//����12��

//Gen Templet2        ������ԭʼͼ������ָ������2
unsigned char code GENT2[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,2,0x00,0x09}; //����12��	

	
//Search Finger      ����CharBufferA��CharBufferB�е������ļ����������򲿷�ָ�ƿ�
unsigned char code SEAT[18]={17,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,   0,8, 4,1,0,0,    0,0x65,  0x00,0x73};	//����16��


//Merge Templet      ;��CharBufferA��CharBufferB�е������ļ��ϲ�����ģ�壬�������ModelBuffer��
unsigned char code MERG[14]={12,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,3,5 , 0x00,0x09};//����12��	

//Store Templet      ����ModelBuffer�е��ļ����浽flashָ�ƿ���
unsigned char code STOR[16]={15,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,6,6,2,     0x00,0x00,     0x00,0x0f}; //����12��

//Read Note
unsigned char code RDNT[14]={13,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,4,0x19,  0, 0x00,0x1e};

//Clear Note
unsigned char code DENT[46]={45,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,36,0x18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x00,0x3d};

//DEL one templet
unsigned char code DELE_one[16]={16, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,7,  0x0c,0x00,0x00, 0,1, 0x00,0x15};

//DEL templet      ;���ָ�ƿ�
unsigned char code DELE_all[12]={12,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,  0x0d,0x00,0x11};


////////////////����ָ���-------����///////////////////////////////////////////////////////////////////////////////////////
unsigned char 		FifoNumber=0; 
unsigned char   FIFO[MAX_NUMBER+1]={0};


unsigned char send_command( unsigned char *p)
{
    unsigned char count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;
  	TxdByte(0xef);//���ݰ���ͷʶ����
	  delay_us(100);
   	TxdByte(0x01);//���ݰ���ͷʶ����
	  delay_us(100);
  	i=*p;         //����ĵڡ�0����Ԫ�ء��������˱�����ĳ��ȣ���������ȸ�����i��������в���
  	p++;
	  p++;
  	for (count=i-1; count!=1;count--)  //Sent command String
    {
	 		temp=*p++;    //ȡ�ڸ���1����Ԫ�ص����ݣ�Ȼ���� 
	    TxdByte(temp);//�����ݷ��ͳ�ȥ
			delay_us(100);
	  }  
  	return 1;//�������,���Ϊ�� (��Ϊ1)   	
}
	
bit Command(unsigned char *p,unsigned char MaxTime) //�������,��ģ�鷢��һ������
{
  	unsigned char count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;
  		
	 bit result=0, start=0,stop=0;
   send_command(p);
  	result=TURE;//�������,���Ϊ�� (��Ϊ1)   	
  	FifoNumber=0;
  	for (count=MAX_NUMBER+1; count!=0; count--)//�������FIFO[]������������ݣ�д��0X00
		 FIFO[count-1]=0x00;  
  	if (result)   
   	{		
     	result=FALSE;
      	start =FALSE;
   		stop  =FALSE;
       	count=0;
       	clk0=0;	//����CL0����
		
       	do /////////////////////////////do������////////////////////////////////
		{	
			restart0:				
	         	if ((S2CON &0x01)==1)//������յ�����
		      	{ 				
			  		tmpdat=S2BUF;//�Ȱѽ��յ������ݷŵ�tmpdat��
	            	S2CON &= ~0x01;
	            	if ((tmpdat==0xef)&&(start==FALSE))//�������Ϊ��һ�������������ݣ�Ҳ���ǡ�ָ��Ӧ�𡱵ĵ�һ���ֽ�
		            	{ 
							count=0;
					    	FIFO[0]=tmpdat;//�����һ��Ӧ���ֽ�(0XEF)�����ڵڡ�0����Ԫ����    
							flag=1;	
							goto 
								restart0;//�������жϷ�ʽ����			
				        	
		             	}
					if(flag==1)//��һ���ֽ��Ѿ�����������flag==1����
						{  
							if(tmpdat!=0x01)  //�������ݴ��󣬽����´ӻ�������������
							{  	
								flag=0;//����Ӧ��ʧ��
								result=FALSE;
		      					start =FALSE;
		   						stop=FALSE;
		       					count=0;
								goto 
									restart0;					
							
							}
							//����ɹ����յ�0xef01�����Կ�ʼ��������
							flag=2;//flag=2;��ʾӦ��ɹ������Կ�ʼ����������
							count++;//����count=1;
							FIFO[count]=tmpdat;//����ڶ���Ӧ���ֽڣ�0X01�������ڵڡ�1����Ԫ����    
							start=TURE;	//Ӧ��ɹ����Կ�ʼ��������
							    goto 
									restart0;	
						}                  
	             	if((flag==2)&&(start==TURE))//flag=2;��ʾӦ��ɹ������Կ�ʼ����������
		             	{	   	  					 
					   		count++; //����Ԫ���±꣫��
				            FIFO[count]=tmpdat;//��������
							if(count>=6)
								{
									checksum=FIFO[count]+checksum; //����У���
								}
							if(count==8)
								{ 
									package=FIFO[7]*0X100+FIFO[8];	//���������							
									stop= TURE;
								}
							if(stop)
								{						
									if(count==package+8)
									{
										checksum=checksum-FIFO[count-1] - FIFO[count];
										if(checksum != (FIFO[count]&0xff)) 
											result=FALSE; //У��ʧ��,�ý����־Ϊ0							
										else 
											result=TURE;
										flag=0;
										break;
									} 
								}
		             	}
	 	       	}
          }/////////////////////////////do������----------------����////////////////////////////////
		   
		while ((clk0 <= MaxTime) && (count <= MAX_NUMBER) && (changeflag==0)); //�ɶ�ʱ���Լ����������������ƣ���֤�����ڴ�һֱѭ��
		  
        FifoNumber=count;	//������յ������ݸ���
	 }
   return (result);
}


bit VefPSW(void)//��֤�豸���ֿ���,�ɹ�����1     
{
 	unsigned char  count=0;
	while (1)
   	{
     	if(Command(VPWD,20) && (FifoNumber==11) && (FIFO[9]==0x00))  
			return(1);
     	count++;
   	  	if (count>=2)//������ɹ�������֤һ�Σ�������β��ɹ�������ʧ��
	        {  
	            return(0);   
	 	    }
	}
}


void Clear_All(void) //���ָ�ƿ�   
{				
      delay_ms(200);
	  Command(DELE_all,50); //���ָ�ƿ�  		
}
void Clear_ONE(u8 num) //���ָ�ƿ�   
{			
    if(Command(DELE_one,60) && (FifoNumber==11) && (FIFO[9]==0x00) )  
    {
		    return 1;
  	}     
    else             
    {
       	return 0;
    }  	
      delay_ms(200); 		
}



unsigned char ImgProcess(unsigned char BUFID)  //����ȡͼ�����������ļ�������BUFID��//�������Ϊ��������  
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

bit Searchfinger(void)//����ָ��(������������Լ����ݷ���ֵȷ���Ƿ����)        
{		
   	if(Command(SEAT,60) && (FifoNumber==15) && (FIFO[9]==0x00) )  
    {
		SearchNumber=FIFO[10]*0x100+FIFO[11];//��������ҳ��
		//MatchScore=FIFO[12]*0x100+FIFO[13]   �����ڴ˼���÷֣��Ӷ����а�ȫ�����趨�����������
	   	return 1;
	}     
    else             
    {
       	return 0;
    }  
}


unsigned char search(void)//����ָ�� 
{
	
 	unsigned char SearchBuf=0,i=0;
  	while (i<20)
    {
     	if (ImgProcess(1)==1)//���ȶ���һ��ָ��  
       	{
       		SearchBuf=Searchfinger();//����ָ�Ʊȶԣ������������������������ָ�����
       		if(SearchBuf==1)
       			return SearchNumber; 
       		else 
						return 255;//��ʾ��������ָ�Ʋ���ȷ
	     
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

bit savefingure(unsigned char ID)//����ָ��
{
	 unsigned char i=0;
	 //���ڿ�ʼ���д洢ָ��ģ��Ĳ���
     for (i=0;i<16;i++)	//����ָ����Ϣ
	 {
		FIFO[i]=STOR[i];
	}  

     FIFO[12]=ID; //��ָ��ģ���ŵ�PAGE_IDҲ����FLASH��λ��
     FIFO[14]=FIFO[14]+ID;	//У���

     if (Command(FIFO,70)==1)//�˴����д��ָ��ģ�������
	 {
	   return(1);
	 }
     else
	 {
	   return(0);//���ɹ�����0
	 } 
}



unsigned char enroll(void) //�ɼ�����ָ�ƣ�����1�� ָ��ģ��
{
 	unsigned char temp=0,count=0;
  	while(1)
  	{
  	 	temp=ImgProcess(1); //��������1    
   		if (temp==1)//���������ļ��ɹ�             
      	{  		      
        	//�ɼ���һ�������ɹ� 
		   	count=0;  
		  	buzzer=0;
			delay_ms(100);
			buzzer=1;
			break;
       	}
     	else                   
       	{
        	if (temp==0)//�ɼ�ָ��û�гɹ�
          	{ 
				count++;
            	if (count>=40)//����ɼ���40�Σ������ɹ���ֱ�Ӳɼ�ʧ�ܣ�ֱ���˳�enroll����������������0  
					return(0);
            }
        }
   	}

	delay_ms(2000);//��ʱ2S��ʼ�ɼ���һ������

	//��ʼ�ɼ��ڶ������� 
 	while(1)
  	{
   		temp=ImgProcess(2); //��������2    
   		if (temp==1)//���������ļ�2�ɹ�
      	{
        	if (  (Command(MERG,40)&& (FifoNumber==11) && (FIFO[9]==0x00))==1  ) //�ϲ��ɹ�����1
			{
			     buzzer=0;
	             delay_ms(1000);
	             buzzer=1;
				 delay_ms(1000);
				 buzzer=0;
	             delay_ms(1000);	//����������ʾ����һ��ģ��ɹ�
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
        	if (temp==1)//�ɼ�ָ��û�гɹ�
        	{
				    count++;
				    if (count>=25) 
				    return(0);
       		}
     	}
   	}
}



