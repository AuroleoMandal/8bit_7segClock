#include "main.h"
void delay_hardware(void)
{
	//Configure timer 0
	TMOD = TMOD & 0xF0;
	TMOD = TMOD | 0x01;
	ET0 = 0;
	
	TH0 = 0x3C;
	TL0 = 0xB0;
	
	TF0 = 0;
	TR0 = 1;
	
	while(TF0 == 0);
	TR0 = 0;
}