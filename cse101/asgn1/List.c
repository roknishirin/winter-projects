#include "List.h"
#include <stdio.h>

// Creates and returns a new empty List.
typedef struct ListObj {
    int pos; // the position of the cursor 
    int length; // length
    struct Node *cursor; // a pointer to the cursor
    struct Node *start; // a pointer to the first position
    struct Node *end; // a pointer to the last position 

} ListObj;

