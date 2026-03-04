#include "endgame.h"

/*
 * Reset the game board to its initial state.
 * Sets all cells within the specified board size to zero.
 */
void mx_init_board(int board[5][5], int board_size)
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
            board[i][j] = 0;
    }
}
