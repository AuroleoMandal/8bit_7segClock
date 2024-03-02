#include "main.h"
#include "port.h"
#include "display.h"
#include "update.h"

tByte clock[6] = {0, 5, 9, 5, 3, 2};
tByte cock[6] = {0, 0, 0, 0, 0, 0};

void Timer2_ISR(void);

void main(void)
{
	timer2_INIT();
	while(1)
	{
		if (readPinP1(0) == 1)
		{
			display(cock);
		}
		else
		{
			display(clock);
		}
	}
}
/*======================================
Timer2_ISR() Interrupt Service Routine increases second by 1 (clock[0]++)
========================================*/
static tByte second_count = 0;

void Timer2_ISR(void) interrupt INTERRUPT_T2
{
	TF2 = 0;
	second_count ++;
	if(second_count == 20)
	{
		second_count = 0;
		increment_second(clock);
	}
}