#include <msp430x14x.h>  
//#include "Config.h"  
//#include "clock.h"  
//#include "1602.h"  
//*************************************************************************  
//          初始化IO口子程序  
//*************************************************************************  
void LCD1602Port_init()  
{  
  
    P4SEL = 0x00;  
        P4DIR = 0xFF;                   //数据口输出模式  
        P5SEL = 0x00;  
        P5DIR|= BIT5 + BIT6 + BIT7;     //控制口设置为输出模式  
}  
  
//***********************************************************************  
//  显示屏命令写入函数  
//***********************************************************************  
void LCD1602_write_com(unsigned char com)   
{     
    RS_CLR;  
    RW_CLR;  
    EN_SET;  
    DataPort = com;                 //命令写入端口  
    delay_ms(5);  
    EN_CLR;  
}  
  
//***********************************************************************  
//  显示屏数据写入函数  
//***********************************************************************  
void LCD1602_write_data(unsigned char data)   
{  
    RS_SET;  
    RW_CLR;  
    EN_SET;  
    DataPort = data;                //数据写入端口  
    delay_ms(5);  
    EN_CLR;  
}  
  
//***********************************************************************  
//  显示屏清空显示  
//***********************************************************************  
void LCD1602_clear(void)   
{  
    LCD1602_write_com(0x01);            //清屏幕显示  
    delay_ms(5);  
}  
  
//***********************************************************************  
//  显示屏字符串写入函数  
//***********************************************************************  
void LCD1602_write_str(unsigned char x,unsigned char y,unsigned char *s)   
{  
      
    if (y == 0)   
    {  
        LCD1602_write_com(0x80 + x);        //第一行显示  
    }  
    else   
    {  
        LCD1602_write_com(0xC0 + x);        //第二行显示  
    }  
      
    while (*s)   
    {  
        LCD1602_write_data( *s);  
        s ++;  
    }  
}  
  
//***********************************************************************  
//  显示屏单字符写入函数  
//***********************************************************************  
void LCD1602_write_char(unsigned char x,unsigned char y,unsigned char data)   
{  
      
    if (y == 0)   
    {  
        LCD1602_write_com(0x80 + x);        //第一行显示  
    }  
    else   
    {  
        LCD1602_write_com(0xC0 + x);        //第二行显示  
    }  
      
    LCD1602_write_data( data);    
}  
  
//***********************************************************************  
//  显示屏初始化函数  
//***********************************************************************  
void LCD1602_init(void)   
{  
    LCD1602_write_com(0x38);        //显示模式设置    
    delay_ms(5);  
    LCD1602_write_com(0x08);        //显示关闭  
    delay_ms(5);  
    LCD1602_write_com(0x01);        //显示清屏  
    delay_ms(5);  
    LCD1602_write_com(0x06);        //显示光标移动设置  
    delay_ms(5);  
    LCD1602_write_com(0x0C);        //显示开及光标设置  
    delay_ms(5);  
}  
  
void LCD1602_write_double(unsigned char x,unsigned char y,unsigned int data)  
{  
  uchar i;  
      for(i=0;i<6;i++)  
    {  
      if(i==2)  
      LCD1602_write_char( x--, y, '.');  
      else  
      {    
        LCD1602_write_char( x--, y, 0x30+data%10);  
        data=data/10;  
      }  
    }  
}  
  
void LCD1602_write_int(unsigned char x,unsigned char y,unsigned int data)  
{  
  uchar i;  
  for(i=0;i<2;i++)  
  {   
      LCD1602_write_char( x--, y, 0x30+data%10);  
      data=data/10;  
  }  
}  
  
void Start_1602()  
{  
    LCD1602Port_init();                //系统初始化，设置IO口属性  
    delay_ms(100);                     //延时100ms  
    LCD1602_init();                    //液晶参数初始化设置  
}  