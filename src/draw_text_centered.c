#include "endgame.h"

/*
 * Calculate the horizontal center and render text using the specified font.
 * The center is calculated based on a fixed virtual width of 800 pixels.
 */
void mx_draw_text_centered(Font font, const char *text, float y,
                           float font_size, float spacing, Color color)
{
    Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    int x = (int)((800.0f - text_size.x) / 2.0f);
    int iy = (int)y;

    DrawTextEx(font, text, (Vector2){(float)x, (float)iy}, font_size,
               spacing, color);
}
