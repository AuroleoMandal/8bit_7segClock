#include "main.h"
#include "port.h"
#include "display.h"
#include "update.h"
#include "timer.h"

#define STATE_CLOCK 0
#define STATE_SET 1
#define STATE_ALARM 2
#define STATE_TIMER 3

#define BUTTON_L 0
#define BUTTON_C 1
#define BUTTON_R 2

tByte clock[6] = {0, 0, 0, 0, 0, 0};

tByte set[6] = {0, 0, 0, 0, 0, 0};
tByte alarm[6] = {0, 0, 0, 0, 0, 0};
tByte timer[6] = {0, 0, 0, 0, 0, 0};

tByte zero[6] = {0, 0, 0, 0, 0, 0};
tByte error[6] = {8, 8, 8, 8, 8, 8};

tByte state = 0;
tByte i = 0;

void timer2_ISR(void);
void timer1_ISR(void);
void copy_time(tByte time1[], tByte time2[]);

void main(void)
{
	writePinP1(7, 0);
	timer2_INIT();
	while(1)
	{
		switch(state)
		{
/*======================================================
======================================================*/
			case STATE_CLOCK:
				display(clock);
			
				if(debounce_readPinP1(BUTTON_L))
					state = STATE_SET;
				if(debounce_readPinP1(BUTTON_C))
					state = STATE_ALARM;
				if(debounce_readPinP1(BUTTON_R))
					state = STATE_TIMER;
				break;

/*======================================================
======================================================*/
			case STATE_SET:
				display(set);
			
			 if(i>=0 && i<6)
				{
					if(debounce_readPinP1(BUTTON_L))
						i++;
					if(debounce_readPinP1(BUTTON_C))
						set[i]++;
					if(debounce_readPinP1(BUTTON_R))
						i--;
				}
				else
				{
					i = 0;
					copy_time(clock, set);
					copy_time(set, zero);
					state = STATE_CLOCK;
				}
				break;
/*======================================================
======================================================*/
			case STATE_ALARM:
				display(alarm);
				if(i>=0 && i<6)
				{
					if(debounce_readPinP1(BUTTON_L))
						i++;
					if(debounce_readPinP1(BUTTON_C))
					{
						alarm[i]++;
					}
					if(debounce_readPinP1(BUTTON_R))
						i--;
				}
				else
				{
					i = 0;
					state = STATE_CLOCK;
				}
				break;
/*======================================================
======================================================*/
			case STATE_TIMER:
				
				if(debounce_readPinP1(BUTTON_C))
				{
					if(TR1)
						timer1_STOP();
					else 
						timer1_INIT();
				}
				if(debounce_readPinP1(BUTTON_R))
				{
					state = STATE_CLOCK;
					copy_time(timer, zero);
				}
			
				display(timer);
				break;

//-------------------------------------------
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
		if(clock == alarm)
			writePinP1(7, 1);
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

void copy_time(tByte time1[], tByte time2[])
{
	for(i=0; i<6; i++)
		time1[i] = time2[i];
}
