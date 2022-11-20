/**
 * Martin Egli
 * 2022-11-20
 * 
 * use timer 0 to generate some timings
 */

// - include -------------------------------------------------------------------
#include "timer.h"
#include <avr/interrupt.h>

// - private variables ---------------------------------------------------------
static volatile uint8_t timer_count_down_ovf, timer_send_event;
// - private functions ---------------------------------------------------------
ISR(TIMER0_OVF_vect)
{
    if(timer_count_down_ovf == 0) {
        timer_stop();
        SEND_EVENT(EV_TIMER);
        SEND_TIMER_EVENT(timer_send_event);
    }
    else {
        timer_count_down_ovf--;
    }
    PINB |= (1 << 5);
}

// - public functions ----------------------------------------------------------
void timer_init(void) {
    timer_stop();
}

void timer_start(uint8_t cnt_nb_ovfs, uint8_t event) {
    timer_stop();
    timer_count_down_ovf = cnt_nb_ovfs;
    timer_send_event = event;
    TCCR0A = 0x00;
    TCNT0 = 0;
    TIFR0 = TOV0;   // clear by wr 1
    TIMSK0 = TOIE0;
    TCCR0B = TIMER_PRESCALER_1024; // run using precsaler

    PORTB |=  (1 << 5);
    PINB |= (1 << 5);
}
