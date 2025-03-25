/*
 * blinkPWNClassV1.c
 * on board led to blink at 30% duty cycle
 * 
 * Created: 12/9/2024 3:52:05 PM
 * Author : prate
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

//define global variables
volatile uint8_t brightnessA;
volatile uint8_t on = 1;
volatile uint8_t ovrFloCt = 0;

//setup for timer
static inline void initTimer0(void){
	TCCR0B |= (1 << CS01 | 1 << CS00);
	TIMSK0 |= (1 << OCIE1B);
	TIMSK0 |= (1<< TOIE0);
	sei();
}

ISR(TIMER0_OVF_vect){
	//on overflow do this
	if(on == 1){
		PORTB |= 32;
	} else {
		PORTB &= ~(32);
	}
	
	OCR0B = brightnessA;
	ovrFloCt++;
	if(ovrFloCt == 200){
		if (on == 1){
			on = 0;
		} else {
			on = 1;
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
	brightnessA = 255;
    while (1) 
    {
    }
	
}

