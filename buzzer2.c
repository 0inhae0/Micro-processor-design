#define F_CPU 16000000UL //AVRĨ�� ������� CPU Ŭ���ð��� 16MHz�� ����
#include <avr/io.h>
#include <util/delay.h>
#include "switch.h"
#include "buzzer.h"

#define DO 0
#define DOs 1
#define RE 2
#define REs 3
#define MI 4
#define FA 5
#define FAs 6
#define SOL 7
#define SOLs 8
#define RA 9
#define RAs 10
#define SI 11
#define DDO 12
#define DDOs 13
#define RRE 14
#define RREs 15
#define MMI 16
#define M -1000
#define EOS -2000

int Rudolph_the_Red_Nosed_Reindeer[] = {
SOL, M, RA, RA, M, SOL, M, MI, MI, M, DDO, DDO, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, M, //�絹�� �罿�ڴ�
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, DDO, DDO, M, SI, SI, SI, SI, SI, SI, M, M, //�ſ� ��¦�̴� ��
FA, M, SOL, SOL, M, FA, M, RE, RE, M, SI, SI, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, SOL, M, //���� �װ� �ôٸ�,
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, RA, RA, M, MI, MI, MI, MI, MI, MI, M, M, //�� �ٴ´� �߰���
SOL, M, RA, RA, M, SOL, M, MI, MI, M, DDO, DDO, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, M, //�ٸ� ��� �罿��
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, DDO, DDO, M, SI, SI, SI, SI, SI, SI, M, M, //������ ������
FA, M, SOL, SOL, M, FA, M, RE, RE, M, SI, SI, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, SOL, M, //������ �� �絹��
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, RRE, RRE, M, DDO, DDO, DDO, DDO, DDO, DO, M, M, //�����̰� �Ǿ���
RA, RA, M, RA, RA, M, DDO, DDO, M, RA, RA, M, SOL, SOL, M, MI, M, SOL, SOL, SOL, SOL, SOL, M, //�Ȱ��� ��ź�� ��
FA, FA, M, RA, RA, M, SOL, SOL, M, FA, FA, M, MI, MI, MI, MI, MI, MI, MI, MI, M, //��Ÿ���ϱ�
RE, RE, M, MI, MI, M, SOL, SOL, M, RA, RA, M, SI, SI, M, SI, SI, M, SI, SI, SI, SI, M, //�絹�� �ڰ� ������
DDO, DDO, M, DDO, DDO, M, SI, SI, M, RA, RA, M, SOL, SOL, M, FA, M, RE, RE, RE, RE, RE, M, //��Ÿ� �����ַ�
SOL, M, RA, RA, M, SOL, M, MI, MI, M, DDO, DDO, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, M, //�� �ķ� �罿����
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, DDO, DDO, M, SI, SI, SI, SI, SI, SI, M, M, //�׸� �ſ� ����߳�
FA, M, SOL, SOL, M, FA, M, RE, RE, M, SI, SI, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, SOL, M, //�絹�� �罿 �ڴ�
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, RRE, RRE, M, DDO, DDO, DDO, DDO, DDO, DO, M, M, //�⸮�⸮ ���Ǹ�~!
EOS};

int Jingle_Bells[] = {
DO, M, RA, M, SOL, M, FA, M, DO, DO, M, M, M, M, M, M, M, M, M, M, M, //�� �� ���̷�
DO, M, RA, M, SOL, M, FA, M, RE, RE, M, M, M, M, M, M, M, M, M, M, M, //��Ÿ� Ÿ��
RE, M, RAs, M, RA, M, SOL, M, MI, MI, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, //�޸��� ���
DDO, M, DDO, M, RAs, M, SOL, M, RA, RA, M, FA, M, M, M, M, M, M, //���赵 �ϴ�
DO, M, RA, M, SOL, M, FA, M, DO, DO, M, M, M, M, M, M, M, M, M, M, M, //���� �����
DO, M, RA, M, SOL, M, FA, M, RE, RE, M, M, M, M, M, M, M, M, M, M, M, //��� ���ߴ�
RE, M, RAs, M, RA, M, SOL, M, DDO, M, DDO, M, DDO, M, DDO, M, //��ܿ��� �Ҹ�����
RRE, M, DDO, M, RAs, M, SOL, M, FA, FA, FA, FA, M, //�뷡�θ���
RA, M, RA, M, RA, RA, M, RA, M, RA, M, RA, RA, M, //���Ҹ� �����
RA, M, DDO, M, FA, M, SOL, M, RA, RA, RA, M, M, M, M, M, //���Ҹ� ���
RAs, M, RAs, M, RAs, M, RAs, M, RAs, M, RA, M, RA, M, RA, M, //�츮��� �����޷�
RA, M, SOL, M, SOL, M, FA, M, SOL, SOL, M, DDO, DDO, M, //���Ҹ� �����
RA, M, RA, M, RA, RA, M, RA, M, RA, M, RA, RA, M, //���Ҹ� �����
RA, M, DDO, M, FA, M, SOL, M, RA, RA, RA, M, M, M, M, M, //���Ҹ� ���
RAs, M, RAs, M, RAs, M, RAs, M, RAs, M, RA, M, RA, M, RA, M, //��۳뷡 �θ��鼭
DDO, M, DDO, M, RAs, M, SOL, M, FA, FA, M, M, M, //���� �޸���
EOS};

