/*////////////////////////////////////////*/
//Project		:DigitalClock
//Author		:Tho Phi
//File name	: SPI.c
//
//
//
/*////////////////////////////////////////*/
#include <avr/io.h>
#include "SPI.h"

void init_SPI()
{
	//already
}
unsigned char SPI_read()
{
	unsigned char SPIData;
	SPIData = SPDR;
	return SPIData;
}
unsigned char SPI_write(unsigned char WriteData)
{
	SPDR = WriteData;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
