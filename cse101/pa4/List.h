/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 4
* List.h
* Contains the List coding module interface. 
*********************************************************************************/

#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Constructors-Destructors ---------------------------------------------------
typedef struct ListObj *List;
typedef struct NodeObj *Node;
List newList(void);
void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void set(List L, void* x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* x);
void append(List L, void* x);
void insertBefore(List L, void* x);
void insertAfter(List L, void* x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);
List concatList(List A, List B);

