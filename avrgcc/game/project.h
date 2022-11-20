/**
 * Martin Egli
 * 2021-07-16
 *
 * basic project definitions
 */

#ifndef _PROJECT_H_
#define _PROJECT_H_
/* - includes --------------------------------------------------------------- */
#include <stdint.h>
#include "macrolib.h"

// - public definitions --------------------------------------------------------
#define PROGRAM_NAME "pwmgen"
#define AUTHOR_NAME "M.Egli"
#define PROGRAM_YEAR "2022"
//#define GIT_REPO_URL    "https://github.com/mwuerms/pwmgen"
#define GIT_REPO_URL "github.com/mwuerms"

#define RET_OK (0)
#define RET_ERR (1)

#define RET_AGAIN (RET_OK)
#define RET_STOP (RET_ERR)

/* - public variables ------------------------------------------------------- */
extern volatile uint8_t global_events;
#define EV_WAKEUP _BV(0)
#define EV_DISPLAY _BV(1) // also use global_display_events
#define EV_GPIO _BV(2)  // also use global_button_events

extern volatile uint8_t global_display_events;
#define EV_DISPLAY_NEXT _BV(0)
#define EV_DISPLAY_UPDATE_INFO _BV(1)

extern volatile uint8_t global_gpio_events;
#define EV_GPIO_HOT_WIRE_TOUCH _BV(0)
#define EV_GPIO_FINISH_POINT_TOUCH _BV(1)
#define EV_GPIO_START_POINT_TOUCH _BV(2)
#define EV_GPIO_START_POINT_RELEASE _BV(3)

#define SEND_EVENT(ev) global_events |= ev
#define SEND_DISPLAY_EVENT(ev) global_display_events |= ev
#define SEND_GPIO_EVENT(ev) global_gpio_events |= ev

/* - functions -------------------------------------------------------------- */

#endif /* _PROJECT_H_ */
