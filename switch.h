#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void (*interrupt_handler4)() = 0;
void (*interrupt_handler5)() = 0;

ISR(INT4_vect) {
	cli();
	if (interrupt_handler4 != 0) {
		interrupt_handler4();
	}
	_delay_ms(300); 
	// 스위치가 눌렸을 때, bouncing 문제를 피하기 위한 방법(debouning)
	// 0.1초동안 delay를 줘서 그 동작 사이에 오류가 나는 것을 막아줌
	sei();
}

ISR(INT5_vect) {
	cli();
	if (interrupt_handler5 != 0) {
		interrupt_handler5();
	}
	_delay_ms(300); 
	sei();
}

void init_switch() {
	DDRE &= 0b11001111; // set PE4 and PE5 for input
	EICRB = 0b00001010; // external interrupt control register: falling edge for INT4 and INT5
	EIMSK = 0b00110000; // INT4, INT5 external interrupt enable
	SREG |= 0b10000000; // SREG bit7 = I (Interrupt Enable) // same as sei()
}

void set_interrupt_handler(int n, void (*handler)()) {
	switch(n) {
		case 4: interrupt_handler4 = handler; break;
		case 5: interrupt_handler5 = handler; break;
	}
}
