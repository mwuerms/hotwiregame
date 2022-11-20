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

/* - defines ---------------------------------------------------------------- */

/* - public variables ------------------------------------------------------- */
volatile uint8_t global_events;
volatile uint8_t global_display_events;
volatile uint8_t global_button_events;

/**
 * main loop
 */
int main(void)
{
    uint8_t local_events = 0;
    // init
    sleep_mode_init();
    use_sleep_mode(ACTIVE);

    gpio_init();
    game_init();
    audio_init();

    sei();

    // event loop
    while (1)
    {
        if (local_events & 1)
        {
        }

        while (1)
        {
            cli();
            // check if there is a new event
            local_events = global_events;
            global_events = 0;
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
