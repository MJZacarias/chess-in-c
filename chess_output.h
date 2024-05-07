#ifndef CHESS_OUTPUT_H
#define CHESS_OUTPUT_H

// Print the legend for understanding board symbols
void print_legend();
// Print the current state of the board
void print_board(char board[8][8]);
// Print the pieces that have been taken
void print_taken_pieces(char *taken_pieces);

#endif // CHESS_OUTPUT_H