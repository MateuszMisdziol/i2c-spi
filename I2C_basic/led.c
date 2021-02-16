#include <LPC21xx.H>
#include "led.h"

#define PIN_16_LED_0 (1<<16)
#define PIN_17_LED_1 (1<<17)
#define PIN_18_LED_2 (1<<18)
#define PIN_19_LED_3 (1<<19)
#define PIN_20_LED_4 (1<<20)
#define PIN_21_LED_5 (1<<21)
#define PIN_22_LED_6 (1<<22)
#define PIN_23_LED_7 (1<<23)


void LedInit(void){
	IO1DIR |= PIN_16_LED_0 | PIN_17_LED_1 | PIN_18_LED_2 | PIN_19_LED_3 | PIN_20_LED_4 | PIN_21_LED_5 | PIN_22_LED_6 | PIN_23_LED_7;
	LedClear();
}

void LedClear(void){
	IO1CLR  = PIN_16_LED_0 | PIN_17_LED_1 | PIN_18_LED_2 | PIN_19_LED_3 | PIN_20_LED_4 | PIN_21_LED_5 | PIN_22_LED_6 | PIN_23_LED_7;
}

void LedOn(unsigned char ucCodeStatus){
	LedClear();
	IO1SET = (ucCodeStatus << 16);
}
