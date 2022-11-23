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

// - private variables ---------------------------------------------------------
static struct {
  game_states_t state;
  uint8_t penalty;
  uint8_t time_s, time_100ms;
} game_ctrl;

// - defines -------------------------------------------------------------------
#define race_timer_start(periode, ev)  timer_start_ms_repeated_event(TIMER_EV_NR_GAME, periode, ev)

// - private functions ---------------------------------------------------------

// - public functions ----------------------------------------------------------
void game_init(void)
{
  disp_init();
  disp_clear();
  
  game_ctrl.state = st_wait_start;
  disp_game_state_wait_start();
}

void game_process_events(uint8_t events, uint8_t detail_events)
{
  switch(game_ctrl.state) {
    case st_wait_start:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_TOUCH) {
          game_ctrl.state = st_wait_3;
          disp_game_state_wait_3();
          audio_on(1000, 500);
          timer_start_ms_single_event(1000, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_wait_3:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_ctrl.state = st_wait_start;
          disp_game_state_wait_start();
          audio_off();
          timer_stop_ms_single_event();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_ctrl.state = st_wait_2;
          disp_game_state_wait_2();
          audio_on(1000, 500);
          timer_start_ms_single_event(1000, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_wait_2:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_ctrl.state = st_wait_start;
          disp_game_state_wait_start();
          audio_off();
          timer_stop_ms_single_event();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_ctrl.state = st_wait_1;
          disp_game_state_wait_1();
          audio_on(1000, 500);
          timer_start_ms_single_event(1000, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_wait_1:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_ctrl.state = st_wait_start;
          disp_game_state_wait_start();
          audio_off();
          timer_stop_ms_single_event();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_ctrl.state = st_race;
          game_ctrl.time_s = 0;
          game_ctrl.time_100ms = 0;
          game_ctrl.penalty = 0;
          disp_game_state_race();
          audio_on(2000, 500);
          race_timer_start(100, EV_TIMER_GAME_UPDATE_DISP);
        }
      }
      break;
    case st_race:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_FINISH_POINT_TOUCH) {
          // stop game here
          game_ctrl.state = st_finish;
        }
        else if(detail_events & EV_GPIO_HOT_WIRE_TOUCH) {
          // touched wire -> penalty
          if(game_ctrl.penalty < 99) {
            game_ctrl.penalty++;
          }
          else {
            // max. reached, stop game 
            game_ctrl.state = st_finish; 
          }
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_UPDATE_DISP) {
          game_ctrl.state = st_race;
          if(game_ctrl.time_100ms < 10) {
            game_ctrl.time_100ms++;
          }
          else {
            game_ctrl.time_100ms = 0;
            if(game_ctrl.time_s < 99) {
              game_ctrl.time_s++;
            }
            else {
              // max. reached, stop game 
              game_ctrl.state = st_finish;
            }
          }
          disp_game_state_race_update(game_ctrl.time_s, game_ctrl.time_100ms, game_ctrl.penalty);
        }
      }
      break;
    case st_finish:
      break;
    default: ;
  }
}
