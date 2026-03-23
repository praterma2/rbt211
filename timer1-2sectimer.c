#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

//create a 2 sec timer using timer1


void timer1_init() {
	// 1. Set CTC mode (WGM12 bit = 1)
	TCCR1B |= (1 << WGM12);
	
	// 2. Set prescaler to 1024 (CS12=1, CS10=1)
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
	// 3. Set OCR1A match value (31249 for 2 seconds)
	OCR1A = 31249;
	
	// 4. Enable Output Compare A Match Interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	// 5. Enable global interrupts
	sei();
}

// Interrupt Service Routine for Timer1 Compare Match A
ISR(TIMER1_COMPA_vect) {
	// Code to run every 2 seconds goes here
	PORTB ^= (1 << PORTB5); // Toggle LED
}

int main(void) {
	// Set LED pin as output if needed
	 DDRB |= (1 << DDB5);
	
	timer1_init();
	
	while (1) {
		// Main loop
	}
}
