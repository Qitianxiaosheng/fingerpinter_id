//#include "stc15f2k60s2.h"
//#include <intrins.h>  
////6ָ��ģ��6�� GND  3-VCC  5��TXD   4��RXD   ͨ�Ų�����57600
//#define TRUE 1

//unsigned char 	SaveNumber=0,searchnum=0;
//unsigned int  	SearchNumber=0;		

//unsigned int 	clk0=0;

//sbit relay =P2^4; //�̵�������
//sbit buzzer=P2^5; //����������
//sbit red=   P2^1;//¼��ģʽָʾ�� �ڰ��ӿ�����Ƭ����
//sbit green= P2^0;//ʶ��ģʽָʾ�� �ڰ���Զ�뵥Ƭ����


//sbit k1=P3^3; //ģʽʶ��
//sbit k2=P3^4; //¼��һ��ָ��
//sbit k3=P3^2; //�������ָ�ƣ�10��ָ�������

////��������:
//unsigned char code tab[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//����������� 0-9 
//					
////��������Ŷ���:
//sbit SMG_g = P1^3;	//����������������ƽţ���λ��
////���ڳ����ж�ʱ������ ������һλ�������ʾ ��Ϊ��̫��ʾ �����Ƽ������1602����12864Һ�� 


//bit changeflag=0,modeflag=0,clearallflag=0;  //Ĭ��Ϊʶ��ģʽ�����Ϊ1Ϊ¼��ָ��ģʽ,ÿ¼��һ��SaveNumber++


////////////////////////////////////////����ָ���/////////////////////////////

////Verify  Password   ����֤�豸���ֿ���
//unsigned char code VPWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};	 //����12��

////�����豸���ֿ���
//unsigned char code STWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x12,0x00,0x00,0x00,0x00,0x00,0x1a};	 //����12��

////GetImage           ��̽����ָ���Ӵ������϶���ͼ��
//unsigned char code GIMG[14]={12, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,1,0x00,0x05};	//����12��

////Gen Templet1        ������ԭʼͼ������ָ������1
//unsigned char code GENT1[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,1,0x00,0x08};	//����12��

////Gen Templet2        ������ԭʼͼ������ָ������2
//unsigned char code GENT2[14]={13,0X01 ,0Xff,0xff,0xff,0xff,0x01,0,4,2,2,0x00,0x09}; //����12��	

//	
////Search Finger      ����CharBufferA��CharBufferB�е������ļ����������򲿷�ָ�ƿ�
//unsigned char code SEAT[18]={17,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,   0,8, 4,1,0,0,    0,0x65,  0x00,0x73};	//����16��


////Merge Templet      ;��CharBufferA��CharBufferB�е������ļ��ϲ�����ģ�壬�������ModelBuffer��
//unsigned char code MERG[14]={12,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,3,5 , 0x00,0x09};//����12��	

////Store Templet      ����ModelBuffer�е��ļ����浽flashָ�ƿ���
//unsigned char code STOR[16]={15,  0X01 ,0Xff,0xff,0xff,0xff, 0x01,  0,6,6,2,     0x00,0x00,     0x00,0x0f}; //����12��

////Read Note
//unsigned char code RDNT[14]={13,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,4,0x19,  0, 0x00,0x1e};

////Clear Note
//unsigned char code DENT[46]={45,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,36,0x18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x00,0x3d};

////DEL one templet
//unsigned char code DELE_one[16]={16, 0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,7,  0x0c,0x00,0x00, 0,1, 0x00,0x15};

////DEL templet      ;���ָ�ƿ�
//unsigned char code DELE_all[12]={12,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,3,  0x0d,0x00,0x11};


//////////////////����ָ���-------����///////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////�궨��////////////////////////////////////////////////////////////////////////
//#define FALSE 0
//#define TURE  1

////״̬�����
//#define on    	1
//#define off   	0

//#define MAX_NUMBER    63 
//#define _Nop()  _nop_()


////////////////////////////////////////�궨��------------����////////////////////////////////////////////////////////

