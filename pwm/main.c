#include "msp430x14x.h"
#include "Config.h"
#include <stdlib.h>
#include <string.h>
int flag=0;
uchar key;
unsigned int a=5;
//unsigned int b=5;
uchar string[3], j = 0;
void TIMERA_Init(void)                                   //??????,???0XFFFF????
{
    TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK????,8??,?????? 
    
}
void set(){
   switch(a)
       {
      
       case 1:  {
               TACCR0=9999;
               CCR1=5000;
               
                }
               break;
       case 2:  {
               TACCR0=4999;
               CCR1=2500;
               
                }
               break; 
       case 3: {
               TACCR0=3332;
               CCR1=1500;
              
                }
               break;
       case 4:  {
               TACCR0=2499;
               
                }
               break;
       case 5: {
               TACCR0=2000;
               
                }
               break;
       case 6: {
               TACCR0=1666;
              
                }
               break;
       case 7:  {
               TACCR0=1428;
              
                }
               break;
       case 8:  {
               TACCR0=1250;
                 
                }
               break;
       case 9 : {
               TACCR0=1111;
              
                }
               break;
       case 10: {
               TACCR0=999;
              
                }
               break;
       /*default:{
               TACCR0=2000;
               a = 5;
       }break; */ 
       }
}
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
#pragma vector=UART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  uchar data;
  data=U0RXBUF;  
  if(data == 'a')
    P6OUT = 0x00;
  a = data-0x30;
  if(a != 0)
    set();
}

#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch(TAIV)                                  //?????????
  {
  case 2:break;
  case 4:break;
  case 10:flag++;break;
  }
}
void KeyPort_init()
{

  P1SEL = 0x04;                   //P1??IO??
  P1DIR = 0x04;                   //P10~P13????,??????????
 
}

void Key_Scan(void) 
{
  uchar key_check;
  uchar key_checkin;
  key_checkin=KeyPort;          	//??IO???,????????
  key_checkin&= 0x0F;          		//??IO???,????????
    if(key_checkin!=0x0F)            	//IO?????????????
      { 
        delay_ms(10); 
        key_check=KeyPort ;
        switch (key_check & 0x0F)
              {
                case 0x0E: 
                  {                   
                    key=1;
                  }
                  break;
                case 0x0D:{  
                    key=2;
                  }
                  break;
              }      
      }
    else
     {
       key=0xFF;        
     }
}
void main(void)
{
      WDTCTL = WDTPW + WDTHOLD;
      TIMERA_Init(); 
      Clock_Init();
      UART_Init();
      KeyPort_init();
      P6DIR=0xff;
      TACCTL1 = OUTMOD_7;
       _EINT();
      CCR1=500;
      TACCR0 = 2000;
      while(1)
      {
       Key_Scan(); 
          if(key!=0xff)
          {     
            switch(key)
          {
        case 1:
          {  
            while((P1IN & 0x01)!=0)
             {
               
             }
            delay_ms(300); 
            a--;
            set();
          }
          break;
        case 2:
          {
            
            while((P1IN & 0x02)!=0)
             {
                
             }
             delay_ms(300); 
             a++;   
             set();
          }
          break;        
        }
       
       }
      
      }
}