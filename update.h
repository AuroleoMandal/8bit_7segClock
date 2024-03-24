#ifndef _UPDATE_H
#define _UPDATE_H

/*===============================================
timer2_INIT() - Initiates Timer 2 
as a 16-bit auto reload timer
=================================================*/

void timer2_INIT(void);

void clock_controlledIncrement(tByte[], tByte);
	
/*===============================================
increment_second() - Function to increase second count 
by one and modify minute and hour count accordingly
=================================================*/

void increment_second(tByte[]);
void increment_minute(tByte[]);
void increment_hour(tByte[]);

#endif