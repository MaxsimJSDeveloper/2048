#include "endgame.h"

/*
 * Render the main menu screen of the game.
 * Displays the title and primary navigation options.
 */
void mx_draw_menu(t_game *game, t_resources *res)
{
    (void)game;

    mx_draw_text_centered(res->bold_font, "2048: ENDGAME", 200, 50, 2,
                          MAROON);
    mx_draw_text_centered(res->main_font, "PRESS ENTER TO START", 300, 20,
                          2, DARKGRAY);
    mx_draw_text_centered(res->main_font, "[S] SCOREBOARD", 380, 20, 2,
                          DARKGRAY);
    mx_draw_text_centered(res->main_font, "Press [Esc] to Quit", 540, 18,
                          2, DARKGRAY);
}
