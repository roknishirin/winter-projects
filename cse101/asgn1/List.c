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

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
    if (L == NULL || L->length == 0 || L->index < 0) {
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

    if (L->length > 0) { // do nothing if empty
        L->cursor = L->front;
        L->index = 0;
    } 
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "moveBack error\n");
        exit(EXIT_FAILURE);
    }

    if (L->length > 0) { // do nothing if empty
        L->cursor = L->back; 
        L->index = L->length - 1;
    }
}

// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; 
// if cursor is undefined do nothing
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "movePrev error\n");
        exit(EXIT_FAILURE);
    }

    if (L->index == -1) { // undefined cursor -> do nothing
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
    if (L->index == -1) { // if cursor is undefined
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

// Insert new element into L. 
// If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "prepend error\n");
        exit(EXIT_FAILURE);
    }
    Node temp = newNode(x);

    // adding a new node if empty
    if (L->length == 0) { 
        L->front = temp;
        L->back = temp;
    } else { 
        temp->next = L->front; 
        L->front->prev = temp;
        L->front = temp;
        if (L->cursor != NULL) {
            L->index++;
        }
    }
    L->length++;
}


 // Insert new element into L. 
 // If L is non-empty, insertion takes place after back element.
 void append(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "prepend error\n");
        exit(EXIT_FAILURE);
    }
    Node temp = newNode(x);
    if (L->length == 0) {
        L->front = temp;
        L->back = temp;
    } else {
        temp->prev = L->back;
        L->back->next = temp;
        L->back = temp;
    }
    L->length++;
 }

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    if (L == NULL || L->length == 0 || L->index < 0) {
        fprintf(stderr, "insertBefore error\n");
        exit(EXIT_FAILURE);
    }
    Node temp = newNode(x);
    if (L->index == 0) {
        temp->next = L->front;
        L->front->prev = temp;
        L->front = temp;
    } else {
        L->cursor->prev->next = temp;
        temp->prev = L->cursor->prev;
        temp->next = L->cursor;
        L->cursor->prev = temp;
    }
    L->index++;
    L->length++;
}

// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if (L == NULL || L->index < 0 || L->length <= 0) {
        fprintf(stderr, "insertAfter error\n");
        exit(EXIT_FAILURE);
    }
    Node temp = newNode(x);
    if (L->cursor == L->back) {
        temp->prev = L->back;
        L->back->next = temp;
        L->back = temp;
    } else {
        L->cursor->next->prev = temp;
        temp->next = L->cursor->next;
        temp->prev = L->cursor;
        L->cursor->next = temp;
    }
    L->length++;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL || L->length <= 0) {
        fprintf(stderr, "deleteFront error\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->front;
    if (L->length == 1) {
        L->index = -1;
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
    }
    else {
        if (L->front == L->cursor) {
            L->front = L->front->next;
            L->cursor = NULL;
        } else { 
            L->front = L->front->next;
        }
        L->index--;
    }
    L->length--;
    freeNode(&temp);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL || L->length <= 0) {
        fprintf(stderr, "deleteFront error\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->back;
    if (L->length == 1) {
        L->index = -1;
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
    } else {
        if (L->cursor == temp) {
            L->cursor = NULL;
            L->index--;
        }
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    L->length--;
    freeNode(&temp);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "delete error\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL  || L->length == 0 || L->index == -1) {
        return;
    }

    if (L->length == 1) { // if only one thing in the list
        freeNode(&L->front);
        L->front = NULL;
        L->back = NULL;
    } else if (L->front == L->cursor) {
        L->front = L->front->next;
        L->front->prev = NULL;
    } else if (L->back == L->cursor) {
       L->back = L->back->prev;
       L->back->next = NULL;
    } else {
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
    }
    freeNode(&L->cursor);
    L->index--;
    L->length--;
}


// other operations -----------------------------------------------------

// Prints to the file pointed to by out, 
// a string representation of L consisting of a space 
// separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
    Node temp = NULL;
    for (temp = L->front; temp != NULL; temp = temp->next) {
        fprintf(out, "%d ", temp->data);
    }
    //fprintf(out, "\n");
}

// Returns a new List representing the same integer sequence as L. 
// The cursor in the new list is undefined, regardless of the state of the cursor in L. 
// The state of L is unchanged.
List copyList(List L) {
    Node temp = L->front;
    List cpy = newList();
    for (int i = 0; i < L->length; i++) {
        append(cpy, temp->data);
        temp = temp->next;
    }
    return cpy;
}

// Returns a new List which is the concatenation of A and B. 
// The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "error in concatlist\n");
        exit(EXIT_FAILURE);
    }
    List joined = copyList(A);
    for (Node C = B->front; C != NULL; C = C->next) {
        append(joined, C->data);
    }
    return joined;
}