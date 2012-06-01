
#ifndef _TIMER_H_
#define _TIMER_H_

				 
#include <REG51F.H>



extern unsigned char value_display;
extern unsigned int  counter0;
extern unsigned int counter1;

// function 
void init_timer0();	  //init timer 0, interrupt after 10ms
void init_timer1();	  //init timer 1, interrupt after 10ms

void start_timer0();
void start_timer1();

void stop_timer0();
void stop_timer1();

void delay_ms(unsigned int duration);//using timer1 to delay duration ms

#endif