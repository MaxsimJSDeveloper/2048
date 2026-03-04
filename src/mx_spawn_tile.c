#include "endgame.h"

/*
 * Find all empty cells on the board and randomly place a new tile.
 * The new tile has a 10% probability of being a '4' and 90% for a '2'.
 */
void mx_spawn_tile(int board[5][5], int board_size)
{
    t_coord empty_cells[25];
    int count;
    int random_idx;
    int r;
    int c;
    int i;
    int j;

    count = 0;
    for (i = 0; i < board_size; i++)
    {
        for (j = 0; j < board_size; j++)
        {
            if (board[i][j] == 0)
            {
                empty_cells[count].r = i;
                empty_cells[count].c = j;
                count++;
            }
        }
    }
    if (count == 0)
        return;
    random_idx = rand() % count;
    r = empty_cells[random_idx].r;
    c = empty_cells[random_idx].c;
    board[r][c] = (rand() % 10 == 0) ? 4 : 2;
}
