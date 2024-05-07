#include <stdio.h>
#include "chess.h"
#include "chess_output.h"

void print_legend()
{
    printf("Upper Case: Black Piece\n");
    printf("Lower Case: White Piece\n");
    printf("p: pawn\n");
    printf("r: rook\n");
    printf("n: knight\n");
    printf("b: bishop\n");
    printf("q: queen\n");
    printf("k: king\n");
}
void print_board(char board[8][8])
{
    printf("    ");
    for (int i = 0; i < 8; i++)
    {
        printf("--");
    }
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d | ", 9 - (i + 1));
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", board[7 - i][j]);
        }
        printf("|\n");
    }
    printf("    ");
    for (int i = 0; i < 8; i++)
    {
        printf("--");
    }
    printf("\n    ");
    for (int i = 0; i < 8; i++)
    {
        printf("%c ", 65 + i);
    }
    printf("\n");
}
void print_taken_pieces(char *taken_pieces)
{
    printf("taken_pieces = \"");
    for (int i = 0; i < 32; i++)
    {
        printf("%c", taken_pieces[i]);
    }
    printf("\"\n");
}