/**
 * Martin Egli
 * 2022-06-06
 *
 */

#ifndef _GAME_H_
#define _GAME_H_
/* - includes --------------------------------------------------------------- */
#include <stdint.h>

typedef enum {
  st_init = 0,
  st_wait_start,
  st_ready,
  st_set,
  st_go,
  st_race,
  st_finish,
} game_states_t;

// - public functions ----------------------------------------------------------
void game_init(void);
void game_process_events(uint8_t events, uint8_t btn_events);

#endif /* _GAME_H_ */
