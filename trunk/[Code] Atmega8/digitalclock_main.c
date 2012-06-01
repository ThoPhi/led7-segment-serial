/*///////////////////////////////////*/
//Project		: Digital clock
//Author		: Tho Phi
//Harware	: Led7Char + Atmega8L
//Date		:14/7/2011
//
/*///////////////////////////////////*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SPI/SPI.h"
#include "LED7/Led7.h"

#define ADC_VREF_TYPE 0x20
//variable
unsigned char led7_data[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

unsigned int CountTimer;
//function
ISR(TIMER1_OVF_vect	)//ngat sau moi 1 ms
{
	TCNT1H = (0xe0);//-8000
	TCNT1L = (0xc0);
	scan_led();

	CountTimer++;
	if(CountTimer >= 10){
		update_buffer();
	}
}
ISR(SPI_STC_vect)
{
	
}
void init_Atmega8();
void delay_us(unsigned long duration)
{
	unsigned long i;
	for(i=0;i<duration;i++);
}
int main(void)
{
unsigned char LedIndex=1;
	init_Atmega8();
	init_SPI();
	init_LED7();
	SELECT_ON;
		SPI_write(0xaa);
	SELECT_OFF;
	while(1){
		//delay_us(800000);
		_delay_ms(1000);
		SELECT_ON;
		
		//SPI_write(0xff);
		//SPI_write(0xff);
		SPI_write(~(led7_data[LedIndex]));
		SELECT_OFF;
		LedIndex = (LedIndex + 1)%10;
		//delay_us(800000);
		_delay_ms(1000);
		
	}
	return 0;
}
void init_Atmega8()
{
	// Declare your local variables here
	
	// Input/Output Ports initialization
	// Port B initialization
	// Func7=In Func6=In Func5=Out Func4=In Func3=Out Func2=Out Func1=In Func0=In 
	// State7=T State6=T State5=0 State4=T State3=0 State2=0 State1=T State0=T 
	PORTB=0x00;
	DDRB=0x2C;
	
	// Port C initialization
	// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTC=0x00;
	DDRC=0x00;
	
	// Port D initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTD=0x00;
	DDRD=0x00;
	
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 1000.000 kHz
	TCCR0=0x02;
	TCNT0=0x00;
	
/*	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: Timer 1 Stopped
	// Mode: Normal top=FFFFh
	// OC1A output: Discon.
	// OC1B output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer 1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;
	
	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: Timer 2 Stopped
	// Mode: Normal top=FFh
	// OC2 output: Disconnected
	ASSR=0x00;
	TCCR2=0x00;
	TCNT2=0x00;
	OCR2=0x00;
	
	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	MCUCR=0x00;
	
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x01;
	*/
	
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 1000.000 kHz
	// Mode: Normal top=FFFFh
	// OC1A output: Discon.
	// OC1B output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer 1 Overflow Interrupt: On
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=0x00;
	TCCR1B=0x02;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;
	
	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: Timer 2 Stopped
	// Mode: Normal top=FFh
	// OC2 output: Disconnected
	ASSR=0x00;
	TCCR2=0x00;
	TCNT2=0x00;
	OCR2=0x00;
	
	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	MCUCR=0x00;
	
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x04;
	
	// Analog Comparator initialization
	// Analog Comparator: Off
	// Analog Comparator Input Capture by Timer/Counter 1: Off
	ACSR=0x80;
	SFIOR=0x00;
	
	// ADC initialization
	// ADC Clock frequency: 1000.000 kHz
	// ADC Voltage Reference: AREF pin
	// Only the 8 most significant bits of
	// the AD conversion result are used
	ADMUX=ADC_VREF_TYPE & 0xff;
	ADCSRA=0x8B;
	
	// SPI initialization
	// SPI Type: Master
	// SPI Clock Rate: 2000.000 kHz
	// SPI Clock Phase: Cycle Half
	// SPI Clock Polarity: Low
	// SPI Data Order: MSB First
	SPCR=0xD0;
	SPSR=0x00;
	
	// Clear the SPI interrupt flag
//#asm
//		in	 r30,spsr
//		in	 r30,spdr
//#endasm
	
	// Global enable interrupts
//#asm("sei")

}
