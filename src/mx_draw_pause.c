#include "endgame.h"

/*
 * Render the pause overlay on top of the current game state.
 * Uses a semi-transparent rectangle to dim the background.
 */
void mx_draw_pause(t_game *game, t_resources *res)
{
    (void)game;

    DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.3f));
    mx_draw_text_centered(res->bold_font, "PAUSED", 250, 40, 2, WHITE);
    mx_draw_text_centered(res->main_font, "PRESS 'P' TO RESUME", 300, 20,
                          2, LIGHTGRAY);
}
