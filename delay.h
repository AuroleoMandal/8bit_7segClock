#ifndef _DELAY_H
#define _DELAY_H

/*===============================================
delay_hardware(tWord delay)
Hardware timer delay. Delay in nanoseconds. 
Inaccurate due to setup delays. 
Will do for implementations not requiring strict timing.
=================================================*/

void delay_hardware(tWord);

#endif