#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doubly_linked_list_move_history.h"
#include "chess.h"

void initialize_list(DoublyLinkedListMoveHistory *list)
{
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}
void insert_end(DoublyLinkedListMoveHistory *list, char move[7])
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->move, move);
    newNode->next = NULL;

    if (list->last == NULL)
    { // If list is empty
        newNode->prev = NULL;
        list->first = newNode;
        list->last = newNode;
    }
    else
    {
        newNode->prev = list->last;
        list->last->next = newNode;
        list->last = newNode;
    }
    list->size++;
}
void print_list(DoublyLinkedListMoveHistory *list)
{
    Node *current = list->first;
    printf("[");
    while (current != NULL)
    {
        printf("'%s', ", current->move);
        current = current->next;
    }
    printf("]");
}
void free_list(DoublyLinkedListMoveHistory *list)
{
    Node *current = list->first;
    Node *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}
void write_to_file(DoublyLinkedListMoveHistory *list)
{
    FILE *file = fopen("game_history.txt", "ac");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Get current date and time
    time_t currentTime;
    time(&currentTime);
    char *dateTimeStr = ctime(&currentTime);
    // Removing newline character from the end of the string
    dateTimeStr[strlen(dateTimeStr) - 1] = '\0';

    // Write current date and time to the file
    fprintf(file, "Date and Time: %s\n", dateTimeStr);

    Node *current = list->first;
    while (current != NULL)
    {
        fprintf(file, "%s\n", current->move);
        current = current->next;
    }

    fclose(file);
    printf("Values written to file successfully.\n");
}
void append_move(DoublyLinkedListMoveHistory *list, struct Move mv, const char from_piece, const char to_piece)
{
    char str_mv[7];
    str_mv[0] = mv.from.col + 97;
    str_mv[1] = mv.from.row + 49;
    str_mv[2] = from_piece;
    str_mv[3] = mv.to.col + 97;
    str_mv[4] = mv.to.row + 49;
    str_mv[5] = to_piece;
    insert_end(list, str_mv);
}
