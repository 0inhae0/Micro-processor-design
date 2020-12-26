#define F_CPU 16000000UL 
#include <avr/io.h> 
#include <util/delay.h> 
#include "lcd1602.h" 

void FirstView()
{
int n = 0;
struct lcd1602a_port port = {&DDRD, &DDRD, &PORTD, &PORTD};
uint8_t heart[1][8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04,0x00 };
 	set_lcd_bit(4);
  	set_lcd_port(port);
   	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	lcd_create_char(0, heart[n]);
    lcd_move(0, 0);
	lcd_puts("MERRY CHRISTMAS!");
	lcd_move(0, 1);
	lcd_puts("HAPPY NEW YEAR!");
	lcd_move(15, 1);
	lcd_putc(0x00);
}

void SecondView()
{
struct lcd1602a_port port = {&DDRD, &DDRD, &PORTD, &PORTD};
 	set_lcd_bit(4);
  	set_lcd_port(port);
   	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	lcd_move(1,0);
	lcd_puts("SELECT A");
	lcd_move(0,1);
	lcd_puts("CHRISTMAS SONG!");
}

void SongSelect1()
{
struct lcd1602a_port port = {&DDRD, &DDRD, &PORTD, &PORTD};
 	set_lcd_bit(4);
  	set_lcd_port(port);
   	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	lcd_move(0,0);
	lcd_puts("SONG 1");
	lcd_move(0,1);
	lcd_puts("JINGLE BELL");
}

void SongSelect2()
{
struct lcd1602a_port port = {&DDRD, &DDRD, &PORTD, &PORTD};
 	set_lcd_bit(4);
  	set_lcd_port(port);
   	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	lcd_move(0,0);
	lcd_puts("2.RUDOLPH THE RED-NOSED REINDEER");
}

void SongSelect3()
{
struct lcd1602a_port port = {&DDRD, &DDRD, &PORTD, &PORTD};
 	set_lcd_bit(4);
  	set_lcd_port(port);
   	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	lcd_move(0,0);
	lcd_puts("3.WE WISH YOU A MERRY CHRISTMAS");
}

void MusicisPlaying()
{
struct lcd1602a_port port = {&DDRD, &DDRD, &PORTD, &PORTD};
 	set_lcd_bit(4);
  	set_lcd_port(port);
   	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	lcd_move(4,0);
	lcd_puts("MUSIC IS");
	lcd_move(3,1);
	lcd_puts("PLAYING...");
}
