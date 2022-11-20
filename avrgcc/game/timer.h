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

/*
    prescaler
       1: 8 000 000 Hz /    1 = 8 000 000.0 Hz = 0.125 us, OVF (256, 0...255) = 32 us
       8: 8 000 000 Hz /    8 = 1 000 000.0 Hz = 1 us,     OVF (256, 0...255) = 256 us
      64: 8 000 000 Hz /   64 =   125 000.0 Hz = 8 us,     OVF (256, 0...255) = 2.048 ms
     256: 8 000 000 Hz /  256 =    31 250.0 Hz = 32 us,    OVF (256, 0...255) = 8.192 ms
    1024: 8 000 000 Hz / 1024 =     7 812.5 Hz = 128 us,   OVF (256, 0...255) = 32.768 ms
    */
#define TIMER_PRESCALER_1 (1)
#define TIMER_PRESCALER_8 (2)
#define TIMER_PRESCALER_64 (3)
#define TIMER_PRESCALER_256 (4)
#define TIMER_PRESCALER_1024 (5)

// using TIMER_PRESCALER_1024
#define TIMER_NB_INTERVALS_1S (30) // 30.5175
#define TIMER_NB_INTERVALS_500MS (15) // 15.258

void timer_start(uint8_t cnt_nb_ovfs, uint8_t event);

#define timer_stop()    do { \
                            TCCR0B = 0x00; \
                            TIMSK0 = 0x00; \
                        } while(0)

#endif // _TIMER_H_