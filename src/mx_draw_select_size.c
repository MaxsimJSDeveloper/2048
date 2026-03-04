#include "endgame.h"

/*
 * Render the board size selection screen.
 * Displays options for 4x4 or 5x5 grids and shows the current player name.
 */
void mx_draw_select_size(t_game *game, t_resources *res)
{
    mx_draw_text_centered(res->bold_font, "SELECT BOARD SIZE", 150, 40, 2,
                          MAROON);
    mx_draw_text_centered(res->main_font,
                          TextFormat("PLAYER: %s", game->player_name),
                          220, 20, 2, DARKBLUE);
    mx_draw_text_centered(res->main_font, "Press [4] for 4x4", 300, 30, 2,
                          DARKGRAY);
    mx_draw_text_centered(res->main_font, "Press [5] for 5x5", 360, 30, 2,
                          DARKGRAY);
    mx_draw_text_centered(res->main_font, "BACKSPACE to return", 500, 15,
                          2, DARKGRAY);
}
