/*////////////////////////////////////////*/
//Project		:DigitalClock
//Author		:Tho Phi
//File name	: LED7.h
//
//
//
/*////////////////////////////////////////*/
#ifndef _LED7_H_
#define _LED7_H_
//macro
#define SELECT_ON	(PORTB &= ~(1<<2))
#define SELECT_OFF	(PORTB |= (1<<2))
//variable

//function
void init_LED7();
void scan_led();
void update_buffer();

#endif
