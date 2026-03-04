#include "endgame.h"

/*
 * Release all allocated game resources and shut down the audio system.
 * This function iterates through textures, sounds, and fonts to free memory.
 */
void mx_unload_resources(t_resources *res)
{
    int i;

    for (i = 0; i < 11; i++)
    {
        if (res->tile_textures[i].id > 0)
            UnloadTexture(res->tile_textures[i]);
    }

    /* Unload audio effects and music stream. */
    UnloadSound(res->move_sound);
    UnloadSound(res->merge_sound);
    UnloadSound(res->win_sound);
    UnloadSound(res->failure_sound);
    UnloadMusicStream(res->bg_music);

    /* Unload fonts and UI textures. */
    UnloadFont(res->main_font);
    UnloadFont(res->bold_font);
    UnloadTexture(res->sound_on_icon);
    UnloadTexture(res->sound_off_icon);
    UnloadTexture(res->pause_icon);
    UnloadTexture(res->play_icon);

    CloseAudioDevice();
}
