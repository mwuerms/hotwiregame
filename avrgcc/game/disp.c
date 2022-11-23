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

void disp_game_state_ready(void)
{
  lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 2);
  lcd_puts("  Ready");
  lcd_display();
}

void disp_game_state_set(void)
{
  lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 2);
  lcd_puts("  Set");
  lcd_display();
}

void disp_game_state_go(void)
{
  lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 2);
  lcd_puts("   GO!");
  lcd_display();
}

void disp_game_state_race(void)
{
  lcd_clrscr();
  lcd_charMode(DOUBLESIZE);
  lcd_gotoxy(0, 2);
  lcd_puts("   GO!");
  lcd_display();
}

void disp_game_state_finish(void)
{
}