int We_wish_your_merry_christmas[] = {
DO, DO, M, FA, FA, M, FA, M, SOL, M, FA, M, MI, M, RE, RE, M, RE, RE, M, RE, RE, M, //We wish you a merry Christmas ; We
SOL, SOL, M, SOL, M, RA, M, SOL, M, FA, M, MI, MI, M, DO, DO, M, DO, DO, M, //wish you a merry Christmas ; We
RA, RA, M, RA, M, RAs, M, RA, M, SOL, M, FA, FA, M, RE, RE, M, DO, M, DO, M, //wish you a merry Christmas ; And a
RE, RE, M, SOL, SOL, M, MI, MI, M, FA, FA, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, DO, DO, M, //happy new year ; Good
FA, FA, M, FA, FA, M, FA, FA, M, MI, MI, MI, MI, M, MI, MI, M, FA, FA, M, MI, MI, M, RE, RE, M, //tidings we brings to you and your
DO, DO, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, SOL, SOL, M, RA, RA, M, SOL, SOL, M, FA, FA, M, //king ; Good tidings for 
DDO, DDO, M, DO, DO, M, DO, M, DO, M, RE, RE, M, SOL, SOL, M, MI, MI, M, FA, FA, M, M, M, M, M, //Christmas And a happy new year
EOS};

int mod = 0; // 0 : ���� | 1 : �絹���罿�� | 2 : ¡�ۺ� | 3 :We wish your merry Christmas

void switch_handler4() {
	mod ++;
	if (mod == 4)
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

	init_switch();	
	set_interrupt_handler(4, switch_handler4);
	set_interrupt_handler(5, switch_handler5);

	while(1)
	{
		int i = 0;

		if(mod == 0)
		{
			PORTB &= 0xEF;
		}
		else if(mod == 1)
		{
			//�絹�� �罿��
			i = 0;
			TCNT0 = TCNT0s[Rudolph_the_Red_Nosed_Reindeer[i]];
			do {
				tone_index = Rudolph_the_Red_Nosed_Reindeer[i++];
				if(tone_index == M)
				{
					PORTB &= 0xEF; //�� ���� ���� ������ ��� ���� ���߱�
					_delay_ms(50);
					PORTB |= 0x10; //�ٽ� ���ֱ�
				}
				else
					_delay_ms(200);
			}while(tone_index != EOS);
		}
		else if(mod == 2)
		{
			//¡�ۺ�
			i = 0;
			TCNT0 = TCNT0s[Jingle_Bells[i]];
			do {
				tone_index = Jingle_Bells[i++];
				if(tone_index == M)
				{
					PORTB &= 0xEF; //�� ���� ���� ������ ��� ���� ���߱�
					_delay_ms(20);
					PORTB |= 0x10; //�ٽ� ���ֱ�
				}
				else
					_delay_ms(200);
			}while(tone_index != EOS);
		}
		else
		{
			//We wish your merry Christmas
			i = 0;
			TCNT0 = TCNT0s[We_wish_your_merry_christmas[i]];
			do {
				tone_index = We_wish_your_merry_christmas[i++];
				if(tone_index == M)
				{
					PORTB &= 0xEF; //�� ���� ���� ������ ��� ���� ���߱�
					_delay_ms(20);
					PORTB |= 0x10; //�ٽ� ���ֱ�
				}
				else
					_delay_ms(200);
			}while(tone_index != EOS);
		}
	}

	init_buzzer();

//�絹�� �罿��

	int i = 0;
	TCNT0 = TCNT0s[Rudolph_the_Red_Nosed_Reindeer[i]];
	do {
		tone_index = Rudolph_the_Red_Nosed_Reindeer[i++];
		if(tone_index == M)
		{
			PORTB &= 0xEF; //�� ���� ���� ������ ��� ���� ���߱�
			_delay_ms(50);
			PORTB |= 0x10; //�ٽ� ���ֱ�
		}
		else
			_delay_ms(200);
	}while(tone_index != EOS);

	PORTB &= 0xEF;
	_delay_ms(5000);


//¡�ۺ�

	i = 0;
	TCNT0 = TCNT0s[Jingle_Bells[i]];
	do {
		tone_index = Jingle_Bells[i++];
		if(tone_index == M)
		{
			PORTB &= 0xEF; //�� ���� ���� ������ ��� ���� ���߱�
			_delay_ms(20);
			PORTB |= 0x10; //�ٽ� ���ֱ�
		}
		else
			_delay_ms(200);
	}while(tone_index != EOS);

	PORTB &= 0xEF;
	_delay_ms(5000);

//We wish your merry Christmas

	i = 0;
	TCNT0 = TCNT0s[We_wish_your_merry_christmas[i]];
	do {
		tone_index = We_wish_your_merry_christmas[i++];
		if(tone_index == M)
		{
			PORTB &= 0xEF; //�� ���� ���� ������ ��� ���� ���߱�
			_delay_ms(20);
			PORTB |= 0x10; //�ٽ� ���ֱ�
		}
		else
			_delay_ms(200);
	}while(tone_index != EOS);

	PORTB &= 0xEF;
	_delay_ms(5000);

}
