#include "main.h"
#include "update.h"

void timer2_INIT(void)
{
	EA = 1;
	
	RCAP2H = 0x3C;
	TH2    = 0x3C;
	RCAP2L = 0xB0;
	TL2    = 0xB0;
	
	ET2 = 1;

	TF2 = 0;
	TR2 = 1;
}

void clock_controlledIncrement(tByte clock[], tByte i)
{
	switch(i)
	{
		case(0):
			clock[0]++;
			if(clock[0] == 10)
				clock[0] = 0;
			break;
		case(1):
			clock[1]++;
			if(clock[1] == 6)
				clock[1] = 0;
			break;
		case(2):
			clock[2]++;
			if(clock[2] == 10)
				clock[2] = 0;
			break;
		case(3):
			clock[3]++;
			if(clock[3] == 6)
				clock[3] = 0;
			break;
		case(4):
			clock[4]++;
			if(clock[4] == 10)
				clock[4] = 0;
			break;
		case(5):
			clock[5]++;
			if(clock[5] == 3)
				clock[5] = 0;
			break;
	}
}
/*===============================================
increment_second() - Function to increase second count 
by one and modify minute and hour count accordingly
=================================================*/

void increment_second(tByte clock[])
{
	clock[0]++;
	if(clock[0]>=10)
	{
		clock[0] = 0;
		clock[1]++;
		if(clock[1]>=6)
		{
			clock[1] = 0;
			increment_minute(clock);
		}
	}
}

void increment_minute(tByte clock[])
{
	clock[2]++;
	if(clock[2]>=10)
	{
		clock[2] = 0;
		clock[3]++;
		if(clock[3]>=6)
		{
			clock[3] = 0;
			increment_hour(clock);
		}
	}
}

void increment_hour(tByte clock[])
{
	clock[4]++;
	if(clock[5]>=2 && clock[4]>=4)
	{
		clock[4] = 0;
		clock[5] = 0;
	}
	else if(clock[4]>=10)
	{
		clock[4] = 0;
		clock[5]++;

	}
}