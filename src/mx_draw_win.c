#include "endgame.h"

/*
 * Render the victory screen.
 * Displays the player's name along with their final winning score.
 */
void mx_draw_win(t_game *game, t_resources *res)
{
    const char *stats = TextFormat("%s, YOUR SCORE: %d", game->player_name,
                                   game->score);

    mx_draw_text_centered(res->bold_font, "YOU WON!", 200, 50, 2, GOLD);
    mx_draw_text_centered(res->main_font, stats, 270, 30, 2, DARKGRAY);
    mx_draw_text_centered(res->main_font, "Press [Enter] to Menu", 400, 20,
                          2, LIGHTGRAY);
}
