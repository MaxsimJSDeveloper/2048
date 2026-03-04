#include "endgame.h"

/*
 * Render the scoreboard screen showing the top record.
 * Retrieves the champion's name and score from the saved high score entry.
 */
void mx_draw_scoreboard(t_game *game, t_resources *res)
{
    char best_name[32];
    int best_score;

    (void)game;
    ClearBackground(RAYWHITE);
    mx_draw_text_centered(res->bold_font, "LEGENDARY RECORD", 100, 40, 2,
                          MAROON);
    mx_get_high_score_entry(best_name, sizeof(best_name), &best_score);
    DrawText(TextFormat("CHAMPION: %s", best_name), 180, 230, 30, DARKGRAY);
    DrawText(TextFormat("SCORE: %d points", best_score), 180, 290, 30, GOLD);
    mx_draw_text_centered(res->main_font, "PRESS [BACKSPACE] TO BACK", 520,
                          20, 2, LIGHTGRAY);
}
