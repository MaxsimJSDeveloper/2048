#include "endgame.h"

/*
 * Render the main game screen including the grid, tiles, and UI elements.
 */
void mx_draw_game(t_game *game, t_resources *res, int board_size)
{
    int bg_size = (board_size == 4) ? 450 : 440;
    int p_x = 20;
    int p_y = 80;
    int d_size = 40;
    Texture2D icon = (game->state == STATE_PAUSE) ? res->play_icon
                                                  : res->pause_icon;
    const char *hint = (game->state == STATE_PAUSE) ? "[P] RESUME"
                                                    : "[P] PAUSE";

    DrawRectangle(180, 100, bg_size, bg_size, DARKGRAY);

    /* Render score and high score in the left panel. */
    DrawTextEx(res->main_font, TextFormat("SCORE: %d", game->score),
               (Vector2){20, 20}, 20, 2, DARKGRAY);
    DrawTextEx(res->main_font, TextFormat("HIGH SCORE: %d", game->high_score),
               (Vector2){20, 50}, 20, 2, GOLD);

    /* Display status icon for pause or play state. */
    if (icon.id > 0)
    {
        Rectangle src = {0.0f, 0.0f, (float)icon.width, (float)icon.height};
        Rectangle dst = {(float)p_x, (float)p_y, (float)d_size, (float)d_size};

        DrawTexturePro(icon, src, dst, (Vector2){0, 0}, 0.0f, WHITE);
    }

    DrawTextEx(res->main_font, hint, (Vector2){(float)p_x + d_size + 10, (float)p_y + 10}, 18, 1, DARKGRAY);

    mx_draw_text_centered(res->bold_font, "2048: ENDGAME", 20, 30, 2, MAROON);

    /* Render player name in the right panel. */
    const char *p_label = TextFormat("PLAYER: %s", game->player_name);
    Vector2 l_size = MeasureTextEx(res->main_font, p_label, 18, 2);

    DrawTextEx(res->main_font, p_label, (Vector2){780 - l_size.x, 60},
               18, 2, DARKBLUE);

    /* Define grid parameters based on the board size. */
    int cell_size = (board_size == 4) ? 100 : 76;
    int step = (board_size == 4) ? 110 : 86;
    int f_size = (board_size == 4) ? 30 : 20;

    /* Iterate through the board to draw each tile. */
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            int val = game->board[i][j];
            int x = 190 + j * step;
            int y = 110 + i * step;

            if (val == 0)
            {
                DrawRectangle(x, y, cell_size, cell_size, LIGHTGRAY);
            }
            else
            {
                int idx = (int)log2(val) - 1;

                if (idx >= 0 && idx < 11 && res->tile_textures[idx].id > 0)
                {
                    Rectangle s = {0.0f, 0.0f, (float)res->tile_textures[idx].width,
                                   (float)res->tile_textures[idx].height};
                    Rectangle d = {(float)x, (float)y, (float)cell_size,
                                   (float)cell_size};

                    DrawTexturePro(res->tile_textures[idx], s, d,
                                   (Vector2){0, 0}, 0.0f, WHITE);
                }
                else
                {
                    /* Fallback for high values or missing textures. */
                    if (res->tile_textures[10].id > 0)
                    {
                        Rectangle s = {0.0f, 0.0f,
                                       (float)res->tile_textures[10].width,
                                       (float)res->tile_textures[10].height};
                        Rectangle d = {(float)x, (float)y, (float)cell_size,
                                       (float)cell_size};

                        DrawTexturePro(res->tile_textures[10], s, d,
                                       (Vector2){0, 0}, 0.0f, GOLD);
                    }
                    else
                        DrawRectangle(x, y, cell_size, cell_size, RAYWHITE);

                    const char *v_txt = TextFormat("%d", val);
                    Vector2 t_sz = MeasureTextEx(res->bold_font, v_txt, f_size, 2);

                    DrawTextEx(res->bold_font, v_txt, (Vector2){x + cell_size / 2 - t_sz.x / 2, y + cell_size / 2 - t_sz.y / 2},
                               f_size, 2, DARKGRAY);
                }
            }
        }
    }

    mx_draw_text_centered(res->main_font, "PRESS [BACKSPACE] TO EXIT TO MENU",
                          560, 18, 2, DARKGRAY);
}
