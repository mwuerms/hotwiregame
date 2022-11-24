/**
 * Martin Egli
 * 2022-06-06
 *
 * Timer1 as variable PWM output
 */

#ifndef _AUDIO_H_
#define _AUDIO_H_
/* - includes --------------------------------------------------------------- */

#include <stdint.h>

// - public MACROS -------------------------------------------------------------
void audio_init(void);

#define AUDIO_FREQ_BEEP_TOUCH_715Hz (715) // Hz 
#define AUDIO_FREQ_BEEP1_880Hz (880) // Hz
#define AUDIO_FREQ_BEEP2_932Hz (932) // Hz
void audio_on_duration_ms(uint16_t freq, uint16_t duration_ms);
void audio_off(void);

#endif /* _AUDIO_H_ */
