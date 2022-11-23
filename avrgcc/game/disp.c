/**
 * Martin Egli
 * 2022-06-06
 *
 */

/* - includes --------------------------------------------------------------- */
#include "disp.h"
#include "lcd.h"
#include "project.h"
#include "version.h"
#include "wdt.h"
#include <stdint.h>
#include "gpio.h"
#include "game.h"
#include "strlib.h"

// - private variables ---------------------------------------------------------
#define LINE_SIZE (23)
static char line[LINE_SIZE + 1]; // +1: '\0' at the end
static char num_str[12];
//static uint8_t num_len;

// - public functions ----------------------------------------------------------
void disp_init(void)
{
  // gpios
  // vars
  lcd_init(LCD_DISP_ON); // init lcd and turn on
  lcd_charMode(DOUBLESIZE);
}
void disp_clear(void)
{
  lcd_clrscr();
  lcd_display();
}

void disp_game_state_wait_start(void) {
  lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 0);
  lcd_puts("  Heisser");
  lcd_gotoxy(0, 2);
  lcd_puts("   Draht");
  lcd_gotoxy(0, 5);
  lcd_puts("goto start");
  lcd_display();
}

void disp_game_state_wait_3(void)
{
  lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 0);
  //       "3 2 1 GO! "
  lcd_puts("3         ");
  lcd_gotoxy(0, 2);
  //lcd_puts("0123456789");
  lcd_puts("          ");
  lcd_gotoxy(0, 4);
  lcd_puts("Touch     ");
  lcd_gotoxy(0, 6);
  lcd_puts("Time  0.0s");
  lcd_display();
}

void disp_game_state_wait_2(void)
{
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 0);
  //       "3 2 1 GO! "
  lcd_puts("  2       ");
  lcd_display();
}

void disp_game_state_wait_1(void)
{
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 0);
  //       "3 2 1 GO! "
  lcd_puts("    1     ");
  lcd_display();
}

void disp_game_state_race(void) {
  lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 0);
  //       "3 2 1 GO! "
  lcd_puts("      GO! ");
  lcd_gotoxy(0, 4);
  lcd_puts("Touch     ");
  lcd_gotoxy(0, 6);
  lcd_puts("Time  0.0s");
  lcd_display();
}
void disp_game_state_race_update(uint8_t secs, uint8_t millisecs, uint8_t penalty)
{
  char ms;
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 4);
  stringncopy(&line[0], "Touch    0", LINE_SIZE);
  int8_t_to_str(num_str, penalty, 2);
  stringncopy(&line[7], num_str, LINE_SIZE);
  lcd_puts(line);

  lcd_gotoxy(0, 6);
  stringncopy(&line[0], "Time  0.0s", LINE_SIZE);
  uint8_t_to_str(num_str, secs);
  line[4] = num_str[0];
  line[5] = num_str[1];
  line[6] = num_str[2];
  line[7] = '.';
  line[8] = millisecs + '0';
  line[9] = 's';
  line[10] = 0;
  lcd_puts(line);
  lcd_display();
}

void disp_game_state_finish(void)
{
}
