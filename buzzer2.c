#define F_CPU 16000000UL //AVR칩에 사용중인 CPU 클럭시간을 16MHz로 설정
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
SOL, M, RA, RA, M, SOL, M, MI, MI, M, DDO, DDO, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, M, //루돌프 사슴코는
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, DDO, DDO, M, SI, SI, SI, SI, SI, SI, M, M, //매우 반짝이는 코
FA, M, SOL, SOL, M, FA, M, RE, RE, M, SI, SI, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, SOL, M, //만일 네가 봤다면,
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, RA, RA, M, MI, MI, MI, MI, MI, MI, M, M, //불 붙는다 했겠지
SOL, M, RA, RA, M, SOL, M, MI, MI, M, DDO, DDO, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, M, //다른 모든 사슴들
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, DDO, DDO, M, SI, SI, SI, SI, SI, SI, M, M, //놀려대며 웃었네
FA, M, SOL, SOL, M, FA, M, RE, RE, M, SI, SI, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, SOL, M, //가엾은 저 루돌프
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, RRE, RRE, M, DDO, DDO, DDO, DDO, DDO, DO, M, M, //외톨이가 되었네
RA, RA, M, RA, RA, M, DDO, DDO, M, RA, RA, M, SOL, SOL, M, MI, M, SOL, SOL, SOL, SOL, SOL, M, //안개낀 성탄절 날
FA, FA, M, RA, RA, M, SOL, SOL, M, FA, FA, M, MI, MI, MI, MI, MI, MI, MI, MI, M, //산타말하길
RE, RE, M, MI, MI, M, SOL, SOL, M, RA, RA, M, SI, SI, M, SI, SI, M, SI, SI, SI, SI, M, //루돌프 코가 밝으니
DDO, DDO, M, DDO, DDO, M, SI, SI, M, RA, RA, M, SOL, SOL, M, FA, M, RE, RE, RE, RE, RE, M, //썰매를 끌어주렴
SOL, M, RA, RA, M, SOL, M, MI, MI, M, DDO, DDO, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, M, //그 후론 사슴들이
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, DDO, DDO, M, SI, SI, SI, SI, SI, SI, M, M, //그를 매우 사랑했네
FA, M, SOL, SOL, M, FA, M, RE, RE, M, SI, SI, M, RA, RA, M, SOL, SOL, SOL, SOL, SOL, SOL, SOL, M, //루돌프 사슴 코는
SOL, M, RA, M, SOL, M, RA, M, SOL, SOL, M, RRE, RRE, M, DDO, DDO, DDO, DDO, DDO, DO, M, M, //기리기리 기억되리~!
EOS};

int Jingle_Bells[] = {
DO, M, RA, M, SOL, M, FA, M, DO, DO, M, M, M, M, M, M, M, M, M, M, M, //흰 눈 사이로
DO, M, RA, M, SOL, M, FA, M, RE, RE, M, M, M, M, M, M, M, M, M, M, M, //썰매를 타고
RE, M, RAs, M, RA, M, SOL, M, MI, MI, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, //달리는 기분
DDO, M, DDO, M, RAs, M, SOL, M, RA, RA, M, FA, M, M, M, M, M, M, //상쾌도 하다
DO, M, RA, M, SOL, M, FA, M, DO, DO, M, M, M, M, M, M, M, M, M, M, M, //종이 울려서
DO, M, RA, M, SOL, M, FA, M, RE, RE, M, M, M, M, M, M, M, M, M, M, M, //장단 맞추니
RE, M, RAs, M, RA, M, SOL, M, DDO, M, DDO, M, DDO, M, DDO, M, //흥겨워서 소리높여
RRE, M, DDO, M, RAs, M, SOL, M, FA, FA, FA, FA, M, //노래부른다
RA, M, RA, M, RA, RA, M, RA, M, RA, M, RA, RA, M, //종소리 울려라
RA, M, DDO, M, FA, M, SOL, M, RA, RA, RA, M, M, M, M, M, //종소리 울려
RAs, M, RAs, M, RAs, M, RAs, M, RAs, M, RA, M, RA, M, RA, M, //우리썰매 빨리달려
RA, M, SOL, M, SOL, M, FA, M, SOL, SOL, M, DDO, DDO, M, //종소리 울려라
RA, M, RA, M, RA, RA, M, RA, M, RA, M, RA, RA, M, //종소리 울려라
RA, M, DDO, M, FA, M, SOL, M, RA, RA, RA, M, M, M, M, M, //종소리 울려
RAs, M, RAs, M, RAs, M, RAs, M, RAs, M, RA, M, RA, M, RA, M, //기쁜노래 부르면서
DDO, M, DDO, M, RAs, M, SOL, M, FA, FA, M, M, M, //빨리 달린다
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

int mod = 0; // 0 : 끄기 | 1 : 루돌프사슴코 | 2 : 징글벨 | 3 :We wish your merry Christmas

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
			//루돌프 사슴코
			i = 0;
			TCNT0 = TCNT0s[Rudolph_the_Red_Nosed_Reindeer[i]];
			do {
				tone_index = Rudolph_the_Red_Nosed_Reindeer[i++];
				if(tone_index == M)
				{
					PORTB &= 0xEF; //한 음이 끝날 때마다 잠시 꺼서 멈추기
					_delay_ms(50);
					PORTB |= 0x10; //다시 켜주기
				}
				else
					_delay_ms(200);
			}while(tone_index != EOS);
		}
		else if(mod == 2)
		{
			//징글벨
			i = 0;
			TCNT0 = TCNT0s[Jingle_Bells[i]];
			do {
				tone_index = Jingle_Bells[i++];
				if(tone_index == M)
				{
					PORTB &= 0xEF; //한 음이 끝날 때마다 잠시 꺼서 멈추기
					_delay_ms(20);
					PORTB |= 0x10; //다시 켜주기
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
					PORTB &= 0xEF; //한 음이 끝날 때마다 잠시 꺼서 멈추기
					_delay_ms(20);
					PORTB |= 0x10; //다시 켜주기
				}
				else
					_delay_ms(200);
			}while(tone_index != EOS);
		}
	}

	init_buzzer();

//루돌프 사슴코

	int i = 0;
	TCNT0 = TCNT0s[Rudolph_the_Red_Nosed_Reindeer[i]];
	do {
		tone_index = Rudolph_the_Red_Nosed_Reindeer[i++];
		if(tone_index == M)
		{
			PORTB &= 0xEF; //한 음이 끝날 때마다 잠시 꺼서 멈추기
			_delay_ms(50);
			PORTB |= 0x10; //다시 켜주기
		}
		else
			_delay_ms(200);
	}while(tone_index != EOS);

	PORTB &= 0xEF;
	_delay_ms(5000);


//징글벨

	i = 0;
	TCNT0 = TCNT0s[Jingle_Bells[i]];
	do {
		tone_index = Jingle_Bells[i++];
		if(tone_index == M)
		{
			PORTB &= 0xEF; //한 음이 끝날 때마다 잠시 꺼서 멈추기
			_delay_ms(20);
			PORTB |= 0x10; //다시 켜주기
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
			PORTB &= 0xEF; //한 음이 끝날 때마다 잠시 꺼서 멈추기
			_delay_ms(20);
			PORTB |= 0x10; //다시 켜주기
		}
		else
			_delay_ms(200);
	}while(tone_index != EOS);

	PORTB &= 0xEF;
	_delay_ms(5000);

}
