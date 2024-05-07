#ifndef CHESS_H
#define CHESS_H
#include "move.h"

// return 1 if move out of bounds, move on itself, or moving a blank piece
int violates_dumb_chess_move_checks(char board[8][8], struct Move mv);
// return 1 if current location is black
int current_location_black(char board[8][8], struct Location lctn);
// return 1 if current location is white
int current_location_white(char board[8][8], struct Location lctn);
// return 1 if current location is blank
int current_location_is_blank(char board[8][8], struct Location lctn);
// return 1 if vertical path clear of pieces
int clear_path_in_vertical_move(char board[8][8], struct Move mv);
// return 1 if horizontal path clear of pieces
int clear_path_in_horizontal_move(char board[8][8], struct Move mv);
// moves the piece and takes the piece from the new location
void move_and_take(char board[8][8], char *taken_pieces, int *n_taken_pieces, struct Move mv);
// returns 1 if to and from pieces are not the same color
int move_locations_oppose_pieces(char board[8][8], struct Move mv);
// return 1 if diagonal path clear of pieces
int clear_path_in_diagonal_move(char board[8][8], struct Move mv);
// white = 1, blank = 0, black = -1
int color(char board[8][8], struct Location lctn);
// return 1 if able to move piece according to chess rules
int move(char board[8][8], char *taken_pieces, int *n_taken_pieces, struct Move mv);

#endif // CHESS_H