#define F_CPU 16000000UL 
#include <avr/io.h> 
#include <util/delay.h> 
#include "lcd1602.h" 
#include "buzzer.h"


int main(void) 
{ 
	init_switch();	

	set_interrupt_handler(4, switch_handler4);

	set_interrupt_handler(5, switch_handler5);

	init_buzzer();

	Firstview();

	int mod4 = 0;
	int mod5 = 0;

	void switch_handler4() 
	{
	mod4++;
	if(mod4 == 5)
	 {
	 mod4 = 2;
	 }
	}

	void switch_handler5() 
	{
    mod5++;
	if(mod5 == 1)
	 {
	 mod5 = 0;
	 }
	}
	
	if(mod4 == 1)
	{
	SecondView();
	}
	else if(mod4 == 2)
	{
	SongSelect1();
	if(mod5 == 1)
	 {
	 MusicisPlaying();
	 JingleBells();
	 }
	}
	else if(mod4 == 3)
	{
	 if(mod5 == 1)
	 {
	 MusicisPlaying();
	 Rudolph_start();
	 }
	}
	else if(mod4 == 4)
	{
	 if(mod5 == 1)
	 {
	 MusicisPlaying();
	 Christmas();
	 }
	}

	//Rudolph_start();

	//PORTB &= 0xEF;
   // _delay_ms(3000);
   
	//JingleBells();
	//PORTB &= 0xEF;
   //_delay_ms(3000);

   //Christmas();

}
