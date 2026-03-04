#include "endgame.h"

/*
 * Process the movement direction based on the provided key code.
 * Delegates the board transformation to specific movement functions.
 */
bool mx_apply_move(int board[5][5], int dir, int *score, int board_size)
{
    switch (dir)
    {
    case KEY_W: // fallthrough
    case KEY_UP:
        return mx_move_up(board, score, board_size);

    case KEY_S: // fallthrough
    case KEY_DOWN:
        return mx_move_down(board, score, board_size);

    case KEY_A: // fallthrough
    case KEY_LEFT:
        return mx_move_left(board, score, board_size);

    case KEY_D: // fallthrough
    case KEY_RIGHT:
        return mx_move_right(board, score, board_size);

    default:
        break;
    }

    return false;
}
