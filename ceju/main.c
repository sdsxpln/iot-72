#include <msp430x14x.h> 
#include "Config.h" 
#include "1602.c"  
#include "clock.c"            
#include "UART.h"

#define uchar unsigned char  
#define uint unsigned int  
/***************????*******************************/   
#define trig_H P2OUT|=BIT0 //????  
#define trig_L P2OUT&=~BIT0  
#define echo P2IN & BIT1 //????  
  
uint cnt;  
unsigned long int tim_data,dista_data,dista_data_all,dista_data_sum;   
/***************??*******************************/   
void delay(uint n)  
{   
  uchar i;  
  for(;n>0;n--)  
  for(i=10;i>0;i--);  
}  
/********************??,????????***************/   
void dista_f(unsigned long int distance_data)  
{  
  dista_data_all=dista_data_all+distance_data;  
  cnt=cnt+1;  
  if(cnt==16)   
  {  
    cnt=0;  
    dista_data_sum=dista_data_all>>4;  
    dista_data_all=0;  
      LCD1602_write_double(13,1,dista_data_sum);   //?1602?????   
     LCD1602_write_char(14,1,'m');  
      LCD1602_write_char(15,1,'m');  
  
  }  
}  
  
/**************???io?********************/  
void Init_IO()  
{  
  P2DIR = 0XFD;  
  P2OUT |= 0XFF;  
  P2IE |= BIT1;                               //??P2????  
  P2IES &=~BIT1;                              //????????  
}  
  
/**************??????******************/  
void Init_Timer()  
{  
  TACTL|=TACLR+TASSEL_2+ID_3;                   //???A???   
}  
/************???**************************/  
void main( void )  
{  
    WDTCTL = WDTPW + WDTHOLD;                   //?????  
    init_clk();                                 //?????  
    Init_IO();                                  //???IO  
    Start_1602();                                //??1602  
    tim_data=0;cnt=0;dista_data=0;                
    delay(1000);   //????  
    uchar string[] = "distance:";  
    LCD1602_write_str(0, 0, string);  
  
    _EINT();                                    //?????  
    while(1)  
    {  
        trig_H;                                   //?????  
        delay(2);                                 //??15us  
        trig_L;                                   //?????  
        delay(50);                                //????  
        while(echo);                              //????  
        delay(1000);                              //????  
    }  
}  
/*****************************P2???*******************/  
#pragma vector=PORT2_VECTOR  
__interrupt void port_init(void)  
{  
  if(echo)                                      //?????  
  {  
    TACTL|=TACLR+TASSEL_2+ID_3;  
    TACTL|=MC_2;                                //?????,?????????   
    P2IES|=BIT1;                                //??P2??????  
  }  
  else                                          //?????  
  {  
    TACTL=0;                                    //????,????  
    TACTL|=TASSEL_2+ID_3;  
    P2IES&=~BIT1;                               //??P2??????       
    tim_data=TAR;                               //????   
   dista_data=(tim_data*1000/58);              //?????(??=us/58)   
   //   dista_data=(tim_data*17/100);             
    dista_f(dista_data);                        //??????  
  }  
  P2IFG&=~BIT1;                                 // P2???????  
}  