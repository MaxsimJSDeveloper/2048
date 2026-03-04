#include "endgame.h"

/*
 * Render the game over screen.
 * Displays the final score and navigation instructions.
 */
void mx_draw_gameover(t_game *game, t_resources *res)
{
    const char *score_txt = TextFormat("FINAL SCORE: %d", game->score);

    mx_draw_text_centered(res->bold_font, "GAME OVER", 250, 40, 2, RED);
    mx_draw_text_centered(res->main_font, score_txt, 300, 20, 2, DARKGRAY);
    mx_draw_text_centered(res->main_font, "Press [Enter] to Menu", 340, 20,
                          2, LIGHTGRAY);
}
