/*
 * blinkPWMV1.c
 * used to blink and dim with a PWM an led
 * Created: 12/9/2024 10:26:14 AM
 * Author : prate
 */ 


// ------- Preamble -------- //

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define DELAY 3

volatile uint8_t ovrFloCt = 0;
volatile uint8_t on = 1;
volatile  uint8_t brightnessB;

// -------- Functions --------- //
static inline void initTimer0(void) {
	/* clock must be /64 or more for ISR timing */
	TCCR0B |= (1 << CS01) | (1 << CS00);
	/* both output compare interrupts */
	TIMSK0 |= (1 << OCIE1B);
	TIMSK0 |= (1 << TOIE0);                 /* overflow interrupt enable */
	sei();
}

ISR(TIMER0_OVF_vect) {
	//upon overflow do this
	if(on == 1){
		PORTB |= 32;
	}else{
		PORTB &= ~(32);
	}
	OCR0B = brightnessB;
	ovrFloCt++;
	if(ovrFloCt == 100){
		if(on == 1){
			on = 0;
		}else{
			on = 1;
		}
		ovrFloCt = 0;
	}
}


ISR(TIMER0_COMPB_vect) {
	//upon compare do this
	PORTB &= ~(32);                   /* turn off high four LEDs */
}

int main(void) {
	// -------- Inits --------- //

	
	DDRB = 0xff;
	initTimer0();
	//brightnessA =18;
	brightnessB = 12;
	// ------ Event loop ------ //
	while (1) {


		}                                                  /* End event loop */
		return 0;                            /* This line is never reached */
	}