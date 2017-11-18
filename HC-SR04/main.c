#include <msp430x14x.h>
#include "Config.h"
#include "HC-SR04.h"
#include "1602.h"
#include "UART.h"

char SR_Temp[];

void main(void)
{
  WDT_Init();
  uchar i;
  long SR_Long;
  BCSCTL1 &= ~XT2OFF;
  do
  {
    IFG1 &= ~OFIFG;
    for(i = 0xff;i>0;i++);
  }while((IFG1 & OFIFG));
  
  BCSCTL2 |= SELM_2 + SELS;
  
  SR_Init();
  Port_Init();
  LCD_init();
  
  while(1)
  {
    SR_Start();
    SR_Long = SR_DoTrans();
    
    SR_Temp[0] = SR_Long/100 + 0x30;
    SR_Temp[1] = (SR_Long/10)%10 + 0x30;
    SR_Temp[2] = '.';
    SR_Temp[3] = SR_Long%10 + 0x30;
    SR_Temp[4] = ' ';
    SR_Temp[5] = 'c';
    SR_Temp[6] = 'm';
    
    void LCD_clear();
    
    for(i = 0;i<7;i++)
    {
      LCD_write_char(4+i, 1, SR_Temp[i]);
    }
  }
}
