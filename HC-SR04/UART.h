#ifndef _UART_H_
#define _UART_H_
#include "msp430x14x.h"
//*************************************************************************
//               MSP430串口初始化
//*************************************************************************
void UART_Init()
{
  U0CTL|=SWRST + CHAR;                //复位SWRST，8位数据模式
  U0TCTL|=SSEL1;                      //SMCLK为串口时钟
  U0BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                        //微调寄存器为0，波特率9600bps
  ME1|=UTXE0;                         //UART0发送使能
  ME1|=URXE0;                         //UART0接收使能
  U0CTL&=~SWRST;
  IE1|=URXIE0;                        //接收中断使能位
  
  P3SEL|= BIT4 + BIT5;                //设置IO口为第二功能模式，启用UART功能
  P3DIR|= BIT4;                       //设置TXD0口方向为输出
}

//*************************************************************************
//              串口0发送数据函数
//*************************************************************************

void Send_Byte(uchar data)
{
  while(!(IFG1&UTXIFG0));          //发送寄存器空的时候发送数据
    U0TXBUF=data;
}
//***************************************//
void Print_float(unsigned int  t, unsigned char position)//发送浮点数   position 小数点后面个数
{
  unsigned int s_int[5];
  unsigned char i = 1;
  while(t>0)
  {
    s_int[i] = t%10;
    t=t/10;
    i++;
  }
    i--;
    Send_Byte('&');
    while(i)
    {
      if(i==position)
        Send_Byte(0x2E);
        Send_Byte(0x30 + s_int[i]);
        i--;
    }
}
//*************************************************************************
//              串口0发送int型整数
//*************************************************************************
void Print_int(unsigned int  t)
{
  unsigned int s_int[5];
  unsigned int i = 1;
  while(t>0)
  {
    s_int[i] = t%10;
    t=t/10;
    i++;
  }
    i--;
    while(i)
    {
        Send_Byte(0x30 + s_int[i]);
        i--;
    }
}

//*************************************************************************
//              串口0发送字符串函数
//*************************************************************************
void Print_Str(uchar *s)
{
    while(*s != '\0')
    {
        Send_Byte(*s++);
    }
}
#endif