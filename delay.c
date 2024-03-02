#include "main.h"
void delay_hardware(void)
{
	//Configure timer 0
	TMOD = TMOD & 0xF0;
	TMOD = TMOD | 0x01;
	ET0 = 0;
	
	TH0 = 0xD8;
	TL0 = 0xF0;
	
	TF0 = 0;
	TR0 = 1;
	
	while(TF0 == 0);
	TR0 = 0;
}