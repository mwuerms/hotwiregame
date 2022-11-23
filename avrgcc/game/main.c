/**
 * Martin Egli
 * 2022-06-06
 *
 * project on github: https://github.com/mwuerms/pwmgen
 * avr-gcc see: /usr/lib/avr
 * http://www.nongnu.org/avr-libc/user-manual/using_tools.html
 */

/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include <avr/interrupt.h>
#include <string.h>

#include "project.h"
#include "mcusleep.h"
#include "audio.h"
#include "gpio.h"
#include "game.h"
#include "wdt.h"
#include "timer.h"
#include "io.h"

/* - defines ---------------------------------------------------------------- */

/* - public variables ------------------------------------------------------- */
volatile uint8_t global_events;
volatile uint8_t global_gpio_events;
volatile uint8_t global_timer_events;

/**
 * main loop
 */
int main(void)
{
    uint8_t local_events = 0;
    uint8_t local_gpio_events = 0;
    uint8_t local_timer_events = 0;

    // init
    wdt_off();
    // 0: module enabled, 1: module in power reduction
    // use TWI, Timer0
    PRR = ((0 << PRTWI)|(1 << PRTIM2)|(0 << PRTIM0)|(1 << PRTIM1)|(1 << PRSPI)|(1 << PRUSART0)|(1 << PRADC));
    
    sleep_mode_init();
    use_sleep_mode(IDLE); // use Timer0

    DDRB |=   ((1 << PIN_DBG1)|(1 << PIN_INT_LED));
    PORTB &= ~((1 << PIN_DBG1)|(1 << PIN_INT_LED));

    gpio_init();
    //gpio_start_monitor_single(_BV(PIN_HOT_WIRE)|_BV(PIN_FINISH_POINT)|_BV(PIN_START_POINT));
    game_init();
    audio_init();

    timer_start_ms_tick();
    timer_start_ms_repeated_event(TIMER_EV_NR_GPIO, 10, EV_TIMER_POLL_GPIO);
    sei();

    // event loop
    while (1)
    {
        if (local_events & EV_GPIO)
        {
            PINB |= (1 << PIN_INT_LED);
            game_process_events(EV_GPIO, local_gpio_events);
        }
        if (local_events & EV_TIMER)
        {
            if(local_timer_events & EV_TIMER_POLL_GPIO) {
                gpio_poll_generate_events();
            }
            game_process_events(EV_TIMER, local_timer_events);
        }

        while (1)
        {
            cli();
            // check if there is a new event
            local_events = global_events;
            global_events = 0;
            local_gpio_events = global_gpio_events;
            global_gpio_events = 0;
            local_timer_events = global_timer_events;
            global_timer_events = 0;

            if (local_events)
            {
                sei();
                break;
            }
            // wait here for new event
            enter_sleep_mode();
        }
    }
    return (0);
}
