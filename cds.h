
void init_adc()
{
	ADMUX = 0x00;
	// REFS(1:0) = ¡°00¡± AREF(+5V) ±âÁØ †¾Ð »ç¿ë
	// ADLAR = .0. µðÆúÆ® ¿À¸¥ÂÊ Á¤·Ä
	// MUX(4:0) = ¡°00000¡± ADC0 »ç¿ë, ´Ü±Ø ÀÔ·Â
	ADCSRA = 0x87;
	// ADEN = .1. ADC¸¦ Enable
	// ADFR = .0. single conversion ¸ðµå
	// ADPS(2:0) = ¡°111¡± ÇÁ¸®½ºÄÉÀÏ·¯ 128ºÐÁÖ
}

unsigned short read_adc() {
	unsigned char adc_low, adc_high;
	unsigned short value;
	ADCSRA |= 0x40; // ADC start conversion, ADSC = „1.
	while ((ADCSRA & 0x10) != 0x10); // ADC º¯È¯ ¿Ï·á °Ë»ç
	adc_low = ADCL; // º¯È¯µÈ Low °ª ÀÐ¾î¿À±â
	adc_high = ADCH; // º¯È¯µÈ High °ª ÀÐ¾î¿À±â
	value = (adc_high << 8) | adc_low; // value ´Â High ¹× Low ¿¬°á 16ºñÆ®°ª
	return value;
}