//unsigned char 		 FifoNumber=0; 
//unsigned char    FIFO[MAX_NUMBER+1]={0};

///*********1������ʱ����**********/
//void delay1ms(unsigned int t)
//{
//	unsigned int i,j;
//	for(i=0;i<t;i++)
//	   for(j=0;j<120;j++)
//	   ;
//}


//void TxdByte(unsigned char dat)//���ڷ�����Ϣ,ͨ����ѯ��ʽ����һ���ַ�
//{
//    TI = 0;		 //��TI��0
//    SBUF = dat;	 //��������
//    while(!TI);	 //�ȴ��������
//    TI = 0;		 //����
//}

//bit Command(unsigned char *p,unsigned char MaxTime) //�������,��ģ�鷢��һ������
//{
//  	unsigned char count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;
//  		
//	bit result=0, start=0,stop=0;

//  	TxdByte(0xef);//���ݰ���ͷʶ����
//   	TxdByte(0x01);//���ݰ���ͷʶ����
//  	i=*p;         //����ĵڡ�0����Ԫ�ء��������˱�����ĳ��ȣ���������ȸ�����i��������в���
//  	p++;
//	  p++;
//  	for (count=i-1; count!=1;count--)  //Sent command String
//    {
//	 		temp=*p++;    //ȡ�ڸ���1����Ԫ�ص����ݣ�Ȼ���� 
//	    	TxdByte(temp);//�����ݷ��ͳ�ȥ
//	}  
//  	result=TURE;//�������,���Ϊ�� (��Ϊ1)   	
//  	FifoNumber=0;
//  	for (count=MAX_NUMBER+1; count!=0; count--)//�������FIFO[]������������ݣ�д��0X00
//		 FIFO[count-1]=0x00;  
//  	if (result)   
//   	{		
//     	result=FALSE;
//      	start =FALSE;
//   		stop  =FALSE;
//       	count=0;
//       	clk0=0;	//����CL0����
//		
//       	do /////////////////////////////do������////////////////////////////////
//		{	
//			restart0:				
//	         	if (RI==1)//������յ�����
//		      	{ 				
//			  		tmpdat=SBUF;//�Ȱѽ��յ������ݷŵ�tmpdat��
//	            	RI=0;
//	            	if ((tmpdat==0xef)&&(start==FALSE))//�������Ϊ��һ�������������ݣ�Ҳ���ǡ�ָ��Ӧ�𡱵ĵ�һ���ֽ�
//		            	{ 
//							count=0;
//					    	FIFO[0]=tmpdat;//�����һ��Ӧ���ֽ�(0XEF)�����ڵڡ�0����Ԫ����    
//							flag=1;	
//							goto 
//								restart0;//�������жϷ�ʽ����			
//				        	
//		             	}
//					if(flag==1)//��һ���ֽ��Ѿ�����������flag==1����
//						{  
//							if(tmpdat!=0x01)  //�������ݴ��󣬽����´ӻ�������������
//							{  	
//								flag=0;//����Ӧ��ʧ��
//								result=FALSE;
//		      					start =FALSE;
//		   						stop=FALSE;
//		       					count=0;
//								goto 
//									restart0;					
//							
//							}
//							//����ɹ����յ�0xef01�����Կ�ʼ��������
//							flag=2;//flag=2;��ʾӦ��ɹ������Կ�ʼ����������
//							count++;//����count=1;
//							FIFO[count]=tmpdat;//����ڶ���Ӧ���ֽڣ�0X01�������ڵڡ�1����Ԫ����    
//							start=TURE;	//Ӧ��ɹ����Կ�ʼ��������
//							    goto 
//									restart0;	
//						}                  
//	             	if((flag==2)&&(start==TURE))//flag=2;��ʾӦ��ɹ������Կ�ʼ����������
//		             	{	   	  					 
//					   		count++; //����Ԫ���±꣫��
//				            FIFO[count]=tmpdat;//��������
//							if(count>=6)
//								{
//									checksum=FIFO[count]+checksum; //����У���
//								}
//							if(count==8)
//								{ 
//									package=FIFO[7]*0X100+FIFO[8];	//���������							
//									stop= TURE;
//								}
//							if(stop)
//								{						
//									if(count==package+8)
//									{
//										checksum=checksum-FIFO[count-1] - FIFO[count];
//										if(checksum != (FIFO[count]&0xff)) 
//											result=FALSE; //У��ʧ��,�ý����־Ϊ0							
//										else 
//											result=TURE;
//										flag=0;
//										break;
//									} 
//								}
//		             	}
//	 	       	}
//          }/////////////////////////////do������----------------����////////////////////////////////
//		   
//		while ((clk0 <= MaxTime) && (count <= MAX_NUMBER) && (changeflag==0)); //�ɶ�ʱ���Լ����������������ƣ���֤�����ڴ�һֱѭ��
//		  
//        FifoNumber=count;	//������յ������ݸ���
//	 }
//   return (result);
//}

