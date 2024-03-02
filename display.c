#include "main.h"
#include "delay.h"
/*==============================================================
num[] array prints the digit corresponding to array index
to Port 2

activePin[] gives the activation signal to Port 3
corresponding to the digit currently to be printed to display
==============================================================*/
const tByte num[10] = {0xC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

const tByte activePin[6] = {0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void display(tByte clock[])
{
	tByte i;
		for(i = 0; i<6; i++)
		{
			P3 = activePin[i];
			P2 = num[clock[i]];
			delay_hardware();
		}
}