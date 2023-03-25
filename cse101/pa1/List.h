/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 1
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
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);
List concatList(List A, List B);
