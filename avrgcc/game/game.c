/**
 * Martin Egli
 * 2022-06-06
 *
 */

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include "project.h"
#include "game.h"
#include "disp_draw.h"
#include "gpio.h"
#include "audio.h"

// - defines -------------------------------------------------------------------

// - private variables ---------------------------------------------------------
static game_states_t game_state;

// - private functions ---------------------------------------------------------

// - public functions ----------------------------------------------------------
void game_init(void)
{
  disp_draw_init();
}

void game_process_events(uint8_t events, uint8_t detail_events)
{
  if (events & EV_DISPLAY)
  {
  }
}
