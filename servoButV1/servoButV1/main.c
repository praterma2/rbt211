/*
 * servoButV1.c
 *
 * Created: 12/18/2024 4:03:18 PM
 * Author : prate
 */ 

/*
 * classButtonPush.cpp
 *
 * Created: 12/8/2022 11:02:55 AM
 * Author : prate
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Datasheet 102 datasheet says 500-2400
#define PULSE_MIN	999U
#define PULSE_MAX	5000U
#define PULSE_MID	2899U

#define TOP_VALUE 39999//50 HZ 39999


int main(void)
{//TIMSK1 |= (1 << TOIE1) | (1 << OCIE1A);
	ICR1 = TOP_VALUE;
	TCCR1A |= (1 << WGM11);
	TCCR1A |= (1 << COM1A1); // Sets OC1A as direct output PB1
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler of 8
	
	DDRB |= (1 << PB1);
	DDRD |= (1 << PD6);
	
	OCR1A = PULSE_MIN;
	
    //input B0
	DDRB & ~(1 << PB0);
	
	
	DDRD &= ~(192);
	
	//PULLUP
	PORTB |= (1 << PB0);
	PORTD |= (192);
	
    while (1) 
    {
		if((PINB & (1 << PINB0)) == 0){
			//go low
			OCR1A = PULSE_MIN;
		} else if(PIND & (1 << PIND7)){
			//go med
			OCR1A = PULSE_MID;
		} else if(PIND & (1 << PIND6)){
			//go high
			OCR1A = PULSE_MAX;
		}
    }
}

