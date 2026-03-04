#include "endgame.h"

/*
 * Scan the entire board to determine if the player has achieved victory.
 * Returns true if a tile with the value 2048 is found.
 */
bool mx_check_win(int board[5][5], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 2048)
                return true;
        }
    }

    return false;
}
