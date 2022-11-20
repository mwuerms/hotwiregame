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
void audio_on(uint16_t freq, uint16_t duration_ms);
void audio_off(void);

#endif /* _AUDIO_H_ */
