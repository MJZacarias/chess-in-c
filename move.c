#include "move.h"

void print_move(struct Move mv)
{
    printf("mv={{%d, %d}, {%d, %d}};\n", mv.from.row, mv.from.col, mv.to.row, mv.to.col);
}
void print_move_str(struct Move mv)
{
    printf("mv={%c%d to %c%d};\n", mv.from.col + 97, mv.from.row + 1, mv.to.col + 97, mv.to.row + 1);
}
struct Move str_to_move(const char *coordinates_str)
{
    int from_col;
    int to_col;
    if (coordinates_str[0] > 96)
    {
        from_col = coordinates_str[0] - 97;
    }
    else
    {
        from_col = coordinates_str[0] - 65;
    }
    if (coordinates_str[2] > 96)
    {
        to_col = coordinates_str[2] - 97;
    }
    else
    {
        to_col = coordinates_str[2] - 65;
    }
    struct Move mv = {
        {coordinates_str[1] - '1', from_col},
        {coordinates_str[3] - '1', to_col}};
    // row col
    return mv;
}
