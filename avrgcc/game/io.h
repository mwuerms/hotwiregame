/**
 * Martin Egli
 * 2022-06-06
 *
 * define all ios for this project
 */

#ifndef _IO_H_
#define _IO_H_
/* - includes --------------------------------------------------------------- */

// AUDIO, PORTB
#define PIN_AUDIO_PWM (1) // D9, variable pwm signal, audio tones

// ISP PORTB: 3, 4, 5

// XTAL, PORTB
#define PIN_XTAL1 (6)
#define PIN_XTAL2 (7)

// rotary encoder PORTC
#define PIN_WHEEL_A (0) // A0, PCINT8, rotary encoder signal A
#define PIN_WHEEL_B (1) // A1, PCINT9, rotary encoder signal B

// OLED I2C, PORTC
#define PIN_OLED_SDA (4) // A5
#define PIN_OLED_SCL (5) // A4

// UART PORTD
#define PIN_RXD (0)
#define PIN_TXD (1)

// Buttons PORTD
#define PIN_HOT_WIRE (2) // D2, INT0, PCINT18,  when the hot wire makes contact
#define PIN_FINISH_POINT (3)  // D3, INT1, PCINT19,  contact of finishing line
#define PIN_START_POINT (4)  // D4, PCINT20, contact of start potision

#endif /* _IO_H_ */