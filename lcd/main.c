#define F_CPU 16000000UL 
#include <avr/io.h> 
#include <util/delay.h> 
#include "lcd1602.h" 
#include <stdint.h>

int main(void) 
{ 
struct lcd1602a_port port = {&DDRE, &DDRE, &PORTE, &PORTE};

set_lcd_bit(4);
set_lcd_port(port); 
lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
lcd_move(0, 0); 
lcd_puts("MERRY CHRISTMAS!");

while (1){
 lcd_display_shift_str(LCD_SHIFT_RIGHT, 16);
   _delay_ms(500);
   } 

}
