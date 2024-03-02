#include "main.h"
#include "port.h"
#include "display.h"
#include "update.h"
#include "timer.h"

tByte clock[6] = {0, 5, 9, 5, 3, 2};
tByte timer[6] = {0, 0, 0, 0, 0, 0};

void timer2_ISR(void);
void timer1_ISR(void);

void main(void)
{
	timer2_INIT();
	timer1_INIT();
	while(1)
	{
		if(readPinP1(0) == 1)
		{
			display(clock);
		}
		else
			display(timer);
	}
}
/*======================================
Timer2_ISR() Interrupt Service Routine increases second by 1 (clock[0]++)
========================================*/
static tByte second_count = 0;

void timer2_ISR(void) interrupt INTERRUPT_T2
{
	TF2 = 0;
	second_count ++;
	if(second_count == 20)
	{
		second_count = 0;
		increment_second(clock);
	}
}

static tByte second_count1 = 0;

void timer1_ISR(void) interrupt INTERRUPT_T1
{
	TF1 =0;
	second_count1++;
		if(second_count1 == 20)
	{
		second_count1 = 0;
		increment_second(timer);
	}
}