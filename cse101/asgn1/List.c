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

// did you make a node object? 
typdef struct NodeObj {
    int info;
    Node next;
    Node prev; 
    
} NodeObj;

// Constructors-Destructors -----------------------------------------
