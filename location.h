#ifndef LOCATION_H
#define LOCATION_H

// Structure to define a specific location on the chessboard
struct Location
{
    int row;
    int col;
};
// Print information on location
void print_location(struct Location lctn);
// Returns 1 if location not in board
int location_in_chess_board(struct Location lctn);
// Returns 1 if location on row 2 or 7
int location_on_second_row(struct Location lctn);

#endif // LOCATION_H