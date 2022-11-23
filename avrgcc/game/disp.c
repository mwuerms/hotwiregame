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
  lcd_puts("0123456789");
  lcd_gotoxy(0, 4);
  lcd_puts("Penalty: X");
  lcd_gotoxy(0, 6);
  lcd_puts("Time: 0.0s");
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
  lcd_puts("Penalty: X");
  lcd_gotoxy(0, 6);
  lcd_puts("Time: 0.0s");
  lcd_display();
}
void disp_game_state_race_update(uint8_t time_s, uint8_t time_100ms, uint8_t penalty)
{
  //lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 0);
  //lcd_puts("   GO!");
  lcd_display();
}

void disp_game_state_finish(void)
{
}
