#ifndef TIMER_H
#define TIMER_H

#define WAIT_FOR_START_CYCLE loop_until_bit_is_set(TIFR, OCF0); \
                              TIFR |= 1<<OCF0;

void timer0_init(void);
void timer2_init(void);
void set_tone(uint8_t);
void sound_on(void);
void sound_off(void);

#endif
