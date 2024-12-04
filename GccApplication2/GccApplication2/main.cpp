/*
 * GccApplication2.cpp
 *
 * Created: 12/4/2024 10:54:03 AM
 * Author : prate
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

static inline void initADC0(void) {
	ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS2);                   /* ADC clock prescaler /16 */
	ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}

int main(void)
{
   uint8_t ledValue;
   uint16_t adcValue;
   uint8_t i;

   initADC0();
   //DDRB |= 0x03;
   DDRD |= 0xff;
    while (1) 
    {
		 ADCSRA |= (1 << ADSC);                     /* start ADC conversion */
		 loop_until_bit_is_clear(ADCSRA, ADSC);          /* wait until done */
		 adcValue = ADC;                                     /* read ADC in */
		 /* Have 10 bits, want 3 (eight LEDs after all) */
		 ledValue = (adcValue >> 7);
		 /* Light up all LEDs up to ledValue */
		 PORTD = 0;
		 for (i = 0; i <= ledValue; i++) {
			 PORTD |= (1 << i);
		 }
		 _delay_ms(50);
    }
}

