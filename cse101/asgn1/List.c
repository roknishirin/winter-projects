#include "List.h"
#include <stdio.h>

// Creates and returns a new empty List.
typedef struct ListObj {
    int pos; // the position of the cursor 
    int length; // length
    Node front;
    Node back;
    Node cursor;

} ListObj;

