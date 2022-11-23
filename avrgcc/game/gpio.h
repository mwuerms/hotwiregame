/**
 * Martin Egli
 * 2022-06-06
 *
 */

#ifndef _GPIO_H_
#define _GPIO_H_
/* - includes --------------------------------------------------------------- */
#include "io.h"

// - public functions ----------------------------------------------------------
void gpio_init(void);

// use any combination of _BV(PIN_HOT_WIRE) | _BV(PIN_FINISH_POINT) | _BV(PIN_START_POINT)
void gpio_start_monitor_single(uint8_t gpio_mask);
void gpio_stop_monitor(uint8_t gpio_mask);
void gpio_poll_generate_events(void);

#endif /* _GPIO_H_ */