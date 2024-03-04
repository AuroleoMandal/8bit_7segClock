#include "main.h"
#include "port.h"
#include "display.h"
#include "update.h"
#include "timer.h"

tByte clock[6] = {0, 5, 9, 5, 3, 2};

tByte set[6] = {1, 1, 1, 1, 1, 1};
tByte alarm[6] = {2, 2, 2, 2, 2, 2};
tByte timer[6] = {0, 0, 0, 0, 0, 0};

tByte error[6] = {8, 8, 8, 8, 8, 8};

tByte state = 0;

void timer2_ISR(void);
void timer1_ISR(void);
tByte stateChange(tByte);

void main(void)
{
	timer2_INIT();
	while(1)
	{
		if(state == 0)
		{
			if (debounce_readPinP1(0) == 1)
				state = 1;
			if (debounce_readPinP1(1) == 1)
				state = 2;
			if (debounce_readPinP1(2) == 1)
				state = 3;
		}
		
		


		if (state == 3 && debounce_readPinP1(3) == 1)
		{
			timer1_INIT();
		}
		switch(state)
		{
			case 0:
				display(clock);
				break;
			case 1:
				display(set);
				break;
			case 2:
				display(alarm);
				break;
			case 3:
				display(timer);
				break;
			default:
			display(error);
		}
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
	TF1 = 0;
	
	TH1 = 0x3C;
	TL1 = 0xB0;
	
	second_count1++;
	
	if(second_count1 == 20)
	{
		second_count1 = 0;
		increment_second(timer);
	}
}
