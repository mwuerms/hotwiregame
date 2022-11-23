/**
 * Martin Egli
 * 2022-06-06
 *
 */

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "project.h"
#include "io.h"
#include "gpio.h"

/*#ifdef __AVR_ATmega328P__
#error ??__AVR_ATmega328P__
#endif*/

volatile struct {
  uint8_t monitor;
  uint8_t hot_wire_touch_cnt;
} gpio_ctrl;

#define GPIO_MONITOR_PIN_HOT_WIRE_SINGLE    (0)
#define GPIO_MONITOR_PIN_HOT_WIRE_REPEATED  _BV(PIN_HOT_WIRE)
#define GPIO_MONITOR_PIN_FINISH_POINT_SINGLE    (0)
#define GPIO_MONITOR_PIN_FINISH_POINT_REPEATED  _BV(PIN_FINISH_POINT)
#define GPIO_MONITOR_PIN_START_POINT_SINGLE    (0)
#define GPIO_MONITOR_PIN_START_POINT_REPEATED  _BV(PIN_START_POINT)

// PIN_HOT_WIRE, INT0
ISR(INT0_vect)
{
  if((gpio_ctrl.monitor & _BV(PIN_FINISH_POINT)) == 0) {
    // do monitor single
    EIMSK &= ~_BV(INT0);
  }
  gpio_ctrl.hot_wire_touch_cnt++;
  SEND_EVENT(EV_GPIO);
  SEND_GPIO_EVENT(EV_GPIO_HOT_WIRE_TOUCH);

  // tested: OK PINB |= (1 << PIN_DBG1); // toggle
}

// PIN_FINISH_POINT, INT1
ISR(INT1_vect)
{
  if((gpio_ctrl.monitor & _BV(PIN_FINISH_POINT)) == 0) {
    // do monitor single
    EIMSK &= ~_BV(INT1);
  }
  SEND_EVENT(EV_GPIO);
  SEND_GPIO_EVENT(EV_GPIO_FINISH_POINT_TOUCH);

  // tested: OK PINB |= (1 << PIN_DBG1); // toggle
}

// PIN_START_POINT, PD4, PCINT20
ISR(PCINT2_vect)
{
  if((gpio_ctrl.monitor & _BV(PIN_FINISH_POINT)) == 0) {
    // do monitor single
    PCICR &= ~_BV(PCIE2);
  }
  uint8_t start_in = PIND & _BV(PIN_START_POINT);

  if(start_in) {
    SEND_EVENT(EV_GPIO);
    SEND_GPIO_EVENT(EV_GPIO_START_POINT_RELEASE);
    PORTB &= ~_BV(PIN_INT_LED);
  }
  else {
    SEND_EVENT(EV_GPIO);
    SEND_GPIO_EVENT(EV_GPIO_START_POINT_TOUCH);
    PORTB |=  _BV(PIN_INT_LED);
  }
  // tested: OK PINB |= (1 << PIN_DBG1); // toggle
}

void gpio_init(void)
{
  // vars
  gpio_ctrl.monitor = 0;
  gpio_ctrl.hot_wire_touch_cnt = 0;

  // gpios
  DDRD &= ~(_BV(PIN_HOT_WIRE) | _BV(PIN_FINISH_POINT) | _BV(PIN_START_POINT));
  EICRA = (_BV(ISC11) | _BV(ISC01)); // INT0, INT1 on falling edge: touch
  //EIFR = (_BV(INTF0) | _BV(INTF1));
  //EIMSK = (_BV(INT0) | _BV(INT1));

  // PIN_START_POINT
  //PCIFR |= _BV(PCIF2); // clear
  //PCICR |= _BV(PCIE2);
  PCMSK2 |= (_BV(PCINT20));
}

void gpio_start_monitor_single(uint8_t gpio_mask) {
  if(gpio_mask & _BV(PIN_HOT_WIRE)) {
    gpio_ctrl.monitor &= ~_BV(PIN_HOT_WIRE); // single
    EIFR  |= _BV(INTF0); // clear
    EIMSK |= _BV(INT0);
  }
  if(gpio_mask & _BV(PIN_FINISH_POINT)) {
    gpio_ctrl.monitor &= ~_BV(PIN_FINISH_POINT); // single
    EIFR  |= _BV(INTF1); // clear 
    EIMSK |= _BV(INT1);
  }
  if(gpio_mask & _BV(PIN_START_POINT)) {
    gpio_ctrl.monitor &= ~_BV(PIN_FINISH_POINT); // single
    PCIFR |= _BV(PCIF2); // clear
    PCICR |= _BV(PCIE2);
  }
}

void gpio_stop_monitor(uint8_t gpio_mask) {
  if(gpio_mask & _BV(PIN_HOT_WIRE)) {
    EIFR  |=  _BV(INTF0); // clear
    EIMSK &= ~_BV(INT0);
  }
  if(gpio_mask & _BV(PIN_FINISH_POINT)) {
    EIFR  |=  _BV(INTF1); // clear 
    EIMSK &= ~_BV(INT1);
  }
  if(gpio_mask & _BV(PIN_START_POINT)) {
    PCIFR |=  _BV(PCIF2); // clear
    PCICR &= ~_BV(PCIE2);
  }
}
