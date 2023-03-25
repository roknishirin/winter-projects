/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 3
* Graph.h
* Contains the Graph coding module interface. 
*********************************************************************************/

#pragma once
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

#define NIL 0
#define UNDEF -2

typedef struct GraphObj *Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph *pG);

// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation procedures ----------------------------------------------------
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

// Other operations -----------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);
