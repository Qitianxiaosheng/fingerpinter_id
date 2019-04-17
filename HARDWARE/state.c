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
* 函 数 名         :   idle_handle
* 函数功能		     : 空闲服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void idle_handle(void)
{
 
  u8 stat[]=" IDLE_STATE";
  Lcd1602_Write_Cmd(0x01); //清屏
  LcdShowStr(0,0,stat);
  Ds1302ReadTime();
	DisplayOneChar(1,1,'0'+TIME[4]/16);			//月
	DisplayOneChar(2,1,'0'+(TIME[4]&0x0f));
	DisplayOneChar(3,1,'-');
	DisplayOneChar(4,1,'0'+TIME[3]/16);			//日
	DisplayOneChar(5,1,'0'+(TIME[3]&0x0f));
	DisplayOneChar(6,1,'-');
	DisplayOneChar(7,1,'0'+TIME[2]/16);				//时
	DisplayOneChar(8,1,'0'+(TIME[2]&0x0f));				 
	DisplayOneChar(9,1,'-');
	DisplayOneChar(10,1,'0'+TIME[1]/16);				//分
	DisplayOneChar(11,1,'0'+(TIME[1]&0x0f));	
	DisplayOneChar(12,1,'-');
	DisplayOneChar(13,1,'0'+TIME[0]/16);				//秒
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
		if(KEY3==0)//如果仍为低电平，表示按键有效
		{
			  bcd2hex();
				while(KEY3==0);//等待松手
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
* 函 数 名         :   add_handle
* 函数功能		     : 添加指纹服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void add_handle(void)
{
	unsigned char stat[]=" ADD_STATE";
  Lcd1602_Write_Cmd(0x01); //清屏
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
	if(KEY3==0)//录入一个指纹
	{
		delay_ms(10);	
		if(KEY3==0)//如果仍为低电平，表示按键有效
		{
			while(KEY3==0);//等待松手
		  if(VefPSW()==1&&SaveNumber<10)//与模块握手通过
			{
				if(enroll()==1)//采集两次，生成1个指纹模板成功
				{
					if(savefingure(SaveNumber+1)==1)//保存也成功
					{
							SaveNumber++;//加一次
						
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
* 函 数 名         :   del_handle
* 函数功能		     : 删除指纹服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void del_handle (void)
{  

	unsigned char stat[]=" DLE_STATE ";
	Lcd1602_Write_Cmd(0x01); //清屏
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
		if(KEY3==0)//如果仍为低电平，表示按键有效
		{
				while(KEY3==0);//等待松手
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
* 函 数 名         :   identify_handle
* 函数功能		     : 识别指纹服务函数
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void identify_handle(void)
{
	
	unsigned char stat[]=" IFY_STATE ";
	Lcd1602_Write_Cmd(0x01); //清屏
  LcdShowStr(0,0,stat);
   if(WAK_Check())
	{
    searchnum=search();
    if(searchnum>=1&&searchnum<=162)//只能存入162个指纹
	 {		         
		buzzer=0;//蜂鸣器响一声 	 
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
	if(searchnum==255)//不正确的指纹 蜂鸣器响三声
	{
		 buzzer=0;delay_ms(100); buzzer=1;delay_ms(100);
		 buzzer=0;delay_ms(100); buzzer=1;delay_ms(100);
		 buzzer=0;delay_ms(100); buzzer=1;delay_ms(100); 
	}
 }
  delay_ms(50);
}
/*******************************************************************************
* 函 数 名         :   pwd_handle
* 函数功能		     : 等待输入管理员密码
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void pwd_handle(void)
{
	static KeyState=0;
  unsigned char stat[]="input pwd :";
	Lcd1602_Write_Cmd(0x01); //清屏
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
		flag = del_state;//进入删除指纹状态
		KeyState = 3;
		KeyValue=0;
	}
	else
	{
		flag = err_state;//退出
		KeyState = 0;
		KeyValue=0;
		delay_ms(500);
	}
  delay_ms(50);
}

/*******************************************************************************
* 函 数 名         :   err_handle
* 函数功能		     : 密码错误
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变flag的值
*******************************************************************************/
void err_handle(void)
{
	u8 i;
  unsigned char stat[]="       error!";
	Lcd1602_Write_Cmd(0x01); //清屏
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
	flag = 0;//退出
}
/*******************************************************************************
* 函 数 名         :   bcd2hex
* 函数功能		     : 将bcd码转化为hex
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变time数组的格式
*******************************************************************************/
void bcd2hex(void)
{
	u16 i;
	for(i=0;i<7;i++)
		TIME[i]=(TIME[i]/16)*10+TIME[i]%16;
}
/*******************************************************************************
* 函 数 名         :   hex2bcd
* 函数功能		     : 将hex码转化为bcd
* 输    入         : 无
* 输    出         : 无
* 说    名         : 改变time数组的格式
*******************************************************************************/
void hex2bcd(void)
{
	u16 i;
	for(i=0;i<7;i++)
		TIME[i]=(TIME[i]/10)*16+TIME[i]%10;
}





