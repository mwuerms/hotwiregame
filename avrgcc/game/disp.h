/**
 * Martin Egli
 * 2022-06-06
 *
 */

#ifndef _DISP_H_
#define _DISP_H_
// - includes ------------------------------------------------------------------
#include <stdint.h>
#include "macrolib.h"

// - definitions ---------------------------------------------------------------

// - public variables ----------------------------------------------------------
//extern const uint16_t decimal_place[];

// - public functions ----------------------------------------------------------
void disp_init(void);
void disp_clear(void);

void disp_game_state_wait_start(void);
void disp_game_state_wait_3(void);
void disp_game_state_wait_2(void);
void disp_game_state_wait_1(void);
void disp_game_state_race(void);
void disp_game_state_race_update(uint8_t time_s, uint8_t time_100ms, uint8_t penalty);
void disp_game_state_finish(void);

#endif /* _DISP_H_ */
