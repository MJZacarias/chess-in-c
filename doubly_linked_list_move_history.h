#ifndef DOUBLY_LINKED_LIST_MOVE_HISTORY_H
#define DOUBLY_LINKED_LIST_MOVE_HISTORY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"

typedef struct Node
{
    char move[7];
    struct Node *prev;
    struct Node *next;
} Node;
typedef struct DoublyLinkedListMoveHistory
{
    Node *first;
    Node *last;
    int size;
} DoublyLinkedListMoveHistory;
// Function to initialize the doubly linked list
void initialize_list(DoublyLinkedListMoveHistory *list);
// Function to insert a new element at the end of the list
void insert_end(DoublyLinkedListMoveHistory *list, char move[7]);
// Function to print the elements of the list
void print_list(DoublyLinkedListMoveHistory *list);
// Function to free memory allocated for the nodes in the list
void free_list(DoublyLinkedListMoveHistory *list);
// Function to write all values of the linked list to a file
void write_to_file(DoublyLinkedListMoveHistory *list);
// Function to add move to linked list
void append_move(DoublyLinkedListMoveHistory *list, struct Move mv, char from_piece, char to_piece);

#endif // DOUBLY_LINKED_LIST_MOVE_HISTORY_H