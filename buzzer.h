#include <avr/io.h>
#include <avr/interrupt.h>

#define ON  1
#define OFF 0

volatile int state = OFF;
volatile int tone_index = 0;

char TCNT0s[16] = {
	17, 31, 43, 55, 66, 77, 87, 97, 100, 116, 122, 129, 137, 143, 150, 155, 161
};
// (묵음), 도, 도#, 레, 레#, 미, 파, 파#, 솔, 솔#, 라, 라#, 시, 도, 도#, 레, 레#, 미

ISR(TIMER0_OVF_vect) {
	// set tone (set count)
	TCNT0 = TCNT0s[tone_index];

	// switch state
	if (state == OFF) {
		PORTB |= 0x10;
		state = ON;
	} else {     
		PORTB &= 0xEF;
		state = OFF;
	}
}


void init_buzzer() {
	DDRB |= 0x10;
	TCCR0 = 0x03; // 32분주
	TIMSK = 0x01; // Overflow
	sei(); // global interrupt enable
}


void simple_test() {
	int count = 1000;
	while (count--) {
		PORTB = 0x10;
		_delay_ms(1);
		PORTB = 0x00;
		_delay_ms(1);
	}
}
