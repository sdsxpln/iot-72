#ifndef _1602_H_
#define _1602_H_
#include <msp430x14x.h>
//*************************************************************************
//			初始化IO口子程序
//*************************************************************************
void Port_Init()
{

	P4SEL = 0x00;
        P4DIR = 0xFF;                   //数据口输出模�?        P5SEL = 0x00;
        P5DIR|= BIT5 + BIT6 + BIT7;     //控制口设置为输出模式
}

//***********************************************************************
//	显示屏命令写入函�?//***********************************************************************
void LCD_write_com(unsigned char com) 
{	
	RS_CLR;
	RW_CLR;
	EN_SET;
	DataPort = com;                 //命令写入端口
	delay_ms(5);
	EN_CLR;
}

//***********************************************************************
//	显示屏数据写入函�?//***********************************************************************
void LCD_write_data(unsigned char data) 
{
	RS_SET;
	RW_CLR;
	EN_SET;
	DataPort = data;                //数据写入端口
	delay_ms(5);
	EN_CLR;
}

//***********************************************************************
//	显示屏清空显�?//***********************************************************************
void LCD_clear(void) 
{
	LCD_write_com(0x01);            //清屏幕显�?	delay_ms(5);
}

//***********************************************************************
//	显示屏字符串写入函数
//***********************************************************************
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s) 
{
	
    if (y == 0) 
    {
    	LCD_write_com(0x80 + x);        //第一行显�?    }
    else 
    {
    	LCD_write_com(0xC0 + x);        //第二行显�?    }
    
    while (*s) 
    {
    	LCD_write_data( *s);
    	s ++;
    }
}

//***********************************************************************
//	显示屏单字符写入函数
//***********************************************************************
void LCD_write_char(unsigned char x,unsigned char y,unsigned char data) 
{
	
    if (y == 0) 
    {
    	LCD_write_com(0x80 + x);        //第一行显�?    }
    else 
    {
    	LCD_write_com(0xC0 + x);        //第二行显�?    }
    
    LCD_write_data( data);  
}
//显示一个不大于五位数的数字
void LCD1602_write_number(unsigned char x,unsigned char y,unsigned int data)
{
  uchar i;
  uint divide=10000;
  data= data%100000;
  for(i=0;i<5;i++)
  {
    LCD1602_write_char( x++, y, 0x30+data/divide);
    data=data%divide;
    divide /=10;
  }
 
}
//***********************************************************************
//	显示屏初始化函数
//***********************************************************************
void LCD_init(void) 
{
    LCD_write_com(0x38);		//显示模式设置  
    delay_ms(5);
    LCD_write_com(0x08);		//显示关闭
    delay_ms(5);
    LCD_write_com(0x01);		//显示清屏
    delay_ms(5);
    LCD_write_com(0x06);		//显示光标移动设置
    delay_ms(5);
    LCD_write_com(0x0C);		//显示开及光标设�?    delay_ms(5);
}

//***********************************************************************
//      液晶显示界面初始�?//***********************************************************************
void LCD_Desk(void)
{    
  LCD_clear();
  LCD_write_str(0,0,"ADC0 Input:");
  LCD_write_str(0,1,"Voltage   :");
  delay_ms(250);
}
#endif
