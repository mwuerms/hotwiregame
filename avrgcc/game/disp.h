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
void disp_game_state_ready(void);
void disp_game_state_set(void);
void disp_game_state_go(void);
void disp_game_state_race(void);
void disp_game_state_finish(void);

#endif /* _DISP_H_ */
