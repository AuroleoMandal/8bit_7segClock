#include "main.h"
void timer1_INIT(void)
{
	//Configure timer 0
	TMOD = TMOD & 0x0F;
	TMOD = TMOD | 0x10;
	ET1 = 1;
	
	TH1 = 0x3C;
	TL1 = 0xB0;
	
	TF1 = 0;
	TR1 = 1;	
}

void timer1_STOP(void)
{
	TF1 = 0;
	TR1 = 0;
}