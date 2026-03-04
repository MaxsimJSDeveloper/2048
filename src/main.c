#include "endgame.h"

/*
 * Main function for the 2048: Endgame Edition.
 * Handles game loop, input processing, state updates, and rendering.
 */
int main(void)
{
    const int virtual_width = 800;
    const int virtual_height = 600;
    const char *random_names[] = {
        "CyberNinja", "PixelKnight", "C-Master",
        "BinaryGhost", "CodeWarrior", "RetroGamer"};

    /* Initialize window and system settings. */
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(virtual_width, virtual_height, "2048: Endgame Edition");
    SetTargetFPS(60);
    srand(time(NULL));

    /* Prepare virtual screen for scaling. */
    RenderTexture2D target = LoadRenderTexture(virtual_width, virtual_height);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    t_resources res = mx_load_resources();
    t_game game = {
        .state = STATE_MENU,
        .score = 0,
        .board_size = 4,
        .quit = false,
        .music_muted = false,
        .sfx_muted = false};

    game.high_score = mx_get_high_score();

    /* Main game loop. */
    while (!WindowShouldClose() && !game.quit)
    {
        /* Manage music stream and volume. */
        if (game.music_muted)
            SetMusicVolume(res.bg_music, 0.0f);
        else
            SetMusicVolume(res.bg_music, 0.5f);

        UpdateMusicStream(res.bg_music);

        /* Global input processing.
         * IsKeyPressed() consumes key state on first call — store results
         * in booleans before any processing, then flush the queue once. */
        bool key_p = IsKeyPressed(KEY_P);
        bool key_f11 = IsKeyPressed(KEY_F11);
        bool key_m = IsKeyPressed(KEY_M);
        bool key_n = IsKeyPressed(KEY_N);

        if (key_p)
        {
            if (game.state == STATE_GAMEPLAY)
                game.state = STATE_PAUSE;
            else if (game.state == STATE_PAUSE)
                game.state = STATE_GAMEPLAY;
        }

        if (key_f11)
            ToggleFullscreen();

        if (key_m)
            game.music_muted = !game.music_muted;

        if (key_n)
            game.sfx_muted = !game.sfx_muted;

        /* Flush queue so system keys don't leak into gameplay GetKeyPressed(). */
        if (key_p || key_f11 || key_m || key_n)
        {
            while (GetKeyPressed() > 0)
                ;
        }

        /* State management logic. */
        switch (game.state)
        {
        case STATE_MENU:
            if (IsKeyPressed(KEY_ENTER))
            {
                int r_idx = rand() % 6;
                snprintf(game.player_name, sizeof(game.player_name), "%s", random_names[r_idx]);
                game.state = STATE_SELECT_SIZE;
            }
            else if (IsKeyPressed(KEY_S))
            {
                game.state = STATE_SCOREBOARD;
            }
            break;

        case STATE_SELECT_SIZE:
        {
            bool key_four = IsKeyPressed(KEY_FOUR);
            bool key_five = IsKeyPressed(KEY_FIVE);
            if (key_four || key_five)
            {
                game.board_size = key_four ? 4 : 5;
                game.score = 0;
                mx_init_board(game.board, game.board_size);
                mx_spawn_tile(game.board, game.board_size);
                mx_spawn_tile(game.board, game.board_size);
                game.state = STATE_GAMEPLAY;
            }
            else if (IsKeyPressed(KEY_BACKSPACE))
            {
                game.state = STATE_MENU;
            }
            break;
        }

        case STATE_GAMEPLAY:
        {
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                mx_save_high_score(game.player_name, game.score);
                game.state = STATE_MENU;
            }

            int key = GetKeyPressed();
            if (key > 0)
            {
                int old_score = game.score;
                if (mx_apply_move(game.board, key, &game.score, game.board_size))
                {
                    if (game.score > old_score && !game.sfx_muted)
                        PlaySound(res.merge_sound);
                    else if (!game.sfx_muted)
                        PlaySound(res.move_sound);

                    mx_spawn_tile(game.board, game.board_size);
                    if (game.score > game.high_score)
                        game.high_score = game.score;

                    if (mx_check_win(game.board, game.board_size))
                    {
                        if (!game.sfx_muted)
                            PlaySound(res.win_sound);
                        game.state = STATE_WIN;
                        mx_save_high_score(game.player_name, game.score);
                    }
                    else if (mx_check_game_over(game.board, game.board_size))
                    {
                        if (!game.sfx_muted)
                            PlaySound(res.failure_sound);
                        game.state = STATE_GAMEOVER;
                        mx_save_high_score(game.player_name, game.score);
                    }
                }
            }
            break;
        }

        case STATE_SCOREBOARD:
            if (IsKeyPressed(KEY_BACKSPACE))
                game.state = STATE_MENU;
            break;

        case STATE_GAMEOVER:
        case STATE_WIN:
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_R))
                game.state = STATE_MENU;
            break;

        default:
            break;
        }

        /* Rendering process. */
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        if (game.state == STATE_MENU)
            mx_draw_menu(&game, &res);
        else if (game.state == STATE_SELECT_SIZE)
            mx_draw_select_size(&game, &res);
        else if (game.state == STATE_GAMEPLAY)
            mx_draw_game(&game, &res, game.board_size);
        else if (game.state == STATE_SCOREBOARD)
            mx_draw_scoreboard(&game, &res);
        else if (game.state == STATE_PAUSE)
        {
            mx_draw_game(&game, &res, game.board_size);
            mx_draw_pause(&game, &res);
        }
        else if (game.state == STATE_WIN)
            mx_draw_win(&game, &res);
        else if (game.state == STATE_GAMEOVER)
            mx_draw_gameover(&game, &res);

        mx_draw_sound_controls(&game, &res);
        EndTextureMode();

        /* Final screen output with scaling. */
        BeginDrawing();
        ClearBackground(BLACK);

        float s = fminf((float)GetScreenWidth() / virtual_width,
                        (float)GetScreenHeight() / virtual_height);
        Rectangle src = {0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height};
        Rectangle dst = {
            (GetScreenWidth() - ((float)virtual_width * s)) * 0.5f,
            (GetScreenHeight() - ((float)virtual_height * s)) * 0.5f,
            (float)virtual_width * s,
            (float)virtual_height * s};

        DrawTexturePro(target.texture, src, dst, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    /* Cleanup and resources unloading. */
    if (game.player_name[0] != '\0')
        mx_save_high_score(game.player_name, game.score);

    mx_unload_resources(&res);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
