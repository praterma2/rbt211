/*
 * motorDriveV1.c
 *
 * Created: 3/31/2025 11:12:37 AM
 * Author : prate
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//define global variables
volatile uint8_t brightnessA;
volatile uint8_t phase = 0;
volatile int ovrFloCt = 0;

//setup for timer
static inline void initTimer0(void){
	TCCR0B |= (1 << CS01 | 1 << CS00);
	TIMSK0 |= (1 << OCIE1B);
	TIMSK0 |= (1<< TOIE0);
	sei();
}

ISR(TIMER0_OVF_vect){
	/*if(on == 1){
		PORTB |= 32;
		} else {
		PORTB &= ~(32);
	}*/
	PORTB |= 32;
	//OCR0B = brightnessA;
	ovrFloCt++;
	if(ovrFloCt == 1600){
		if (phase == 0){
			OCR0B = 128;
			phase = 1;
		} else if (phase == 1){
			OCR0B = 191;
			phase = 2;
		} else if (phase == 2){
			OCR0B = 64;
			phase = 3;
		} else if (phase == 3){
			OCR0B = 255;
			phase = 0;
		}
		ovrFloCt = 0;
	}
}

ISR(TIMER0_COMPB_vect){
	PORTB &= ~(32);
}

int main(void)
{
    DDRB |= 32;
	
	initTimer0();
	brightnessA = 25;
    while (1) 
    {
    }
	
}



