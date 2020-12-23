#define F_CPU 16000000UL
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602.h"

uint8_t lcd_bit;
uint8_t is_lcd_initial = 0;
uint8_t lcd_limit_rows;
uint8_t lcd_limit_cols;
uint8_t lcd_cursor_x = 0;
uint8_t lcd_cursor_y = 0;
struct lcd1602a_port lcd_port;

static uint8_t lcd_port_init();
static uint8_t lcd_data(uint8_t byte);
static uint8_t lcd_command(uint8_t byte);

void set_lcd_port(struct lcd1602a_port port)
{
   lcd_port.data_ddr = port.data_ddr;
   lcd_port.data_port = port.data_port;
   lcd_port.rsrwe_ddr = port.rsrwe_ddr;
   lcd_port.rsrwe_port = port.rsrwe_port;
}

void set_lcd_bit(uint8_t bit)
{
   lcd_bit = bit;
}

uint8_t lcd_init(uint8_t rows, uint8_t cols)
{
   lcd_port_init();
   
   lcd_limit_rows = rows - 1;
   lcd_limit_cols = cols - 1;
   
   if (lcd_limit_rows < 0) lcd_limit_rows = 0;
   if (lcd_limit_cols < 0) lcd_limit_cols = 0;
   if (LCD_ROWS_MAX - 1 < lcd_limit_rows) lcd_limit_rows = LCD_ROWS_MAX - 1;
   if (LCD_COLS_MAX - 1 < lcd_limit_cols) lcd_limit_cols = LCD_COLS_MAX - 1;
   
   _delay_ms(30);
   
   if (lcd_bit == 4) {
      lcd_command(0x20);
      _delay_us(39);
   }
   
   lcd_command(0x20 | ((lcd_bit == 8) << 4) | (lcd_limit_cols << 3));
   _delay_us(39);
   lcd_command(0x0C);
   _delay_us(39);
   lcd_command(0x01);
   _delay_ms(1.53);
   lcd_command(0x06);
   _delay_us(39);
   
   lcd_cursor_x = 0;
   lcd_cursor_y = 0;
   is_lcd_initial = 1;
   
   return 0;
}

uint8_t lcd_move(uint8_t x, uint8_t y)
{
   lcd_cursor_x = x % (lcd_limit_rows + 1);
   lcd_cursor_y = x > lcd_limit_rows ? (LCD_COLS_MAX - 1) : y % (lcd_limit_cols + 1);
   
   lcd_command(0x80 + lcd_cursor_x + lcd_cursor_y * 0x40);
   _delay_us(39);
   
   return 0;
}

uint8_t lcd_putc(const char c)
{
   lcd_move(lcd_cursor_x, lcd_cursor_y);
   lcd_data(c);
   lcd_cursor_x++;
   lcd_move(lcd_cursor_x, lcd_cursor_y);
   return 0;
}

uint8_t lcd_puts(const char* str)
{
   int i = 0;
   
   for(i = 0; str[i]; i++) {
      lcd_putc(str[i]);
   }
   
   return 0;
}

uint8_t lcd_clear()
{
   lcd_command(0x01);
   _delay_ms(1.53);
   
   lcd_cursor_x = 0;
   lcd_cursor_y = 0;
   return 0;
}


uint8_t lcd_create_char(uint8_t location, uint8_t pattern[8])
{
   int i;
   
   lcd_command(0x40 + (location & 0x07) * 8);
   _delay_us(39);
   
   for (i = 0; i <  8; i++) {
      lcd_data(pattern[i] & 0x1F);
   }
   
   return 0;
}

uint8_t lcd_display_shift(uint8_t direction)
{
   lcd_display_shift_str(direction, 0);
}

uint8_t lcd_display_shift_str(uint8_t direction, uint8_t str_size)
{
   int i;
   static int count = -1;
   
   count ++;
   
   lcd_command(0x18 | ((direction & 0x01) << 2));
   _delay_us(39);
   
   if (count > lcd_limit_rows) {
      for (i = 0; i < count + 1 + str_size; i++) {
         lcd_command(0x18 | ((!direction & 0x01) << 2));
         _delay_us(39);
      }
      count = -1 - str_size;
   }
   
   return 0;
}

static uint8_t lcd_port_init()
{
   
   *(lcd_port.rsrwe_ddr) |= 0x07;
   *(lcd_port.rsrwe_port) &= ~0x07;
   
   if (lcd_bit == 8) {
      *(lcd_port.data_ddr) = 0xFF;
      *(lcd_port.data_port) = 0x00;
      return 0;
   } else if (lcd_bit == 4) {
      *(lcd_port.data_ddr) |= 0xF0;
      *(lcd_port.data_port) &= ~0xF0;
      return 0;
   }
   
   return -1;
}

static uint8_t lcd_data(uint8_t byte)
{
   _delay_ms(2);
   
   if (lcd_bit == 8) {
      *(lcd_port.data_port) = byte;
      *(lcd_port.rsrwe_port) &= ~0x03;
      *(lcd_port.rsrwe_port) |= 0x01;
      _delay_us(1);
      *(lcd_port.rsrwe_port) |= 0x04;
      _delay_us(1);
      *(lcd_port.rsrwe_port) &= ~0x04;
      
      return 0;
   } else if (lcd_bit == 4) {
      *(lcd_port.data_port) &= ~0xf0;
      *(lcd_port.data_port) |= byte & 0xf0;
      *(lcd_port.rsrwe_port) &= ~0x03;
      *(lcd_port.rsrwe_port) |= 0x01;
      _delay_us(1);
      *(lcd_port.rsrwe_port) |= 0x04;
      _delay_us(1);
      *(lcd_port.rsrwe_port) &= ~0x04;
      
      *(lcd_port.data_port) &= ~0xf0;
      *(lcd_port.data_port) |= (byte << 4) & 0xf0;
      *(lcd_port.rsrwe_port) &= ~0x03;
      *(lcd_port.rsrwe_port) |= 0x01;
      _delay_us(1);
      *(lcd_port.rsrwe_port) |= 0x04;
      _delay_us(1);
      *(lcd_port.rsrwe_port) &= ~0x04;
      
      return 0;
   }
   return -1;
}

static uint8_t lcd_command(uint8_t byte)
{
   _delay_ms(2);
   
   if (lcd_bit == 8) {
      *(lcd_port.data_port) = byte;
      *(lcd_port.rsrwe_port) &= ~0x03;
      _delay_us(1);
      *(lcd_port.rsrwe_port) |= 0x04;
      _delay_us(1);
      *(lcd_port.rsrwe_port) &= ~0x04;
      
      return 0;
   } else if (lcd_bit == 4) {
      *(lcd_port.data_port) &= ~0xf0;
      *(lcd_port.data_port) |= byte & 0xf0;
      *(lcd_port.rsrwe_port) &= ~0x03;
      _delay_us(1);
      *(lcd_port.rsrwe_port) |= 0x04;
      _delay_us(1);
      *(lcd_port.rsrwe_port) &= ~0x04;
      
      *(lcd_port.data_port) &= ~0xf0;
      *(lcd_port.data_port) |= (byte << 4) & 0xf0;
      *(lcd_port.rsrwe_port) &= ~0x03;
      _delay_us(1);
      *(lcd_port.rsrwe_port) |= 0x04;
      _delay_us(1);
      *(lcd_port.rsrwe_port) &= ~0x04;
      
      return 0;
   }
   
   return -1;
}
