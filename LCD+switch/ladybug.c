#define F_CPU 16000000UL //AVRÄ¨¿¡ »ç¿ëÁßÀÎ CPU Å¬·°½Ã°£À» 16MHz·Î ¼³Á¤
#include <avr/io.h>
#include <util/delay.h>
#include "switch.h"


int mod = 0; // 0 : ²ô±â | 1 : ÄÑ±â | 2 : ¹Ý!Â¦!¹Ý!Â¦! | 3 :¹Ù¾È~Â¦ ¹Ù¾È~Â¦ | 4 : (´Ù°°ÀÌ) ¹ÝÂ¦¹ÝÂ¦!!

void switch_handler4() {
	mod ++;
	if (mod == 5)
		mod = 1;
}

void switch_handler5() {
    if (mod == 0)
		mod = 1;
	else
		mod = 0;
}

int main(void)
{
	PORTA=0x00;
	PORTB=0x00;
	PORTC=0x00;
	PORTD=0x00;
	DDRA=0xff;
	DDRB=0xff;
	DDRC=0xff;
	DDRD=0xff;
	DDRE=0x00;
	

	init_switch();	
	set_interrupt_handler(4, switch_handler4);
	set_interrupt_handler(5, switch_handler5);

	while(1)
	{
		if(mod == 0)
		{
			PORTA=0x00;
		    PORTB=0x00;
		    PORTC=0x00;
		    PORTD=0x00;
		}
		else if(mod == 1)
		{
			PORTA = 0xff;
		    PORTC = 0xff;
		    PORTB = 0xff;
		    PORTD = 0xff;
		}
		else if(mod == 2)
		{
			PORTA = 0x01;
		    PORTC = 0x00;
		    PORTB = 0xff;
		    PORTD = 0xff;
		    _delay_ms(500);

		    PORTA = 0xff;
		    PORTC = 0xff;
		    PORTB = 0x00;
		    PORTD = 0xe0;
		    _delay_ms(500);
		}
		else if(mod == 3)
		{
			PORTA = 0x01;
		    PORTC = 0x00;
		    PORTB = 0xff;
		    PORTD = 0xff;
		    _delay_ms(1000);

		    PORTA = 0xff;
		    PORTC = 0xff;
		    PORTB = 0x00;
		    PORTD = 0xe0;
		    _delay_ms(1000);
		}
		else
		{
			PORTA = 0xff;
		    PORTC = 0xff;
		    PORTB = 0xff;
		    PORTD = 0xff;
		    _delay_ms(200);

		    PORTA = 0x00;
		    PORTC = 0x00;
		    PORTB = 0x00;
		    PORTD = 0x00;
		    _delay_ms(200);
		}
	}

}
