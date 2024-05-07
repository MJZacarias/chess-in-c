#ifndef MOVE_H
#define MOVE_H
#include "location.h"

// Structure to define a move with starting and ending positions
struct Move
{
    struct Location from;
    struct Location to;
};
// Print information about a move
void print_move(struct Move mv);
// Print a move as coordinates (e.g., e2e4)
void print_move_str(struct Move mv);
// Converts string (e.g., e2E4) to struct Move (Move = {{1,4},{3,4}})
struct Move str_to_move(const char *coordinates_str);

#endif // MOVE_H