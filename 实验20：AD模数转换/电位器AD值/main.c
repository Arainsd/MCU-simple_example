/**************************************************************************************
*		              电位器AD实验												  *
实现现象：下载程序后数码管后4位显示电位器检测的AD值，范围是0-4095，一般达不到最大，这个受
			你供电电压的影响.
注意事项：如果不想让点阵模块显示，可以将74HC595模块上的JP595短接片拔掉。																				  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include"XPT2046.h"	

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 disp[4];
u8 code smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* 函数名         :datapros()
* 函数功能		 :数据处理函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void datapros()
{
	u16 temp;
	static u8 i;
	if(i==50)
	{
		i=0;
		temp = Read_AD_Data(0x94);		//   AIN0 电位器
	}
	i++;
	disp[0]=smgduan[temp/1000];//千位
	disp[1]=smgduan[temp%1000/100];//百位
	disp[2]=smgduan[temp%1000%100/10];//个位
	disp[3]=smgduan[temp%1000%100%10];		
}


/*******************************************************************************
* 函数名         :DigDisplay()
* 函数功能		 :数码管显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0;i<4;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位	
		}
		P0=disp[3-i];//发送数据
		delay(100); //间隔一段时间扫描	
		P0=0x00;//消隐
	}		
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	while(1)
	{
		datapros();	 //数据处理函数
		DigDisplay();//数码管显示函数		
	}		
}

