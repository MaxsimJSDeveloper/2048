#include "endgame.h"

/*
 * Shift all tiles to the left and merge identical adjacent tiles.
 * Updates the score and returns true if any movement or merging occurred.
 */
bool mx_move_left(int board[5][5], int *score, int board_size)
{
    bool moved = false;
    int packed[5];
    int result[5];
    int pos;
    int res_pos;
    int i;
    int j;

    for (i = 0; i < board_size; i++)
    {
        /* Initialize buffers for packing and final results. */
        for (j = 0; j < 5; j++)
        {
            packed[j] = 0;
            result[j] = 0;
        }
        pos = 0;
        res_pos = 0;

        /* Move all non-zero tiles to the left. */
        for (j = 0; j < board_size; j++)
        {
            if (board[i][j] != 0)
                packed[pos++] = board[i][j];
        }

        /* Merge identical adjacent tiles and update score. */
        for (j = 0; j < board_size - 1; j++)
        {
            if (packed[j] != 0 && packed[j] == packed[j + 1])
            {
                packed[j] *= 2;
                if (score)
                    *score += packed[j];
                packed[j + 1] = 0;
                j++;
            }
        }

        /* Repack tiles after merging to remove zeros. */
        for (j = 0; j < board_size; j++)
        {
            if (packed[j] != 0)
                result[res_pos++] = packed[j];
        }

        /* Update the board and check if any changes were made. */
        for (j = 0; j < board_size; j++)
        {
            if (board[i][j] != result[j])
                moved = true;
            board[i][j] = result[j];
        }
    }

    return moved;
}

/*
 * Reverse the elements of a single row.
 * Used as a helper for right-side movement logic.
 */
void mx_reverse_row(int row[5], int board_size)
{
    int temp;
    int j;

    for (j = 0; j < board_size / 2; j++)
    {
        temp = row[j];
        row[j] = row[board_size - 1 - j];
        row[board_size - 1 - j] = temp;
    }
}

/*
 * Reverse all rows on the board.
 */
void mx_reverse_board(int board[5][5], int board_size)
{
    int i;

    for (i = 0; i < board_size; i++)
        mx_reverse_row(board[i], board_size);
}

/*
 * Transpose the board matrix (swap rows and columns).
 * Used for vertical movement calculation.
 */
void mx_transpose_board(int board[5][5], int board_size)
{
    int temp;
    int i;
    int j;

    for (i = 0; i < board_size; i++)
    {
        for (j = i + 1; j < board_size; j++)
        {
            temp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = temp;
        }
    }
}

/*
 * Execute a move to the right by reversing, moving left, and reversing back.
 */
bool mx_move_right(int board[5][5], int *score, int board_size)
{
    bool moved;

    mx_reverse_board(board, board_size);
    moved = mx_move_left(board, score, board_size);
    mx_reverse_board(board, board_size);

    return moved;
}

/*
 * Execute a move up by transposing, moving left, and transposing back.
 */
bool mx_move_up(int board[5][5], int *score, int board_size)
{
    bool moved;

    mx_transpose_board(board, board_size);
    moved = mx_move_left(board, score, board_size);
    mx_transpose_board(board, board_size);

    return moved;
}

/*
 * Execute a move down by transposing, moving right, and transposing back.
 */
bool mx_move_down(int board[5][5], int *score, int board_size)
{
    bool moved;

    mx_transpose_board(board, board_size);
    moved = mx_move_right(board, score, board_size);
    mx_transpose_board(board, board_size);

    return moved;
}
