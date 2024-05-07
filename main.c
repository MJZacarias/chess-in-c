#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "chess_output.h"
#include "doubly_linked_list_move_history.h"

void run_game()
{
    // Initialize the chessboard
    char board[8][8] = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};
    char taken_pieces[] = "                                                                ";
    int n_taken_pieces = 0;
    char input[5] = "    ";
    int turn = 1;
    struct DoublyLinkedListMoveHistory mv_hstry;
    initialize_list(&mv_hstry);

    print_board(board);
    printf("Enter next chess move (or 'quit'): ");
    scanf("%s", input);

    while (strcmp(input, "quit") != 0)
    {
        struct Move plyrs_mv = str_to_move(input);
        int correct_turn = color(board, plyrs_mv.from) == turn;
        char from_piece = board[plyrs_mv.from.row][plyrs_mv.from.col];
        char to_piece = board[plyrs_mv.to.row][plyrs_mv.to.col];
        if (correct_turn == 1 && move(board, taken_pieces, &n_taken_pieces, plyrs_mv) == 1)
        {
            append_move(&mv_hstry, plyrs_mv, from_piece, to_piece);
            turn *= -1;
            print_board(board);
        }
        else
        {
            printf("Move is not valid\n");
        }

        printf("Enter next chess move (or 'quit'): ");
        scanf("%s", input);
    }
    write_to_file(&mv_hstry);

    free_list(&mv_hstry);
}

int main()
{
    run_game();
    return 0;
}
