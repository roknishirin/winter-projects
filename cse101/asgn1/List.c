#include "List.h"
#include <stdio.h>


// structs  ---------------------------------------------------------

// Creates and returns a new empty List.
typedef struct ListObj {
    int pos; // the position of the cursor 
    int length; // length
    Node front;
    Node back;
    Node cursor;

} ListObj;

typedef struct NodeObj {
    int data;
    Node next; // next node
    Node prev;  // previous node

} NodeObj;

// Constructors-Destructors -----------------------------------------
// Creates and returns a new empty List.
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    L->index = -1;
    L->cursor = NULL;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) {
    if (*pL != NULL && pL != NULL) {
        while (length(*pL) != 0) {
            clear(*pL);
        }
    }
    free(*pL);
    *pL = NULL;
}