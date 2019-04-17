#include "state.h"
#define add_day 0
#define add_hor 1
#define add_min 2

 extern KeyValue;
 extern flag;
 extern uchar TIME[7];	
 u8 rtc_flag = add_day;
 u8 id_flag = id_000;
 u8 pwd_flag=0;
 u8 id_stat0[] = " id_000 ";
 u8 id_stat1[] = " id_001 ";
 u8 id_stat2[] = " id_002 ";
 
 
/*******************************************************************************
* �� �� ��         :   idle_handle
* ��������		     : ���з�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void idle_handle(void)
{
 
  u8 stat[]=" IDLE_STATE";
  Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
  Ds1302ReadTime();
	DisplayOneChar(1,1,'0'+TIME[4]/16);			//��
	DisplayOneChar(2,1,'0'+(TIME[4]&0x0f));
	DisplayOneChar(3,1,'-');
	DisplayOneChar(4,1,'0'+TIME[3]/16);			//��
	DisplayOneChar(5,1,'0'+(TIME[3]&0x0f));
	DisplayOneChar(6,1,'-');
	DisplayOneChar(7,1,'0'+TIME[2]/16);				//ʱ
	DisplayOneChar(8,1,'0'+(TIME[2]&0x0f));				 
	DisplayOneChar(9,1,'-');
	DisplayOneChar(10,1,'0'+TIME[1]/16);				//��
	DisplayOneChar(11,1,'0'+(TIME[1]&0x0f));	
	DisplayOneChar(12,1,'-');
	DisplayOneChar(13,1,'0'+TIME[0]/16);				//��
	DisplayOneChar(14,1,'0'+(TIME[0]&0x0f));
	if(KEY2==0)
	{	
		delay_ms(10);
		if(KEY2 == 0)
		{
		 switch(rtc_flag)
			{	
				case add_day : rtc_flag = add_hor;break;
			  case add_hor : rtc_flag = add_min;break;
				case add_min : rtc_flag = add_day;break;
				default : rtc_flag = add_day;break;
			}
		 while(!KEY2);
    }
	}
	if(KEY3==0)//
	{
		delay_ms(10);	
		if(KEY3==0)//�����Ϊ�͵�ƽ����ʾ������Ч
		{
			  bcd2hex();
				while(KEY3==0);//�ȴ�����
					switch(rtc_flag)
			 {
				case add_day:
					if(TIME[3]<=29)
						TIME[3]=TIME[3]+1;
					else
					{
						TIME[4]=TIME[4]+1;
						TIME[3]=1;
					}
					  break;
				case add_hor:
				  if(TIME[2]<=50)
						TIME[2]=TIME[2]+1;
					break;
				case add_min:
				  if(TIME[1]<=58)
						TIME[1]=TIME[1]+1;
					else
						TIME[1]=0;
					break;
				default:      break;
			 }
			 hex2bcd();
			 Ds1302Init();
	   }
	}
	 switch(rtc_flag)
			{	
				case add_day : LcdShowStr(15,0,"d");break;
			  case add_hor : LcdShowStr(15,0,"h");break;
				case add_min : LcdShowStr(15,0,"m");break;
				default : rtc_flag = add_day;break;
			}
  delay_ms(50);
		  
}
/*******************************************************************************
* �� �� ��         :   add_handle
* ��������		     : ���ָ�Ʒ�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void add_handle(void)
{
	unsigned char stat[]=" ADD_STATE";
  Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
	if(KEY2==0)
	{	
		delay_ms(10);
		if(KEY2 == 0)
		{
		 switch(id_flag)
			{	
				case id_000 : id_flag = id_001;SaveNumber=1; break;
			  case id_001 : id_flag = id_002;SaveNumber=2; break;
				case id_002 : id_flag = id_000;SaveNumber=0; break;
				default : id_flag = id_000;SaveNumber=1;
			}
		 while(!KEY2);
    }
	}
	
  if(id_flag==id_000)
		LcdShowStr(0,1,id_stat0);
	else if(id_flag==id_001)
    LcdShowStr(0,1,id_stat1);
	else
		LcdShowStr(0,1,id_stat2);
	if(KEY3==0)//¼��һ��ָ��
	{
		delay_ms(10);	
		if(KEY3==0)//�����Ϊ�͵�ƽ����ʾ������Ч
		{
			while(KEY3==0);//�ȴ�����
		  if(VefPSW()==1&&SaveNumber<10)//��ģ������ͨ��
			{
				if(enroll()==1)//�ɼ����Σ�����1��ָ��ģ��ɹ�
				{
					if(savefingure(SaveNumber+1)==1)//����Ҳ�ɹ�
					{
							SaveNumber++;//��һ��
						
						  LcdShowStr(10,1,"OK!");
							delay_ms(2000);
					}
				}
			}
		}
	}
  delay_ms(50);
}
/*******************************************************************************
* �� �� ��         :   del_handle
* ��������		     : ɾ��ָ�Ʒ�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void del_handle (void)
{  

	unsigned char stat[]=" DLE_STATE ";
	Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
	
	if(KEY2==0)
	{	
		delay_ms(10);
		if(KEY2 == 0)
		{
		 switch(id_flag)
			{	
				case id_000 : id_flag = id_001;SaveNumber=1; break;
			  case id_001 : id_flag = id_002; SaveNumber=2;break;
				case id_002 : id_flag = clear_all;SaveNumber=0; break;
			  case clear_all :id_flag = id_000;SaveNumber=10; break;
				default : id_flag = id_000;SaveNumber=1; break;
			}
		 while(!KEY2);
    }
	}
  if(id_flag==id_000)
		LcdShowStr(0,1,id_stat0);
	else if(id_flag==id_001)
    LcdShowStr(0,1,id_stat1);
	else if(id_flag==id_002)
		LcdShowStr(0,1,id_stat2);
	else 
	  LcdShowStr(0,1,"clear_all");
	if(KEY3==0)//
	{
		delay_ms(10);	
		if(KEY3==0)//�����Ϊ�͵�ƽ����ʾ������Ч
		{
				while(KEY3==0);//�ȴ�����
					switch(id_flag)
			 {
				case id_000:  break;
				case id_001:  break;
				case id_002:  break;
				case clear_all: Clear_All(); LcdShowStr(12,1,"OK!");;delay_ms(1500);break;
				default:DisplayOneChar(4,1,'0'+searchnum);
			
			 }
	  }
	
	}
	
	
  delay_ms(50);
}
/*******************************************************************************
* �� �� ��         :   identify_handle
* ��������		     : ʶ��ָ�Ʒ�����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void identify_handle(void)
{
	
	unsigned char stat[]=" IFY_STATE ";
	Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
   if(WAK_Check())
	{
    searchnum=search();
    if(searchnum>=1&&searchnum<=162)//ֻ�ܴ���162��ָ��
	 {		         
		buzzer=0;//��������һ�� 	 
	  delay_ms(1000);
		buzzer=1;
	  delay_ms(1000);
		switch(searchnum)
		{
			case 1: LcdShowStr(0,1,id_stat0);delay_ms(1500); break;
			case 2: LcdShowStr(0,1,id_stat1);delay_ms(1500); break;
			case 3: LcdShowStr(0,1,id_stat2);delay_ms(1500); break;
			default:DisplayOneChar(4,1,'0'+searchnum);
		
		}
	}
	if(searchnum==255)//����ȷ��ָ�� ������������
	{
		 buzzer=0;delay_ms(100); buzzer=1;delay_ms(100);
		 buzzer=0;delay_ms(100); buzzer=1;delay_ms(100);
		 buzzer=0;delay_ms(100); buzzer=1;delay_ms(100); 
	}
 }
  delay_ms(50);
}
/*******************************************************************************
* �� �� ��         :   pwd_handle
* ��������		     : �ȴ��������Ա����
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void pwd_handle(void)
{
	static KeyState=0;
  unsigned char stat[]="input pwd :";
	Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
	if(KeyState!=3)
		KeyDown();
  if((KeyValue==0)&&(KeyState==0))
	{
		KeyState = 0;
	}
	else if((KeyValue==1)&&(KeyState==0))
	{
		KeyState = 1;
		DisplayOneChar(1,1,'0'+KeyValue);
		delay_ms(500);
	}
		else if((KeyValue==1)&&(KeyState==1))
	{
		KeyState = 1;	
	}
	else if(KeyValue==3&&KeyState==1)
	{
		KeyState = 2;
		DisplayOneChar(2,1,'0'+KeyValue);
		delay_ms(500);
	}
	else if(KeyValue==3&&KeyState==2)
	{
		KeyState = 2;
	}
	else if(KeyValue==4&&KeyState==2)
	{
		KeyState = 3;
		DisplayOneChar(3,1,'0'+KeyValue);
		delay_ms(500);
	}
	else if(KeyState == 3)
	{
		flag = del_state;//����ɾ��ָ��״̬
		KeyState = 3;
		KeyValue=0;
	}
	else
	{
		flag = err_state;//�˳�
		KeyState = 0;
		KeyValue=0;
		delay_ms(500);
	}
  delay_ms(50);
}

/*******************************************************************************
* �� �� ��         :   err_handle
* ��������		     : �������
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�flag��ֵ
*******************************************************************************/
void err_handle(void)
{
	u8 i;
  unsigned char stat[]="       error!";
	Lcd1602_Write_Cmd(0x01); //����
  LcdShowStr(0,0,stat);
	for(i=0;i<9;i++)
	{
		if(i%3==0)
		{  
			 LcdShowStr(0,1,".  ");
			 delay_ms(1000);
		}
		else if(i%3==1)
		{
			 LcdShowStr(1,1,".. ");
			 delay_ms(1000);
		}
	}	
	flag = 0;//�˳�
}
/*******************************************************************************
* �� �� ��         :   bcd2hex
* ��������		     : ��bcd��ת��Ϊhex
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�time����ĸ�ʽ
*******************************************************************************/
void bcd2hex(void)
{
	u16 i;
	for(i=0;i<7;i++)
		TIME[i]=(TIME[i]/16)*10+TIME[i]%16;
}
/*******************************************************************************
* �� �� ��         :   hex2bcd
* ��������		     : ��hex��ת��Ϊbcd
* ��    ��         : ��
* ��    ��         : ��
* ˵    ��         : �ı�time����ĸ�ʽ
*******************************************************************************/
void hex2bcd(void)
{
	u16 i;
	for(i=0;i<7;i++)
		TIME[i]=(TIME[i]/10)*16+TIME[i]%10;
}





