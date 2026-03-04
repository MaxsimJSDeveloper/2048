#include "endgame.h"

/*
 * Render music and sound effects control icons at the top-right corner.
 * Displays different icons based on the current mute status of the game.
 */
void mx_draw_sound_controls(t_game *game, t_resources *res)
{
    float scale = 0.06f;
    int size = 32;
    int gap = 24;
    int y = 10;
    int start_x = 680;
    int sec_x = start_x + size + gap;
    Texture2D m_icon = game->music_muted ? res->sound_off_icon
                                         : res->sound_on_icon;
    Texture2D s_icon = game->sfx_muted ? res->sound_off_icon
                                       : res->sound_on_icon;

    DrawTextureEx(m_icon, (Vector2){(float)start_x, (float)y}, 0.0f,
                  scale, WHITE);
    DrawTextEx(res->main_font, "M", (Vector2){(float)start_x + size + 5, (float)y + 5}, 18, 1, DARKGRAY);
    DrawTextureEx(s_icon, (Vector2){(float)sec_x, (float)y}, 0.0f,
                  scale, WHITE);
    DrawTextEx(res->main_font, "N", (Vector2){(float)sec_x + size + 5, (float)y + 5}, 18, 1, DARKGRAY);
}
