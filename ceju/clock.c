#include <msp430x14x.h>  
//#include "config.h"  
//#include "clock.h"  
  
/********************ϵͳʱ�ӳ�ʼ��****************/  
void init_clk(void) //��ʼ��ϵͳʱ��  
{  
  uchar i;  
  BCSCTL1 &=~XT2OFF; //��XT2����  
  BCSCTL2 |=SELM_2+SELS;  
    do  
    {  
      IFG1 &=~OFIFG; //��������־  
      for(i=0;i<0xff;i++); //��ʱ�ȴ�  
    }  
  while((IFG1 & OFIFG)!=0);  
  IFG1 &=~ OFIFG;  
}