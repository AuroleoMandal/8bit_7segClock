#include "main.h"

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