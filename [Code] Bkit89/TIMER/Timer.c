
#include "Timer.h"



unsigned char value_display;
unsigned int  counter0;
unsigned int counter1;

void init_timer0()
{
	IE &= ~(0x02);// enable timer 0
	IE |= 0x02;
	
	TMOD &= ~(0x01);// setup mode for timer 0
	TMOD |= 0x01;	

	TH0 = (-10000/256); 
	TL0 = (-10000%256);

	TR0 = 1;//start timer0	
	
}

void init_timer1()
{
	IE &= ~(0x08);// enable timer 0
	IE |= 0x08;
	
	TMOD &= ~(0x10);// setup mode for timer 0
	TMOD |= 0x10;	

	TH1 = (-10000/256); 
	TL1 = (-10000%256);

	TR1 = 1; //start timer1
	
}

void start_timer0()
{
	TR0 = 1;
}

void start_timer1()
{
	TR1 = 1;
}

void stop_timer0()
{
	TR0 = 0;
}

void stop_timer1()
{
	TR1 = 0;
}

void timer0_isr() interrupt 1
{
	TR0 = 0;//stop timer 0

	// reinitialize
	TH0 = (-1000/256); 
	TL0 = (-1000%256);

	//Add your code here
	
//	scan_led_matrix();

	TR0 = 1;//start timer 0
}
void timer1_isr() interrupt 3
{
	
	TR1 = 0;//stop timer 1

	// reinitialize
	TH1 = (-1000/256); 
	TL1 = (-1000%256);

	//Add your code here

	
	if(counter1!= 0)
	{
		counter1--;
	}

	TR1 = 1;//start timer 1
}
void delay_ms(unsigned int duration)
{
	counter1 = duration;
	while(counter1 !=0)
	{
	}
}
