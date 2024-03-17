#include "main.h"
void delay_hardware(tWord delay)
{
	tWord loadValue;
	
	//Configure timer 0
	TMOD = TMOD & 0xF0; 
	TMOD = TMOD | 0x01;
	ET0 = 0;
	
	loadValue = 0xFFFF - delay;
	
	TH0 = loadValue / 0xFF;
	TL0 = loadValue % 0xFF;
	
	TF0 = 0;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
}