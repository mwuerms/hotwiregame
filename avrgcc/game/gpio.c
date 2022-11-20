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

volatile uint8_t button_on_cnt;
volatile uint8_t button_wheel_cnt;
volatile int8_t wheel_cnt;

// PIN_HOT_WIRE, INT0
ISR(INT0_vect)
{
  button_on_cnt++;
  SEND_EVENT(EV_GPIO);
  SEND_GPIO_EVENT(EV_GPIO_HOT_WIRE_TOUCH);
}

// PIN_FINISH_POINT, INT1
ISR(INT1_vect)
{
  button_wheel_cnt++;
  SEND_EVENT(EV_GPIO);
  SEND_GPIO_EVENT(EV_GPIO_FINISH_POINT_TOUCH);
}

// PIN_START_POINT, PD4, PCINT20
ISR(PCINT1_vect)
{
  uint8_t start_in = PIND & _BV(PIN_START_POINT);
  cli();

  if(start_in) {
    SEND_EVENT(EV_GPIO);
    SEND_GPIO_EVENT(EV_GPIO_START_POINT_RELEASE);
  }
  else {
    SEND_EVENT(EV_GPIO);
    SEND_GPIO_EVENT(EV_GPIO_START_POINT_TOUCH);
  }

  sei();
}

void gpio_init(void)
{
  // vars
  button_on_cnt = 0;
  button_wheel_cnt = 0;
  wheel_cnt = 0;

  // gpios
  DDRD &= ~(_BV(PIN_HOT_WIRE) | _BV(PIN_FINISH_POINT) | _BV(PIN_START_POINT));
  EICRA = (_BV(ISC11) | _BV(ISC01)); // INT0, INT1 on falling edge = button pressed
  EIFR = (_BV(INTF0) | _BV(INTF1));
  EIMSK = (_BV(INT0) | _BV(INT1));

  // PIN_START_POINT
  PCIFR |= _BV(PCIF2); // clear
  PCICR |= _BV(PCIE2);
  PCMSK2 |= (_BV(PCINT20));
}