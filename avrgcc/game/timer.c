/**
 * Martin Egli
 * 2022-11-20
 * 
 * use timer 0 to generate some timings
 */

// - include -------------------------------------------------------------------
#include "timer.h"
#include <avr/interrupt.h>
#include "io.h"

// - defines -------------------------------------------------------------------
#define TIMER_RELOAD_CNT_1MS_PRESC_64 (255-(125*2))
// - private variables ---------------------------------------------------------
static volatile uint16_t timer_delay_ms;
static volatile uint8_t  timer_send_event;

// - 1 ms tick timer -----------------------------------------------------------
static volatile struct {
    struct {
        uint16_t ms, s;
    } time;
    struct {
        uint16_t cnt_down_ms, cnt_down_ms_reload;
        uint8_t  event;
    } repeated_event[2];
    struct {
        uint16_t cnt_down_ms;
        uint8_t  event;
    } single_event;
} timer_ms_tick;

// - private functions ---------------------------------------------------------


static void timer_tick_process_repeated(uint8_t ev_nr) {
    if(timer_ms_tick.repeated_event[ev_nr].event) {
        if(timer_ms_tick.repeated_event[ev_nr].cnt_down_ms == 0) {
            timer_ms_tick.repeated_event[ev_nr].cnt_down_ms = timer_ms_tick.repeated_event[ev_nr].cnt_down_ms_reload;
            SEND_EVENT(EV_TIMER);
            SEND_TIMER_EVENT(timer_ms_tick.repeated_event[ev_nr].event);
            //PINB |= (1 << PIN_INT_LED); // toggle
        }
        else {
            timer_ms_tick.repeated_event[ev_nr].cnt_down_ms--;
        }
    }
    // else inactive
}

// 1 ms tick timer
ISR(TIMER0_OVF_vect)
{
    TCNT0 = TIMER_RELOAD_CNT_1MS_PRESC_64;
    //unused, timing OK, PINB |= (1 << PIN_DBG1); // toggle

    // count ms, s
    if(timer_ms_tick.time.ms < 1000) {
        timer_ms_tick.time.ms++;
    }
    else {
        timer_ms_tick.time.ms = 0;
        timer_ms_tick.time.s++;
    }

    // repeated event: send event every xy ms?
    timer_tick_process_repeated(0);
    timer_tick_process_repeated(1);

    // single event
    if(timer_ms_tick.single_event.event) {
        if(timer_ms_tick.single_event.cnt_down_ms == 0) {
            SEND_EVENT(EV_TIMER);
            SEND_TIMER_EVENT(timer_ms_tick.single_event.event);
            timer_ms_tick.single_event.event = 0; // do only once
        }
        else {
            timer_ms_tick.single_event.cnt_down_ms--;
        }
    }
    // else inactive
}

// - public functions ----------------------------------------------------------
void timer_init(void) {
    timer_stop();
}

void timer_start_ms_tick(void) {
    timer_stop();
    timer_reset_ms_tick();
    
    TCCR0A = 0x00;
    TCNT0 = TIMER_RELOAD_CNT_1MS_PRESC_64;
    TIFR0 = (1<<TOV0);   // clear by wr 1
    TIMSK0 = (1<<TOIE0);
    TCCR0B = ((0<<CS02)|(1<<CS01)|(1<<CS00)); // run using precsaler 64, 8MHz / 64 / 125 = 1 ms

    PORTB &= ~(1 << 5);
}

void timer_reset_ms_tick(void) {
    uint8_t sr = SREG;
    cli();
    
    timer_ms_tick.time.ms = 0;
    timer_ms_tick.time.s = 0;
    
    SREG = sr;
}

void timer_start_ms_repeated_event(uint8_t ev_nr, uint16_t ms_cnt_dn, uint8_t timer_event) {
    uint8_t sr = SREG;
    cli();

    timer_ms_tick.repeated_event[ev_nr].cnt_down_ms = ms_cnt_dn;
    timer_ms_tick.repeated_event[ev_nr].cnt_down_ms_reload = ms_cnt_dn;
    timer_ms_tick.repeated_event[ev_nr].event = timer_event;

    SREG = sr;
}

void timer_stop_ms_repeated_event(uint8_t ev_nr) {
    uint8_t sr = SREG;
    cli();

    timer_ms_tick.repeated_event[ev_nr].cnt_down_ms = 0;
    timer_ms_tick.repeated_event[ev_nr].cnt_down_ms_reload = 0;
    timer_ms_tick.repeated_event[ev_nr].event = 0;

    SREG = sr;
}

void timer_start_ms_single_event(uint16_t delay_ms, uint8_t event) {
    uint8_t sr = SREG;
    cli();

    timer_ms_tick.single_event.cnt_down_ms = delay_ms;
    timer_ms_tick.single_event.event = event;

    SREG = sr;
}

void timer_stop_ms_single_event(void) {
    uint8_t sr = SREG;
    cli();

    timer_ms_tick.single_event.cnt_down_ms = 0;
    timer_ms_tick.single_event.event = 0;

    SREG = sr;
}
