/**
 * Martin Egli
 * 2022-06-06
 *
 * generate variable pwm signal:
 * 1 ... 10 kHz, 0.1 ... 99.9 %
 *
 * Timer1 as variable PWM output
 * periode (TOP, frequency):
 *  ICR1
 * outputs(same frequency, different duty cycle):
 *  OC1A
 *  OC1B
 *
 * f_{pwm} = f_{clkI/O}/(N*(1+TOP))
 * f_{clkI/O} = F_CPU = 8000000
 * N: prescalser = 1 (1, 8, 64, 256, or 1024)
 *
 */
#warning _TODO frequency sweep
#warning _TODO duty cycle sweep

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

void audio_on(uint16_t freq, uint16_t duration_ms)
{
#if 0
    uint16_t prescaler = 1;
    uint8_t cs_value = _BV(CS12);
    TIMSK1 = 0; // disable all interrupts

    // TOP = f_{clkI/O}(N*f_{pwm}-1
    // check set_duty_cycle
    if (set_duty_cycle > PWM_MAX_DUTY_CYCLE)
    {
        // error, out of range, do not start pwm
        pwm_stop();
        DDRB |= _BV(PIN_AUDIO_PWM);
        PORTB |= _BV(PIN_AUDIO_PWM);
        return;
    }
    if (set_duty_cycle == 0)
    {
        // error, out of range, do not start pwm
        pwm_stop();
        DDRB |= _BV(PIN_AUDIO_PWM);
        PORTB &= ~_BV(PIN_AUDIO_PWM);
        return;
    }
    // get prescaler N from range
    if (set_freq > PWM_MAX_FREQUENCY)
    {
        // error, out of range, do not start pwm
        pwm_stop();
        DDRB |= _BV(PIN_AUDIO_PWM);
        PORTB |= _BV(PIN_AUDIO_PWM);
        return;
    }
    if (set_freq == 0)
    {
        // error, out of range, do not start pwm
        pwm_stop();
        DDRB |= _BV(PIN_AUDIO_PWM);
        PORTB &= ~_BV(PIN_AUDIO_PWM);
        return;
    }
    else if (set_freq >= 250)
    {
        prescaler = 1;
        cs_value = _BV(CS10);
    }
    else if (set_freq >= 31)
    {
        prescaler = 8;
        cs_value = _BV(CS11);
    }
    else if (set_freq >= 4)
    {
        prescaler = 64;
        cs_value = _BV(CS11) | _BV(CS10);
    }
    else
    {
        prescaler = 256;
        cs_value = _BV(CS12);
    }
    // TOP in ICR1
    timer_top = ((uint32_t)(F_CPU) / (prescaler * (uint32_t)(set_freq))) - 1;
    ICR1 = (uint16_t)timer_top;
    // duty cycle in OCR1A
    OCR1A = (uint16_t)((timer_top * set_duty_cycle) / PWM_MAX_DUTY_CYCLE);

    // use mode 14: fast pwm, TOP: ICR1
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | cs_value;
#endif
}

void audio_off(void)
{
    TIMSK1 = 0; // disable all interrupts
    TCCR1B = 0; // stop clock/counter
    TCCR1C = 0; // force outputs low
    TCCR1A = 0;
}
