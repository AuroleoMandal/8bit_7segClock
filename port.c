#include "main.h"
#include "delay.h"
void writePinP1(const tByte PIN, const bit VALUE)
{
	tByte p = 0x01;
	p <<= PIN;
	if(VALUE == 1) //Write 1 at pin
	{
		P1 = P1 | p;
	}
	else           //Write 0 at pin
	{
		p = ~p;
		P1 = P1 & p;
	}
}

//Read from a pin at P1
bit readPinP1(const tByte PIN)
{
	tByte p = 0x01;
	p <<= PIN;
	
	writePinP1(PIN,1); //Setup for reading
	return (P1 & p);
}




tByte switchStatus[8] = {0, 0, 0, 0, 0, 0, 0, 0};

bit debounce_readPinP1(const tByte PIN)
{
	bit switchPressed = 0;
	if(readPinP1(PIN) == 0 && switchStatus[PIN] == 0)
	{
		delay_hardware(10000);
		if(readPinP1(PIN) == 0)
		{
			switchStatus[PIN] = 1;
		}
	}
	if(readPinP1(PIN) == 1 && switchStatus[PIN] == 1)
	{
		switchStatus[PIN] = 0;
		switchPressed = 1;
	}

	return switchPressed;
}