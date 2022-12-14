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
game_states_t game_state;
static struct {
  uint8_t penalty;
  uint8_t time_s, time_100ms;
} game_race;

// - defines -------------------------------------------------------------------
#define race_timer_start(periode, ev)  timer_start_ms_repeated_event(TIMER_EV_NR_GAME, periode, ev)

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
          game_state = st_wait_3;
          disp_game_state_wait_3();
          audio_on_duration_ms(AUDIO_FREQ_A4_440Hz, 500);
          timer_start_ms_single_event(TIMER_EV_NR_GAME, 500, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_wait_3:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_state = st_wait_start;
          timer_stop_ms_single_event(TIMER_EV_NR_GAME);
          disp_game_state_wait_start();
          audio_off();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_state = st_wait_2;
          disp_game_state_wait_2();
          audio_on_duration_ms(AUDIO_FREQ_C5_523Hz, 500);
          timer_start_ms_single_event(TIMER_EV_NR_GAME, 500, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_wait_2:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_state = st_wait_start;
          timer_stop_ms_single_event(TIMER_EV_NR_GAME);
          disp_game_state_wait_start();
          audio_off();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_state = st_wait_1;
          disp_game_state_wait_1();
          audio_on_duration_ms(AUDIO_FREQ_E5_659Hz, 500);
          timer_start_ms_single_event(TIMER_EV_NR_GAME, 500, EV_TIMER_GAME_NEXT_STEP);
        }
      }
      break;
    case st_wait_1:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_RELEASE) {
          game_state = st_wait_start;
          timer_stop_ms_single_event(TIMER_EV_NR_GAME);
          disp_game_state_wait_start();
          audio_off();
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_NEXT_STEP) {
          game_state = st_race;
          game_race.time_s = 0;
          game_race.time_100ms = 0;
          game_race.penalty = 0;
          disp_game_state_race();
          audio_on_duration_ms(AUDIO_FREQ_A5_880Hz, 1000);
          race_timer_start(100, EV_TIMER_GAME_UPDATE_DISP);
        }
      }
      break;
    case st_race:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_FINISH_POINT_TOUCH) {
          // stop game here
          game_state = st_finish;
          disp_game_state_finish(" IM ZIEL  ");//"  FINISH  ");
          audio_on_duration_ms(AUDIO_FREQ_C6_1046Hz, 1000);
        }
        else if(detail_events & EV_GPIO_HOT_WIRE_TOUCH) {
          // touched wire -> penalty
          if(game_race.penalty < 99) {
            game_race.penalty++;
            audio_on_duration_ms(AUDIO_FREQ_BEEP_TOUCH, 500);
          }
          else {
            // max. reached, stop game 
            game_state = st_finish;
            disp_game_state_finish("  ZU OFT  ");
            audio_on_duration_ms(AUDIO_FREQ_FAIL_A5Bb6_923Hz, 1000);
          }
        }
      }
      else if(events & EV_TIMER) {
        if(detail_events & EV_TIMER_GAME_UPDATE_DISP) {
          PORTB |=  _BV(PIN_DBG1);
          game_state = st_race;
          if(game_race.time_100ms < 9) {
            game_race.time_100ms++;
          }
          else {
            game_race.time_100ms = 0;
            if(game_race.time_s < 99) {
              game_race.time_s++;
            }
            else {
              // max. reached, stop game 
              game_state = st_finish;
              disp_game_state_finish(" ZU LANGE ");
              audio_on_duration_ms(AUDIO_FREQ_FAIL_A5Bb6_923Hz, 1000);
            }
          }
          disp_game_state_race_update(game_race.time_s, game_race.time_100ms, game_race.penalty);
          PORTB &= ~_BV(PIN_DBG1);
        }
      }
      break;
    case st_finish:
      if(events & EV_GPIO) {
        if(detail_events & EV_GPIO_START_POINT_TOUCH) {
          game_state = st_wait_start;
          disp_game_state_wait_start();
        }
      }
      break;
    default: ;
  }
}
