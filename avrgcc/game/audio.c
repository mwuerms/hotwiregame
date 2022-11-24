/**
 * Martin Egli
 * 2022-06-06
 *
 * generate audio frequency from 8 MHz
 */

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "io.h"
#include "audio.h"

// - private variables ---------------------------------------------------------

// - private functions ---------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
    return;
}

// - public functions ----------------------------------------------------------
void audio_init(void)
{
    DDRB |= (1 << PIN_AUDIO_PWM);
}

void audio_on_duration_ms(uint16_t freq, uint16_t duration_ms)
{
    uint32_t timer_top;
    TIMSK1 = 0; // disable all interrupts
    // TOP in ICR1 = f_{clkI/O}(N*f_{pwm}-1
    timer_top = ((uint32_t)(F_CPU) / (uint32_t)(freq)) - 1;
    ICR1 = (uint16_t)timer_top;
    // duty cycle in OCR1A
    OCR1A = ICR1/2; // 50 % duty cycle fix

    // use mode 14: fast pwm, TOP: ICR1
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
}

void audio_off(void)
{
    TIMSK1 = 0; // disable all interrupts
    TCCR1B = 0; // stop clock/counter
    TCCR1C = 0; // force outputs low
    TCCR1A = 0;
}
