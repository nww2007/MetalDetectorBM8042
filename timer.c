#include <avr/io.h>
#include <stdint.h>
#include "timer.h"


void timer0_init(void){
    TCCR0 = 0
          | (0<<FOC0)
		  | (1<<WGM01) | (0<<WGM00)  // CTC
		  | (0<<COM01) | (0<<COM00)  // Выход OC0 отключен
		  | (1<<CS02) | (0<<CS01) | (0<<CS00)  // таймер заполняется с частотй кварца/256 
	;
    OCR0 = 255;
}


void timer2_init(void){
    DDRB |= (1 << PB3);    // Этим выводом включается звук
    PORTB &= ~(1 << PB3);  // Пока звук отключит
    DDRD |= (1 << PD7);    // Это вывод OC2
    TCCR2 = 0
          | (0<<FOC2)
		  | (1<<WGM21) | (0<<WGM20)  // CTC
		  | (0<<COM21) | (1<<COM20)  // Выход OC2 переключается при совпадении границы
		  | (1<<CS02) | (1<<CS01) | (1<<CS00)  // таймер заполняется с частотй кварца/1024
	;
    OCR2 = 0;
}


void set_tone(uint8_t tone){
    OCR2 = tone;
}


void sound_on(void){
    PORTB |= (1 << PB3);
}


void sound_off(void){
    PORTB &= ~(1 << PB3);
}
