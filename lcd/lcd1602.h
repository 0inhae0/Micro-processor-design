
#ifndef LCD1602
#define LCD1602
#define LCD_PIN_RS 0 
#define LCD_PIN_RW 1 
#define LCD_PIN_E 2 
#define LCD_PIN_DB0 0 
#define LCD_PIN_DB1 1 
#define LCD_PIN_DB2 2 
#define LCD_PIN_DB3 3 
#define LCD_PIN_DB4 4 
#define LCD_PIN_DB5 5 
#define LCD_PIN_DB6 6 
#define LCD_PIN_DB7 7 
#define LCD_ROWS_MAX 16 
#define LCD_COLS_MAX 2 
#define LCD_SHIFT_RIGHT 1 
#define LCD_SHIFT_LEFT 0 
struct lcd1602a_port 
{ volatile uint8_t *rsrwe_ddr;
  volatile uint8_t *data_ddr;
  volatile uint8_t *rsrwe_port;
  volatile uint8_t *data_port; 
  };
  void set_lcd_port(struct lcd1602a_port port); 
  void set_lcd_bit(uint8_t bit); 
  uint8_t lcd_init(uint8_t rows, uint8_t cols); 
  uint8_t lcd_move(uint8_t x, uint8_t y); 
  uint8_t lcd_putc(const char c); 
  uint8_t lcd_puts(const char* str); 
  uint8_t lcd_clear(); 
  uint8_t lcd_create_char(uint8_t location, uint8_t pattern[8]); 
  uint8_t lcd_display_shift_str(uint8_t direction, uint8_t str_size); 
  uint8_t lcd_display_shift(uint8_t direction); 
  #endif /* LCD1602A_H_ */
