#include<avr/io.h>
#define F_CPU 8000000ul
#include<util/delay.h>

#define motor PB0

void ADC_init(void);
unsigned int ADC_read(unsigned char);

void delay(unsigned int value1)
{
   	for (int i=0;i<value1;i++)
   	_delay_us(1);
}


// ------------------------------------------------
int main(void)
{
	uint16_t value;
	DDRB=0xFF;
	ADC_init(); // Initialization of ADC
	while(1)
	{
		value=ADC_read(0);
		if(value<1)
		value=0;
		
		PORTB=0x01;
		delay(value);
		PORTB=0x02;
		delay(value);
		PORTB=0x04;
		delay(value);
		PORTB=0x08;
		delay(value);
	}
}
//------------------------------------------------

void ADC_init(void) // Initialization of ADC
{
	ADMUX|=(1<<REFS0); // AVcc with external capacitor at AREF
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// Enable ADC and set Prescaler division factor as 128
}

unsigned int ADC_read(unsigned char ch)
{
	ch= ch & 0b00000111; // channel must be b/w 0 to 7
	ADMUX |= ch; // selecting channel
	ADCSRA|=(1<<ADSC); // start conversion
	while(!(ADCSRA & (1<<ADIF))); // waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF); // clearing of ADIF, it is done by writing 1 to it
	return (ADC);
}