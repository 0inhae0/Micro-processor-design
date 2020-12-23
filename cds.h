
void init_adc()
{
	ADMUX = 0x00;
	// REFS(1:0) = ��00�� AREF(+5V) ���ؠ��� ���
	// ADLAR = .0. ����Ʈ ������ ����
	// MUX(4:0) = ��00000�� ADC0 ���, �ܱ� �Է�
	ADCSRA = 0x87;
	// ADEN = .1. ADC�� Enable
	// ADFR = .0. single conversion ���
	// ADPS(2:0) = ��111�� ���������Ϸ� 128����
}

unsigned short read_adc() {
	unsigned char adc_low, adc_high;
	unsigned short value;
	ADCSRA |= 0x40; // ADC start conversion, ADSC = �1.
	while ((ADCSRA & 0x10) != 0x10); // ADC ��ȯ �Ϸ� �˻�
	adc_low = ADCL; // ��ȯ�� Low �� �о����
	adc_high = ADCH; // ��ȯ�� High �� �о����
	value = (adc_high << 8) | adc_low; // value �� High �� Low ���� 16��Ʈ��
	return value;
}
