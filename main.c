#include <stdio.h>  // Для отладочного вывода
#include <stdbool.h>
#include <stdint.h>
#include "leds.h"
#include "adc.h"
#include "uart.h"
#include "timer.h"
#include "pulse.h"
#include "gain.h"
#include "sh.h"
#include "ac.h"
#include "pwm.h"


// Для отладочного вывода
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);


enum {MAX_PULSE=3000,   // Максимальная длина импульса не модет быть больше (us)
      CURRENT_SC=111,   // Порог тока выше которого считается, что в датчике КЗ
      // При питании 13 В и датчике 497 мкГ, 1.133 Ом
      // CURRENT_SET - ток в конце импульса (мА)/current (попугам АЦП)/потребляемый ток (мА)
      // 120 - 1000/111/540, 37 - 500/37/207, 30 - 450/30.5/178, 24 - 400/24.7/157,
      // 19 - 350/20.5/139, 15 - 300/15.6/118, 12 - 250/13/100, 7 - 226/8.2/84
      CURRENT_SET=12,   // Установленный ток датчика
      };


// Переводим микросекунды в количество циклов
#define US(delay) (uint16_t)((uint32_t)delay*200/88)
inline void delay(volatile uint16_t what_a_delay){
    for(; what_a_delay!=0; what_a_delay--);
}


int main(void){
    uint16_t p_w = 0;      // Длительность сканирующего импульса
    uint16_t pulse_width;  // Длительность импулса отклика
    uint16_t current;      // Ток через даткмик
    int16_t limit;         // Положение потенциометра
    int16_t t;


	uart_init();
	stdout = &mystdout;
    adc_init();
    leds_init();
    pulse_init();
    amplifire_init();
    pwm_init();
    timer0_init();
    timer2_init();

    gain_on();
    sh_on();
    pwm_set(255);
    while(true){
        // Даём сканирующего импульс заданной длительности
        DO_PULSE(p_w);

        // Измеряем ток. Максимум на АЦП сразу после сканирующего импульса
        // I(mA)=4.412*current+47.24
        current = adc_read(CURRENT);

        // Измеряем длительность импульса отклика
        // Эта длительность и даёт информацию о наличи металла
        // Импульс отклика возникает через 9 мкс после завершения сканирующего импульса
        pulse_width = 0;
        WAIT_FOR_END_PULSE{
            pulse_width++;
            if(pulse_width >= MAX_PULSE) break;
        }

        // Проверяем нет ли короткого замыкания в датчике
        if(current > CURRENT_SC){
            p_w = 0;
        }
        // Подhttps://www.youtube.com/watch?v=yUwD8eOc97E&list=WL&index=5&t=50sдерживаем установленный ток в датчике
        if(current > CURRENT_SET){
            if(p_w) p_w--;
        }else{
            if(p_w < MAX_PULSE) p_w++;
        }
        // Если p_w == 0 (мкс) это признак короткого замыкания в датчике
        // Если p_w == MAX_PULSE (мкс) это признак обрыва датчика

        // Выводим индкацию
        // Надо постоянно переинициализировать АЦП т.к. АЦП отключается при
        // инициализации аналового компаратора при измерении длительности импульса отклика
        adc_init();
        // Считываем положение потенциометра
        limit = adc_read(LIMIT);

        // Выводим светодиодную индикацию
        t = pulse_width - 1023 + limit;
        if(t < 0) t=0;
        t /= 117;
        leds_set_value(t);

        // Выводим звуковую индикацию
        t = pulse_width - 1023 + limit;
        if(t < 0) t=0;
        t /= 10;
        set_tone(t);
        sound_on();

// printf("%i\n", t);
// printf("%i\n", current);
// printf("%i\n", p_w);
// printf("%i\n", pulse_width);

        // Стабилизируем время цикла таймером
        // Это нужно для правильного измерения тока через датчик
        WAIT_FOR_START_CYCLE;
    }

    return 0;
}
