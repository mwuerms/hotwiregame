/**
 * Martin Egli
 * 2022-06-06
 *
 */

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include "project.h"
#include "game.h"
#include "disp.h"
#include "gpio.h"
#include "audio.h"
#include "timer.h"

// - defines -------------------------------------------------------------------
#define race_timer_start()  //timer_reset_ms_tick()

// - private variables ---------------------------------------------------------
static game_states_t game_state;

// - private functions ---------------------------------------------------------

// - public functions ----------------------------------------------------------
void game_init(void)
{
  disp_init();
  disp_clear();
  
  game_state = st_wait_start;
  disp_game_state_wait_start();
}

void game_process_events(uint8_t events, uint8_t detail_events)
{
  switch(game_state) {
    case st_wait_start:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_TOUCH) {
          game_state = st_ready;
          disp_game_state_ready();
          audio_on(1000, 500);
          timer_start_ms_single_event(1000, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_ready:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_state = st_wait_start;
          disp_game_state_wait_start();
          audio_off();
          timer_stop();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_state = st_set;
          disp_game_state_set();
          audio_on(1000, 500);
          timer_start_ms_single_event(1000, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_set:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_state = st_wait_start;
          disp_game_state_wait_start();
          audio_off();
          timer_stop();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_state = st_go;
          disp_game_state_go();
          audio_on(2000, 500);
          race_timer_start();
        }
      }
      break;
    case st_go:
      break;
    case st_race:
      break;
    case st_finish:
      break;
    default: ;
  }
}
