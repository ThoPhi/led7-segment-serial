/*////////////////////////////////////////*/
//Project		:DigitalClock
//Author		:Tho Phi
//File name	: Led7.c
//
//
//
/*////////////////////////////////////////*/
#include <avr/io.h>
#include "Led7.h"
#include "../SPI/SPI.h"

//macro

//variable
//unsigned char led7_data[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char ScanBuffer[4] = {0x00, 0x00, 0x00, 0x00};
unsigned char Year,Month,Day, Hour,Minute,Second, Tick;
//function
void init_LED7()
{
	Hour = 0;
	Minute = 0;
	Second = 0;
	Tick = 0;
}
void scan_led()
{
	//unsigned char i;
	SELECT_ON;
	SPI_write(ScanBuffer[3]);
	SPI_write(ScanBuffer[2]);
	SPI_write(ScanBuffer[1]);
	SPI_write(ScanBuffer[0]);
	SELECT_OFF;
}
void clock_tick()
{
	Tick++;
	if(Tick>=100){
		Tick = 0;
		Second ++;
		if(Second >=60){
			Second = 0;
			Minute ++;
			if(Minute >= 60){
				Minute =0;
				Hour++;
				if(Hour >= 24){
					Hour = 0;
					Day ++;
					if((Month == 1)| (Month == 3)|(Month == 5)|(Month == 7)|(Month == 8)|(Month == 10)|(Month == 12)){
						if(Day >=31){
							Day = 0;
							Month ++;
						}
					}
					else if((Month == 4)|(Month == 6)|(Month == 9)|(Month == 11)){
						if(Day>= 30){
							Day =0;
							Month ++;
						}
					}
					else if (Month ==2){
						if((Year %4) == 0){//nam nhuan
							if(Day >=29){
								Day = 0;
								Month++;
							}
						}
						else {
							if(Day >= 28){
								Day = 0;
								Month ++;
							}
						}
					}
					if(Month >= 13) {
						Month =0;
						Year ++;		//happy new year :D
					}
				}
					
			}
		}
	}		
}
void update_buffer()
{
	clock_tick();
	ScanBuffer[3] = Hour/10;
	ScanBuffer[2] = Hour%10;
	ScanBuffer[1] = Minute/10;
	ScanBuffer[0] = Minute%10;
}