//bit VefPSW(void)//��֤�豸���ֿ���,�ɹ�����1     
//{
// 	unsigned char  count=0;
//	while (1)
//   	{
//     	if(Command(VPWD,20) && (FifoNumber==11) && (FIFO[9]==0x00))  
//			return(1);
//     	count++;
//   	  	if (count>=2)//������ɹ�������֤һ�Σ�������β��ɹ�������ʧ��
//	        {  
//	            return(0);   
//	 	    }
//	}
//}


//void Clear_All(void) //���ָ�ƿ�   
//{				
//      delay1ms(200);
//	  Command(DELE_all,50); //���ָ�ƿ�  		
//}

//unsigned char ImgProcess(unsigned char BUFID)  //����ȡͼ�����������ļ�������BUFID��//�������Ϊ��������  
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

//bit Searchfinger(void)//����ָ��(������������Լ����ݷ���ֵȷ���Ƿ����)        
//{		
//   	if(Command(SEAT,60) && (FifoNumber==15) && (FIFO[9]==0x00) )  
//    {
//		SearchNumber=FIFO[10]*0x100+FIFO[11];//��������ҳ��
//		//MatchScore=FIFO[12]*0x100+FIFO[13]   �����ڴ˼���÷֣��Ӷ����а�ȫ�����趨�����������
//	   	return 1;
//	}     
//    else             
//    {
//       	return 0;
//    }  
//}


//unsigned char search(void)//����ָ�� 
//{
// 	unsigned char SearchBuf=0,i=0;
//  	while (i<20)
//    {
//     	if (ImgProcess(1)==1)//���ȶ���һ��ָ��  
//       	{
//       		SearchBuf=Searchfinger();//����ָ�Ʊȶԣ������������������������ָ�����
//       		if(SearchBuf==1)
//       		{
//       			return SearchNumber; 
//       		}
//       		else 
//			{
//			   return 255;//��ʾ��������ָ�Ʋ���ȷ
//			}     
//       	}
//		i++;	
//    }
//   return 0;
//}

//bit savefingure(unsigned char ID)//����ָ��
//{
//	 unsigned char i=0;
//	 //���ڿ�ʼ���д洢ָ��ģ��Ĳ���
//     for (i=0;i<16;i++)	//����ָ����Ϣ
//	 {
//		FIFO[i]=STOR[i];
//	}  

//     FIFO[12]=ID; //��ָ��ģ���ŵ�PAGE_IDҲ����FLASH��λ��
//     FIFO[14]=FIFO[14]+ID;	//У���

//     if (Command(FIFO,70)==1)//�˴����д��ָ��ģ�������
//	 {
//	   return(1);
//	 }
//     else
//	 {
//	   return(0);//���ɹ�����0
//	 } 
//}



