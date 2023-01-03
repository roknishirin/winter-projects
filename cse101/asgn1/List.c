#include "List.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// structs  ------------------------------------------------------------------

// Creates and returns a new empty List.
typedef struct ListObj {
    int index; // the position of the cursor 
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

// Constructors-Destructors ------------------------------------------------
// Creates and returns a new empty List.
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    L->index = -1;
    L->cursor = NULL;
    return L;
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

// Creates and returns a new Node object.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return N;
}

// Frees all heap memory associated with *pN, and sets *pN to NULL.
void freeNode(Node *pN) {
    if (*pN != NULL && pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "length error\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "index error\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        return -1;
    }

    return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L) {
    if (L->length == 0 || L == NULL) {
        fprintf(stderr, "front error\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// Returns back element of L. Pre: length()>0
int back(List L) {
    if (L->length == 0 || L == NULL) {
        fprintf(stderr, "front error\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

int get(List L) {
    if (L == NULL || L->cursor == NULL || L->length == 0 || L->index < 0) {
        fprintf(stderr, "get error\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "equals error\n");
        exit(EXIT_FAILURE);
    }
    bool same = (A->length == B->length); // comparing list lengths 
    Node C = A->front;
    Node D = B->front;
    while (same && C != NULL) {
        same = (C->data == D->data); // comparing list values 
        C = C->next;
        D = D->next;
    }
    return same; 

}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "clear error\n");
        exit(EXIT_FAILURE);
    }
    while (L->length > 0) {
        deleteFront(L);
    }
    L->index = -1;
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
    if (L == NULL || L->length <= 0 || L->index < 0) {
        fprintf(stderr, "set error\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "moveFront error\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 0) { // do nothing if empty
        return;
    }

    L->cursor = L->front;
    L->index = 0;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "moveBack error\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 0) { // do nothing if empty
        return; 
    }
    L->cursor = L->back; 
    L->index = L->length - 1;
}

// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; 
// if cursor is undefined do nothing
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "movePrev error\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) { // undefined cursor -> do nothing
        return;
    }

    if (L->cursor == L->front) { // defined & at front
        L->cursor = NULL; // becomes undefined 
        L->index--;
        return;
    }

    if (L->cursor != L->front) { // defined & not at front
        L->cursor = L->cursor->prev;
        L->index--;
    }
}


// If cursor is defined and not at back, move cursor one step toward the back of L; 
// if cursor is defined and at back, cursor becomes undefined; 
// if cursor is undefined do nothing
void moveNext(List L) {
      if (L == NULL) {
        fprintf(stderr, "moveNext error\n");
        exit(EXIT_FAILURE);
    }  
    if (L->cursor == NULL) { // if cursor is undefined
        return;
    }
    if (L->cursor == L->back) { // if cursor is defined & at back
        L->cursor = NULL; // cursor becomes undefined 
        L->index--;
        return;
    }

    if (L->cursor != L->back) { // if cursor is defined & not at back
        L->cursor = L->cursor->next; // cursor takes step toward back
        L->index++;
    }
}



