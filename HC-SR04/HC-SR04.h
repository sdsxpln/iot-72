
#include "msp430x14x.h"
#define Trig_H P2OUT |= BIT4
#define Trig_L P2OUT &= ~BIT4 //trig->P2^4, echo->P1^1;
#define unit unsigned int
#define uchar unsigned char
#define CPU (8000000)
#define delay_us(x) (__delay_cycles((double)x*CPU/1000000.0))
#define delay_ms(x) (__delay_cycles((double)x*CPU/1000.0))
#define delay_s(x) (__delay_cycles((double)x*CPU/1.0))

void SR_Init(void);
void SR_DelayNus(unit n);
void SR_Start(void);
long SR_DoTrans();

unit TB_CCR0, TB0_CCR0, TB1_CCR0;
uchar SR_Flag = 0;

void SR_Init(void)
{
	Trig_L;
	P2DIR |= BIT4;
	
	P1SEL |= BIT1;
	P1DIR &= ~BIT1;
	
	TACTL = TASSEL_2 + TACLR + ID_3;
	CCTL0 = CM_1 + CCIS_0 + CAP + CCIE;
	
	TBCTL |= TBSSEL_2 + ID_3 + TBCLR;
	TBCCTL0 |= CM_1 + CCIS_1 + SCS +CAP + CCIE;
	
	_EINT();
}

void SR_DelayNus(unit n)
{
	unit i;
	for(i = 0;i<n;i++)
		delay_us(1);
}

void SR_Start(void)
{
	Trig_L;
	SR_DelayNus(20);
	Trig_H;
	SR_DelayNus(20);
	Trig_L;
}

long SR_DoTrans()
{
	long Temp;
	SR_Start();
	while(!(P1IN&BIT7));
	
	TBCTL |= MC_2 + TBCLR;
	TB1_CCR0 = TBR;
	while(P1IN&BIT7);
	
	TB_CCR0 = TBR;
	TBCTL &= ~MC_2;
	Temp = (long)((TB_CCR0-TB1_CCR0)*340.0/2);
	Temp = Temp/1000;
	
	delay_ms(700);
	return Temp;
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TimerA0Int(void)
{
	if(TACCTL0&CM_1)
	{
		TB0_CCR0 = TACCR0;
		TACCTL0 &= ~CM_1;
		TACCTL0 |= CM_2;
		TACTL |= MC_2;
	}
	else
	{
		TB1_CCR0 = TACCR0;
		TACCTL0 &= ~CM_2;
		TACCTL0 |= CM_1;
		TACTL |= MC_0;
		TB0_CCR0 = TB1_CCR0-TB0_CCR0;
		SR_Flag = 1;
	}
}
