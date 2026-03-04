#include "endgame.h"

/*
 * Load all game resources including textures, fonts, sounds, and music.
 * Initializes the audio device and sets up texture filtering for fonts.
 */
t_resources mx_load_resources(void)
{
    t_resources res;
    int i;
    int values[11] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
    const char *path;

    InitAudioDevice();
    for (i = 0; i < 11; i++)
    {
        path = TextFormat("resource/textures/tile_%d.png", values[i]);
        res.tile_textures[i] = LoadTexture(path);
    }

    /* Load and configure fonts with trilinear filtering. */
    res.bold_font = LoadFontEx("resource/fonts/Orbitron-Bold.ttf", 40, NULL, 0);
    res.main_font = LoadFontEx("resource/fonts/Orbitron-Regular.ttf", 20, NULL, 0);
    GenTextureMipmaps(&res.main_font.texture);
    SetTextureFilter(res.main_font.texture, TEXTURE_FILTER_TRILINEAR);
    GenTextureMipmaps(&res.bold_font.texture);
    SetTextureFilter(res.bold_font.texture, TEXTURE_FILTER_TRILINEAR);

    /* Load audio effects and start background music. */
    res.move_sound = LoadSound("resource/sounds/landslide.mp3");
    res.merge_sound = LoadSound("resource/sounds/merge.mp3");
    res.win_sound = LoadSound("resource/sounds/win.mp3");
    res.failure_sound = LoadSound("resource/sounds/failure.mp3");
    res.bg_music = LoadMusicStream("resource/sounds/bg_music.mp3");
    res.bg_music.looping = true;
    PlayMusicStream(res.bg_music);

    /* Load UI icons. */
    res.sound_on_icon = LoadTexture("resource/textures/sound_on.png");
    res.sound_off_icon = LoadTexture("resource/textures/sound_off.png");
    res.pause_icon = LoadTexture("resource/textures/button_pause.png");
    res.play_icon = LoadTexture("resource/textures/play_game.png");

    return res;
}
