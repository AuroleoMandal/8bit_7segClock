#include "main.h"
#include "port.h"
#include "display.h"
#include "update.h"
#include "timer.h"

#define STATE_CLOCK 0
#define STATE_SET 1
#define STATE_ALARM 2
#define STATE_TIMER 3

tByte clock[6] = {0, 5, 6, 5, 3, 2};

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
		if(state == STATE_CLOCK)
		{
			if (debounce_readPinP1(0) == 1)
				state = STATE_SET;
			if (debounce_readPinP1(1) == 1)
				state = STATE_ALARM;
			if (debounce_readPinP1(2) == 1)
				state = STATE_TIMER;
		}
		
		



		
		switch(state)
		{
			case STATE_CLOCK:
				display(clock);
				break;
			case STATE_SET:
				display(set);
				break;
			case STATE_ALARM:
				display(alarm);
				break;
			case STATE_TIMER:
				
				if(debounce_readPinP1(1))
				{
					if(TR1 == 1)
						timer1_STOP();
					else 
						timer1_INIT();
				}
				if(debounce_readPinP1(2))
					state = STATE_CLOCK;

			
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
