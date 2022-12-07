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

#define AUDIO_FREQ_BEEP_TOUCH (880) // Hz 
#define AUDIO_FREQ_A4_440Hz  (440)
#define AUDIO_FREQ_C5_523Hz  (523)
#define AUDIO_FREQ_E5_659Hz  (659)
#define AUDIO_FREQ_A5_880Hz (880)
#define AUDIO_FREQ_C6_1046Hz (1046)
#define AUDIO_FREQ_FAIL_A5Bb6_923Hz  (923)  // A5#/Bb6 

void audio_on_duration_ms(uint16_t freq, uint16_t duration_ms);
void audio_off(void);

#endif /* _AUDIO_H_ */
