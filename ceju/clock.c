#include <msp430x14x.h>  
//#include "config.h"  
//#include "clock.h"  
  
/********************系统时钟初始化****************/  
void init_clk(void) //初始化系统时钟  
{  
  uchar i;  
  BCSCTL1 &=~XT2OFF; //打开XT2振荡器  
  BCSCTL2 |=SELM_2+SELS;  
    do  
    {  
      IFG1 &=~OFIFG; //清除错误标志  
      for(i=0;i<0xff;i++); //延时等待  
    }  
  while((IFG1 & OFIFG)!=0);  
  IFG1 &=~ OFIFG;  
}