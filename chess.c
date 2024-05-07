#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "chess.h"
#include "chess_output.h"
#include "move.h"
#include "log.h"

int violates_dumb_chess_move_checks(char board[8][8], struct Move mv)
{
    if (location_in_chess_board(mv.from) || location_in_chess_board(mv.to) ||
        (mv.from.row == mv.to.row && mv.from.col == mv.to.col))
    {
        print_move(mv);
        write_to_log("violates_dumb_chess_move_checks() Move is either not in board or 'to' and 'from' is the same location");
        return 1;
    }
    else if (current_location_is_blank(board, mv.from))
    {
        write_to_log("violates_dumb_chess_move_checks() Can't move blank piece");
        return 1;
    }
    return 0;
}
int current_location_black(char board[8][8], struct Location lctn)
{
    return 'a' <= board[lctn.row][lctn.col] && board[lctn.row][lctn.col] <= 'z';
}
int current_location_white(char board[8][8], struct Location lctn)
{
    return 'A' <= board[lctn.row][lctn.col] && board[lctn.row][lctn.col] <= 'Z';
}
int current_location_is_blank(char board[8][8], struct Location lctn)
{
    return board[lctn.row][lctn.col] == ' ';
}
int color(char board[8][8], struct Location lctn)
{
    if (current_location_white(board, lctn))
    {
        return 1;
    }
    else if (current_location_black(board, lctn))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
int clear_path_in_diagonal_move(char board[8][8], struct Move mv)
{
    int row_direction = (mv.from.row > mv.to.row) ? -1 : 1;
    int col_direction = (mv.from.col > mv.to.col) ? -1 : 1;
    int row_size = abs(mv.from.row - mv.to.row);

    for (int i = 1; i < row_size; i++)
    {
        if (board[mv.from.row + i * row_direction][mv.from.col + i * col_direction] != ' ')
        {
            return 0;
        }
    }
    return 1;
}
int clear_path_in_vertical_move(char board[8][8], struct Move mv)
{
    int direction = (mv.from.row > mv.to.row) ? -1 : 1;
    for (int i = mv.from.row + direction; i != mv.to.row; i += direction)
    {
        if (board[i][mv.to.col] != ' ')
        {
            return 0;
        }
    }
    return 1;
}
int clear_path_in_horizontal_move(char board[8][8], struct Move mv)
{
    int direction = (mv.from.col > mv.to.col) ? -1 : 1;
    for (int i = mv.from.col + direction; i != mv.to.col; i += direction)
    {
        if (board[mv.to.row][i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}
void move_and_take(char board[8][8], char *taken_pieces, int *n_taken_pieces, struct Move mv)
{
    taken_pieces[(*n_taken_pieces)++] = board[mv.to.row][mv.to.col];
    board[mv.to.row][mv.to.col] = board[mv.from.row][mv.from.col];
    board[mv.from.row][mv.from.col] = ' ';
}
int move_locations_oppose_pieces(char board[8][8], struct Move mv)
{
    return (current_location_black(board, mv.from) && current_location_white(board, mv.to)) ||
           (current_location_white(board, mv.from) && current_location_black(board, mv.to));
}
int move(char board[8][8], char *taken_pieces, int *n_taken_pieces, struct Move mv)
{
    if (violates_dumb_chess_move_checks(board, mv))
    {
        return 0;
    }
    char current_piece = board[mv.from.row][mv.from.col];

    switch (tolower(current_piece))
    {
    case 'k': // King
        if (abs(mv.from.row - mv.to.row) <= 1 && abs(mv.from.col - mv.to.col) <= 1)
        {
            move_and_take(board, taken_pieces, n_taken_pieces, mv);
        }
        else
        {
            write_to_log("move() King can't move like that");
            return 0;
        }
        break;

    case 'q': // Queen
        if ((mv.from.row == mv.to.row && clear_path_in_horizontal_move(board, mv)) ||
            (mv.from.col == mv.to.col && clear_path_in_vertical_move(board, mv)) ||
            (abs(mv.from.row - mv.to.row) == abs(mv.from.col - mv.to.col) && clear_path_in_diagonal_move(board, mv)))
        {
            move_and_take(board, taken_pieces, n_taken_pieces, mv);
        }
        else
        {
            write_to_log("move() Queen can't move like that");
            return 0;
        }
        break;

    case 'r': // Rook
        if ((mv.from.row == mv.to.row && clear_path_in_horizontal_move(board, mv)) ||
            (mv.from.col == mv.to.col && clear_path_in_vertical_move(board, mv)))
        {
            move_and_take(board, taken_pieces, n_taken_pieces, mv);
        }
        else
        {
            write_to_log("move() Rook can't move like that");
            return 0;
        }
        break;

    case 'b': // Bishop
        if (abs(mv.from.row - mv.to.row) == abs(mv.from.col - mv.to.col) && clear_path_in_diagonal_move(board, mv))
        {
            move_and_take(board, taken_pieces, n_taken_pieces, mv);
        }
        else
        {
            write_to_log("move() Bishop can't move like that");
            return 0;
        }
        break;

    case 'n': // Knight
        if ((abs(mv.from.row - mv.to.row) == 2 && abs(mv.from.col - mv.to.col) == 1) ||
            (abs(mv.from.row - mv.to.row) == 1 && abs(mv.from.col - mv.to.col) == 2))
        {
            move_and_take(board, taken_pieces, n_taken_pieces, mv);
        }
        else
        {
            write_to_log("move() Knight can't move like that");
            return 0;
        }
        break;

    case 'p': // Pawn
        if (color(board, mv.from) == 1)
        { // White
            // Move two spaces forward
            if (mv.from.row == 1 && mv.to.row == 3 && mv.from.col == mv.to.col && clear_path_in_vertical_move(board, mv))
            {
                move_and_take(board, taken_pieces, n_taken_pieces, mv);
            }
            // Move one space forward
            else if (mv.to.row == mv.from.row + 1 && mv.from.col == mv.to.col && current_location_is_blank(board, mv.to))
            {
                move_and_take(board, taken_pieces, n_taken_pieces, mv);
            }
            // Take diagnoal piece
            else if (mv.to.row == mv.from.row + 1 && abs(mv.to.col - mv.from.col) == 1 && move_locations_oppose_pieces(board, mv))
            {
                move_and_take(board, taken_pieces, n_taken_pieces, mv);
            }
            else
            {
                write_to_log("move() white Pawn can't move like that");
                return 0;
            }
        }
        else
        { // Black
            // Move two spaces forward
            if (mv.from.row == 6 && mv.to.row == 4 && mv.from.col == mv.to.col && clear_path_in_vertical_move(board, mv))
            {
                move_and_take(board, taken_pieces, n_taken_pieces, mv);
            }
            // Move one space forward
            else if (mv.to.row == mv.from.row - 1 && mv.from.col == mv.to.col && current_location_is_blank(board, mv.to))
            {
                move_and_take(board, taken_pieces, n_taken_pieces, mv);
            }
            // Take diagnoal piece
            else if (mv.to.row == mv.from.row - 1 && abs(mv.to.col - mv.from.col) == 1 && move_locations_oppose_pieces(board, mv))
            {
                move_and_take(board, taken_pieces, n_taken_pieces, mv);
            }
            else
            {
                write_to_log("move() black Pawn can't move like that");
                return 0;
            }
        }
        break;
    }
    return 1;
}
