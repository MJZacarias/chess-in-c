#include "move.h"

void print_location(struct Location lctn)
{
    printf("lctn={%d, %d};\n", lctn.row, lctn.col);
}
int location_in_chess_board(struct Location lctn)
{
    if (!(0 <= lctn.row && lctn.row <= 7) || !(0 <= lctn.col && lctn.col <= 7))
    {
        print_location(lctn);
        return 1;
    }
    return 0;
}
int location_on_second_row(struct Location lctn)
{
    return (lctn.row == 1 || lctn.row == 6);
}
