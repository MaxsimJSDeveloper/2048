#include "endgame.h"

/*
 * Determine if the game is over by checking for empty tiles
 * or any possible horizontal or vertical merges.
 */
bool mx_check_game_over(int board[5][5], int board_size)
{
    /* Look for any empty cells on the board. */
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == 0)
                return false;
        }
    }

    /* Check for possible horizontal merges between adjacent tiles. */
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size - 1; j++)
        {
            if (board[i][j] == board[i][j + 1])
                return false;
        }
    }

    /* Check for possible vertical merges between adjacent tiles. */
    for (int i = 0; i < board_size - 1; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == board[i + 1][j])
                return false;
        }
    }

    return true;
}
