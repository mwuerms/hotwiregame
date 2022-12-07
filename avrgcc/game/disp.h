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
void disp_game_state_race_update(uint8_t secs, uint8_t millisecs, uint8_t penalty);
void disp_game_state_finish(char *str);


void disp_12(uint8_t ee, uint8_t pp, uint8_t acfe);

#endif /* _DISP_H_ */
