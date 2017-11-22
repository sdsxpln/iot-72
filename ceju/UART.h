#ifndef _UART_H_
#define _UART_H_
#include "msp430x14x.h"
void Print_Str(uchar *s);
//*************************************************************************
//               MSP430?????
//*************************************************************************
void UART_Init()
{
  U0CTL|=SWRST + CHAR;                //??SWRST,8?????
  U0TCTL|=SSEL1;                      //SMCLK?????
  U0BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                        //??????0,???9600bps
  ME1|=UTXE0;                         //UART0????
  ME1|=URXE0;                         //UART0????
  U0CTL&=~SWRST;
  IE1|=URXIE0;                        //???????
  
  P3SEL|= BIT4 + BIT5;                //??IO????????,??UART??
  P3DIR|= BIT4;                       //??TXD0??????
}

//*************************************************************************
//              ??0??????
//*************************************************************************

void Send_Byte(uchar data)
{
  while(!(IFG1&UTXIFG0));          //?????????????
    U0TXBUF=data;
}
//***************************************//
void Print_float(unsigned int  t, unsigned char position)//?????   position ???????
{
  unsigned int s_int[5] = {0};
  int i = 0;
  while(t>0)
  {
    s_int[i++] = t%10;
    t=t/10;
  }
  for(i=4;i>=0;i--)  
  {  
    if(i==position) 
    {
      Send_Byte(0x30 + s_int[i]);
      Send_Byte(0x2E);  
    }
    else  
    {    
      Send_Byte(0x30 + s_int[i]);   
    }  
  }
  //delay_ms(100);
  Send_Byte('m');
  Send_Byte('m');
  Send_Byte(' ');
  delay_ms(100);
}
//*************************************************************************
//              ??0??int???
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
//              ??0???????
//*************************************************************************
void Print_Str(uchar *s)
{
    while(*s != '\0')
    {
        Send_Byte(*s++);
    }
}
#endif