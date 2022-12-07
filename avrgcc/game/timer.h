/**
 * Martin Egli
 * 2022-11-20
 * 
 * use timer 0 to generate some timings
 */

#ifndef _TIMER_H_
#define _TIMER_H_

// - include -------------------------------------------------------------------
#include "project.h"

// - public functions ----------------------------------------------------------
void timer_init(void);
void timer_start_ms_tick(void);
void timer_reset_ms_tick(void);

#define TIMER_EV_NR_GPIO (0)
#define TIMER_EV_NR_GAME (1)
void timer_start_ms_repeated_event(uint8_t ev_nr, uint16_t ms_cnt_dn, uint8_t timer_event);
void timer_stop_ms_repeated_event(uint8_t ev_nr);
void timer_start_ms_single_event(uint8_t ev_nr, uint16_t delay_ms, uint8_t event);
void timer_stop_ms_single_event(uint8_t ev_nr);

#define timer_stop()    do { \
                            TCCR0B = 0x00; \
                            TIMSK0 = 0x00; \
                        } while(0)

#endif // _TIMER_H_