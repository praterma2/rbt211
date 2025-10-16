/*
 * intBlinkV1.c
 * blink pin b5 for 1.048576 sec
 * 1/160000000 * 65536 * 256 = 1.048576 sec
 * Created: 10/16/2025 10:34:44 AM
 * Author : prate
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

static inline void initTimer1(void){
	//set prescalar to 256
	TCCR1B |= 4;
	//set to ovrflo 1
	TIMSK1 |= 1;
	//engage
	sei();
}

ISR(TIMER1_OVF_vect){
	//toggle pin b5
	PORTB ^= 32;
}
int main(void)
{
    DDRB |= 32;
	initTimer1();
    while (1) 
    {
    }
}

