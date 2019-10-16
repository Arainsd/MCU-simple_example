/**************************************************************************************
*		              8*8LED点阵———显示数字实验												  *
实现现象：下载程序后点阵上显示数字0
			
注意事项：一定要将JOE短接片短接到GND端，如果不需要595后面的小灯点亮可以拔掉JP595短接片。																				  
***************************************************************************************/

#include "reg51.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include<intrins.h>

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

u8 ledduan[]={0x00,0x00,0x3e,0x41,0x41,0x41,0x3e,0x00};
u8 ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* 函数名         : Hc595SendByte(u8 dat)
* 函数功能		   : 向74HC595发送一个字节的数据
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Hc595SendByte(u8 dat)
{
	u8 a;
	SRCLK=0;
	RCLK=0;
	for(a=0;a<8;a++)
	{
		SER=dat>>7;
		dat<<=1;

		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;	
	}

	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{			
	u8 i;
	while(1)
	{
		P0=0x7f;
		for(i=0;i<8;i++)
		{
			P0=ledwei[i];		  //位选
			Hc595SendByte(ledduan[i]);	//发送段选数据
			delay(100);		   //延时
			Hc595SendByte(0x00);  //消隐
		}	
	}		
}
