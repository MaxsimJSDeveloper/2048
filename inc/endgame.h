#ifndef ENDGAME_H
#define ENDGAME_H

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef enum e_state
{
    STATE_MENU,
    STATE_SELECT_SIZE,
    STATE_GAMEPLAY,
    STATE_PAUSE,
    STATE_WIN,
    STATE_GAMEOVER,
    STATE_SCOREBOARD
} t_state;

typedef struct s_coord
{
    int r;
    int c;
} t_coord;

typedef struct s_game
{
    int board[5][5];
    int board_size;
    int score;
    int high_score;
    char player_name[32];
    t_state state;
    bool quit;
    bool music_muted;
    bool sfx_muted;
} t_game;

typedef struct s_resources
{
    Font main_font;
    Font bold_font;
    Sound move_sound;
    Sound merge_sound;
    Sound win_sound;
    Music bg_music;
    Sound failure_sound;
    Texture2D tile_textures[11];
    Texture2D sound_on_icon;
    Texture2D sound_off_icon;
    Texture2D pause_icon;
    Texture2D play_icon;
} t_resources;

/* Grid and Spawn management. */
void mx_init_board(int board[5][5], int board_size);
void mx_spawn_tile(int board[5][5], int board_size);

/* Logic and Movement. */
bool mx_apply_move(int board[5][5], int dir, int *score, int board_size);
bool mx_check_game_over(int board[5][5], int board_size);
bool mx_move_left(int board[5][5], int *score, int board_size);
bool mx_move_right(int board[5][5], int *score, int board_size);
bool mx_move_up(int board[5][5], int *score, int board_size);
bool mx_move_down(int board[5][5], int *score, int board_size);
void mx_transpose_board(int board[5][5], int board_size);
void mx_reverse_board(int board[5][5], int board_size);

/* Score and Persistence. */
void mx_save_high_score(const char *name, int score);
int mx_get_high_score(void);
bool mx_check_win(int board[5][5], int size);
void mx_get_high_score_entry(char *name, int name_size, int *score);

/* Drawing functions. */
void mx_draw_menu(t_game *game, t_resources *res);
void mx_draw_game(t_game *game, t_resources *res, int board_size);
void mx_draw_pause(t_game *game, t_resources *res);
void mx_draw_scoreboard(t_game *game, t_resources *res);
void mx_draw_win(t_game *game, t_resources *res);
void mx_draw_gameover(t_game *game, t_resources *res);
void mx_draw_sound_controls(t_game *game, t_resources *res);
void mx_draw_select_size(t_game *game, t_resources *res);
void mx_draw_text_centered(Font font, const char *text, float y,
                           float font_size, float spacing, Color color);

/* Resource management. */
t_resources mx_load_resources(void);
void mx_unload_resources(t_resources *res);

#endif
