#include <msp430x14x.h> 
#include "Config.h" 
#include "1602.c"        
#include "UART.h"

int count = 0;
int flag = 0;

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
    //Print_float(dista_data_sum, 2);
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
  //TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;
  //TACCR0 = 9999;
}  
void InitTimerB(){
  TBCTL=TBSSEL1+ID1+ID0+MC0+TBCLR;//选择1/8SMCLK 增计数 清除TAR
  TBCCTL0=CCIE;//CCR0中断允许 比较模式
  TBCCR0=10000;//时间间隔10ms
}
/************???**************************/  
void main( void )  
{  
    
    WDTCTL = WDTPW + WDTHOLD;                   //?????  
    Clock_Init();
    InitTimerB(); 
    Init_IO(); 
    UART_Init();
    Start_1602();                                //??1602  
    tim_data=0;cnt=0;dista_data=0;                
    delay(1000);   //????  
    uchar string[] = "distance:";  
    LCD1602_write_str(0, 0, string);  
  
    _EINT();                                    //?????  
    while(1)  
    {  
        /*if(flag == 1)
        {
          Print_float(dista_data_sum, 2);
          flag = 0;
        }*/
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
      //dista_data=(tim_data*17/100);             
    dista_f(dista_data);                        //??????  
  }  
  P2IFG&=~BIT1;                                 // P2???????  
}  

#pragma vector=TIMERB0_VECTOR
__interrupt void TimerBINT()
{
  count++;
  if(count>=300)
  {
    Print_float(dista_data_sum, 2);
    //flag = 1;
    count = 0;
  }
}