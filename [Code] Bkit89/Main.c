/////////////////////////////////////
//Project 	: Digital Clock
//Author	: ThoPhi
//MCU		: 89v51rb2	(BKIT89)
//
//
/////////////////////////////////////
#include <reg51f.h>
void init()
{
	P0 = 0;
	P1 = 0;
	P2 = 0;
	P3 = 0;	
}
void main()
{
	init();

	while(1);
}
