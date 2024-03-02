#ifndef _MAIN_H
#define _MAIN_H

#include <reg52.h>

#define OSC_FREQ (12000000UL)
#define OSC_PER_INST (12)

typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tLong;

//Interrupts
#define INTERRUPT_T0 1
#define INTERRUPT_T1 3
#define INTERRUPT_T2 5

#endif