//unsigned char enroll(void) //�ɼ�����ָ�ƣ�����1�� ָ��ģ��
//{
// 	unsigned char temp=0,count=0;
//  	while(1)
//  	{
//  	 	temp=ImgProcess(1); //��������1    
//   		if (temp==1)//���������ļ��ɹ�             
//      	{  		      
//        	//�ɼ���һ�������ɹ� 
//		   	count=0;  
//		  	buzzer=0;
//			delay1ms(100);
//			buzzer=1;
//			break;
//       	}
//     	else                   
//       	{
//        	if (temp==0)//�ɼ�ָ��û�гɹ�
//          	{ 
//				count++;
//            	if (count>=40)//����ɼ���40�Σ������ɹ���ֱ�Ӳɼ�ʧ�ܣ�ֱ���˳�enroll����������������0  
//					return(0);
//            }
//        }
//   	}

//	delay1ms(2000);//��ʱ2S��ʼ�ɼ���һ������

//	//��ʼ�ɼ��ڶ������� 
// 	while(1)
//  	{
//   		temp=ImgProcess(2); //��������2    
//   		if (temp==1)//���������ļ�2�ɹ�
//      	{
//        	if (  (Command(MERG,40)&& (FifoNumber==11) && (FIFO[9]==0x00))==1  ) //�ϲ��ɹ�����1
//			{
//			     buzzer=0;
//	             delay1ms(1000);
//	             buzzer=1;
//				 delay1ms(1000);
//				 buzzer=0;
//	             delay1ms(1000);	//����������ʾ����һ��ģ��ɹ�
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
//        	if (temp==1)//�ɼ�ָ��û�гɹ�
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
////	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
////	SCON = 0x50;		//8λ����,�ɱ䲨����
////	TMOD = 0x21;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
////	  AUXR=0X40;		 //����1Tģʽ
////	TL1 = 0xFF;		//�趨��ʱ��ֵ
////	TH1 = 0xFF;		//�趨��ʱ����װֵ
////	ET1 = 0;		//��ֹ��ʱ��1�ж�
////	TR1 = 1;		//������ʱ��1

//        SCON=0x50;        //REN=1�����н���״̬�����ڹ���ģʽ2     	   
//	   TMOD= 0x00;       //��ʱ��1Ϊģʽ0��16λ�Զ����أ�                
//	   AUXR=0X40;		 //����1Tģʽ
//       TL1=(65535-(11059200/4/57600));    //���ò�������װֵ
//	   TH1=(65535-(11059200/4/57600))>>8;

//                        // ���в�������� STC15�ֲ�������ϸ˵�� 	 619ҳ
//      
//	   TR1  = 1;        //������ʱ��1  
//	//   ES   = 1;        //�������ж�                                                                     
//	  // EA   = 1;        // �����ж� 



//}


//void main(void)//������
//{
//	unsigned char i=0;

//	 
//	UartInit();

//	ET0=1;     //��ʱ��0���ж�
//	TL0=0x97;  //17ms�ĳ�ֵ
//	TH0=0xBD;
//    TR0=1;// ����ʱ��0
//	
//	IT0=0;//�ж�0�͵�ƽ�ж�
//	IT1=1;//�ж�1�͵�ƽ�ж�
//	EX0=1;//���ж�0
//	EX1=1;//���ж�1
//    EA=1;

//	SMG_g = 0x01;	 /////0
//	P1 = 0x01;	 /////0
//	P0 = ~tab[0];//��ʾ0	////////����~��Ϊ����

//	for(i=0;i<6;i++)//��ʼ����6�Σ����û��һ�γɹ�����ʾģ��ͨ�Ų�������ֻҪ�ɹ���������ѭ��
//	{
//		if(VefPSW()==1)//��ģ������ͨ�����̵����𡣽���ʶ��ģʽ
//		 {
//				green=0;
//				buzzer=0;
//	            delay1ms(300);
//	            buzzer=1;
//				green=1;
//                red=0;
//				break; //�ɹ����˳����ѭ��
//		}
//	}


