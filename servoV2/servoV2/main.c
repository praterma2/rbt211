/*
 * servoV2.c
 *
 * Created: 12/11/2024 2:57:48 PM
 * Author : prate
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define SERVO_PIN PB1 // Define the pin where the servo is connected

// Function to initialize the timer for PWM generation
void timer1_init() {
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Non-inverting mode, Fast PWM
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8, Fast PWM
	ICR1 = 20000; // Set the TOP value for a 50Hz PWM signal
}

// Function to set the servo angle (0 to 180 degrees)
void set_servo_angle(int angle) {
	int pulse_width = 1000 + angle * 20; // Calculate pulse width in microseconds
	OCR1A = pulse_width; // Update the compare match register
}

int main() {
	DDRB |= (1 << SERVO_PIN); // Set servo pin as output
	timer1_init();

	while(1) {
		set_servo_angle(0); // Set servo to 0 degrees
		_delay_ms(1000);

		set_servo_angle(90); // Set servo to 90 degrees
		_delay_ms(1000);

		set_servo_angle(180); // Set servo to 180 degrees
		_delay_ms(1000);
	}
}
