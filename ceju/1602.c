#include <msp430x14x.h>  
//#include "Config.h"  
//#include "clock.h"  
//#include "1602.h"  
//*************************************************************************  
//          ��ʼ��IO���ӳ���  
//*************************************************************************  
void LCD1602Port_init()  
{  
  
    P4SEL = 0x00;  
        P4DIR = 0xFF;                   //���ݿ����ģʽ  
        P5SEL = 0x00;  
        P5DIR|= BIT5 + BIT6 + BIT7;     //���ƿ�����Ϊ���ģʽ  
}  
  
//***********************************************************************  
//  ��ʾ������д�뺯��  
//***********************************************************************  
void LCD1602_write_com(unsigned char com)   
{     
    RS_CLR;  
    RW_CLR;  
    EN_SET;  
    DataPort = com;                 //����д��˿�  
    delay_ms(5);  
    EN_CLR;  
}  
  
//***********************************************************************  
//  ��ʾ������д�뺯��  
//***********************************************************************  
void LCD1602_write_data(unsigned char data)   
{  
    RS_SET;  
    RW_CLR;  
    EN_SET;  
    DataPort = data;                //����д��˿�  
    delay_ms(5);  
    EN_CLR;  
}  
  
//***********************************************************************  
//  ��ʾ�������ʾ  
//***********************************************************************  
void LCD1602_clear(void)   
{  
    LCD1602_write_com(0x01);            //����Ļ��ʾ  
    delay_ms(5);  
}  
  
//***********************************************************************  
//  ��ʾ���ַ���д�뺯��  
//***********************************************************************  
void LCD1602_write_str(unsigned char x,unsigned char y,unsigned char *s)   
{  
      
    if (y == 0)   
    {  
        LCD1602_write_com(0x80 + x);        //��һ����ʾ  
    }  
    else   
    {  
        LCD1602_write_com(0xC0 + x);        //�ڶ�����ʾ  
    }  
      
    while (*s)   
    {  
        LCD1602_write_data( *s);  
        s ++;  
    }  
}  
  
//***********************************************************************  
//  ��ʾ�����ַ�д�뺯��  
//***********************************************************************  
void LCD1602_write_char(unsigned char x,unsigned char y,unsigned char data)   
{  
      
    if (y == 0)   
    {  
        LCD1602_write_com(0x80 + x);        //��һ����ʾ  
    }  
    else   
    {  
        LCD1602_write_com(0xC0 + x);        //�ڶ�����ʾ  
    }  
      
    LCD1602_write_data( data);    
}  
  
//***********************************************************************  
//  ��ʾ����ʼ������  
//***********************************************************************  
void LCD1602_init(void)   
{  
    LCD1602_write_com(0x38);        //��ʾģʽ����    
    delay_ms(5);  
    LCD1602_write_com(0x08);        //��ʾ�ر�  
    delay_ms(5);  
    LCD1602_write_com(0x01);        //��ʾ����  
    delay_ms(5);  
    LCD1602_write_com(0x06);        //��ʾ����ƶ�����  
    delay_ms(5);  
    LCD1602_write_com(0x0C);        //��ʾ�����������  
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
    LCD1602Port_init();                //ϵͳ��ʼ��������IO������  
    delay_ms(100);                     //��ʱ100ms  
    LCD1602_init();                    //Һ��������ʼ������  
}  