//    while(1)
//	{	 //CLK_DIV=0x03;//���÷�Ƶ03
//		if(k2==0)//¼��һ��ָ��
//		{
//			  	delay1ms(10);	
//			  	if(k2==0)//�����Ϊ�͵�ƽ����ʾ������Ч
//				  	{
//				  	  while(k2==0);//�ȴ�����
//					  if(VefPSW()==1&&modeflag==1&&SaveNumber<10)//��ģ������ͨ��
//						  {
//						  	  if(enroll()==1)//�ɼ����Σ�����1��ָ��ģ��ɹ�
//							  	{
//								   if(savefingure(SaveNumber+1)==1)//����Ҳ�ɹ�
//								   	{
//										SaveNumber++;//��һ��
//										P0=~tab[SaveNumber];	   ////////����~��Ϊ����
//										delay1ms(200);
//										P0=0x00;//��һ����ʾ����˸һ��
//										delay1ms(200);
//										P0=~tab[SaveNumber];	   ////////����~��Ϊ����
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

//		if(modeflag==0)//Ϊʶ��ģʽ
//		{
//			  green=0;
//			  red=1;
//			  searchnum=search();
//			  if(searchnum>=1&&searchnum<=162)//ֻ�ܴ���162��ָ��
//			  {
//			  	  	P0=~tab[searchnum];//��ʾ��������ָ��ģ��	  ////////����~��Ϊ����
//			       //��������һ�� 
//				    //�̵�����Լ3����
//				   relay=0;
//			       buzzer=0;
//			       delay1ms(1000);
//			       buzzer=1;
//				   delay1ms(10000);
//				   relay=1;
//				   
//			  }
//			  if(searchnum==255)//����ȷ��ָ�� ������������
//			  {
//			  	   P0=~tab[0];//��ʾ0			  ////////����~��Ϊ����
//				   buzzer=0;delay1ms(100); buzzer=1;delay1ms(100);
//			       buzzer=0;delay1ms(100); buzzer=1;delay1ms(100);
//			       buzzer=0;delay1ms(100); buzzer=1;delay1ms(100); 
//			  }
//		}

//		if(modeflag==1)//¼��ģʽ
//		{
//		  green=1;
//		  red=0;
//		}

//		if(clearallflag==1)
//		{
//			clearallflag=0;
//			Clear_All();
//		    red=0;	     //��ɫ����
//		    green=1;
//			//����������һ�Σ���ʾ�������ָ�ƽ���
//			modeflag=1;//����¼��ָ��ģʽ
//			P0=~tab[0];//��ʾû��ָ��¼��	  ////////����~��Ϊ����
//			buzzer=0;
//			delay1ms(1200);
//			buzzer=1;
//			SaveNumber=0;
//		}

//		if(changeflag==1)
//		{
//		    changeflag=0;
//			if(modeflag==0) //ʶ��ģʽ
//			 {
//			 	green=0;
//				red=1;
//				P0=~tab[0];//��ʾ��ǰ�м��� ָ��		 ////////����~��Ϊ����		   
//			 }
//			 else		   //¼��ģʽ
//			 {
//			 	red=0;
//				green=1;
//				P0=~tab[0];//��ʾ0	  ////////����~��Ϊ����		   
//			 }
//		}
//	}////////////////////////////while(1)����////////////////////////////////
//	
//}



//void  Timer0(void) interrupt 1//��ʱ��0�жϺ���
//{
// 	TL0=0x97;
//	TH0=0xBD;
//	clk0++;   //��ʱ17ms
//}

//void int0(void) interrupt 0//�ж�0���������ָ��
//{
//	if(k3==0) //�������ָ��
//	{
//		delay1ms(10);
//		if(k3==0)//�����Ϊ�͵�ƽ����ʾ������Ч
//		{
//			while(k3==0);//�ȴ�����	
//			clearallflag=1;
//			changeflag=1;
//		}	
//	}	
//}


//void int1(void) interrupt 2//�ж�1��ģʽת��
//{
//	if(k1==0)//ģʽת�� ������modeflag ����־,Ĭ�ϴӵ�1��ָ�ƿ�ʼ¼��
//	{
//	  delay1ms(10);	
//	  if(k1==0)//�����Ϊ�͵�ƽ����ʾ������Ч
//	  	{
//			 while(k1==0);//�ȴ�����
//			 modeflag=~modeflag;//0��ʾ¼��ָ��  1��ʾʶ��ָ��
//			 changeflag=1;
//		}	
//	}	
//}