/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 3
* Graph.c
* Contains the implementation of the Graph coding module. 
*********************************************************************************/ 

#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct GraphObj {
    List *lst;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    int size;
    int order;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->lst = malloc(sizeof(List) * (n + 1));
    G->color = malloc(sizeof(int) * (n + 1));
    G->parent = malloc(sizeof(int) * (n + 1));
    G->discover = malloc(sizeof(int) * (n + 1));
    G->finish = malloc(sizeof(int) * (n + 1));
    G->size = 0;
    G->order = n;
    
    for (int i = 1; i < (n + 1); i++) {
        G->lst[i] = newList();
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    return G;
}

void freeGraph(Graph *pG) { 
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i < getOrder(*pG) + 1; i ++) {
            freeList(&(*pG)->lst[i]);
        }
        free((*pG)->lst);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}


// Access functions -----------------------------------------------------------

// return the corresponding field values
int getOrder(Graph G) {
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getOrder() on a NULL Graph");
            exit(EXIT_FAILURE);
    }
    return G->order;
}

// return the corresponding field values,
int getSize(Graph G) {
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getSize() on a NULL Graph");
	exit(EXIT_FAILURE);
    }
    return G->size;
}

// will return the parent of vertex u in the BFS tree
int getParent(Graph G, int u) {
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getParent() on a NULL Graph");
	exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: u value in getParent() is invalid");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// returns the discovery time
int getDiscover(Graph G, int u) {
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getDiscover() on a NULL Graph");
	exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: u value in getDiscover() is invalid");
        exit(EXIT_FAILURE);
    }

    return G->discover[u];
}

// returns the finish time
int getFinish(Graph G, int u) {
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getFinish() on a NULL Graph");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: u value in getFinish() is invalid");
        exit(EXIT_FAILURE);
    }
    
    return G->finish[u];
}

// Manipulation procedures ----------------------------------------------------

// adds int u to the lst of v, and vice versa
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on a NULL graph");
        exit(EXIT_FAILURE);
    }
    
    // precons
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() on invalid u or v value");
	exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
}

// adds directed edge from u to v
// logic from class tutor
void addArc(Graph G, int u, int v) { 
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on a NULL graph");
        exit(EXIT_FAILURE);
    }   
    
    // precons
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() on invalid u or v value");
        exit(EXIT_FAILURE);
    }

    if (G->lst[u] == 0) {
        append(G->lst[u], v);
    }

    moveFront(G->lst[u]);

    while (index(G->lst[u]) >= 0 && G->lst[u] != NULL && get(G->lst[u]) < v) { // keep on iterating until u is bigger/same
        moveNext(G->lst[u]);
    }

    if (index(G->lst[u]) != -1) { // if its not empty
        if (v == get(G->lst[u])) { // if its not already inside
	 return;
        }
        insertBefore(G->lst[u], v);

    } else { // empty
        append(G->lst[u], v);
    }    
    G->size++;
}

// helper function for DFS 
// pseudocode given by professor
// we need time to be a pointer to store the changing var values
void Visit(Graph G, List L, int x, int *time) {
    if (G == NULL || L == NULL) {
        fprintf(stderr, "Graph or List Error: calling visit() on a null list or graph");
        exit(EXIT_FAILURE);
    }

    // discovery
    G->discover[x] = ++(*time);
    G->color[x] = 1;

    for ((moveFront(G->lst[x])); (index(G->lst[x]) >= 0); (moveNext(G->lst[x]))) {
        int y = get(G->lst[x]);
        if (G->color[y] == 0) { // if white
            G->parent[y] = x;
            Visit(G, L, y, time);
        }
    }
    G->color[x] = 2;

    // finish 
    G->finish[x] = ++(*time);
    prepend(L, x);
}

// the Depth First Search Algorithm
void DFS(Graph G, List S) {
    if (G == NULL || S  == NULL) {
        fprintf(stderr, "Graph or List Error: calling visit() on a null list or graph");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "List Error: calling DFS() on different sized orders");
	exit(EXIT_FAILURE);
    }

    for (int i = 1; i < getOrder(G) + 1; i++) {
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    int time = 0;

    // use a copied list (advice from tutor)
    List L = copyList(S);
    clear(S);

    // main loop of DFS
    moveFront(L);
    for (int i = 1; i < getOrder(G) + 1; i++) {
        if (G->color[get(L)] == 0) {
            Visit(G, S, get(L), &time);
        }
        moveNext(L);
    }

    freeList(&L); 
}

// Other operations -----------------------------------------------------------

// return a transposed graph
Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling transpose() on a NULL list");
        exit(EXIT_FAILURE);
    }
   
    Graph cpy = newGraph(getOrder(G));

    for (int i = 1; i < getOrder(G) + 1; i++) {
        moveFront(G->lst[i]);
        while(index(G->lst[i]) != -1) {
            addArc(cpy, get(G->lst[i]), i);
            moveNext(G->lst[i]);
        }
    }
    return cpy; 
}


Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling copyGraph() on a NULL list");
        exit(EXIT_FAILURE);
    }
   
    Graph cpy = newGraph(getOrder(G));

    for (int i = 1; i < getOrder(G) + 1; i++) {
        moveFront(G->lst[i]);
        while(index(G->lst[i]) != -1) {
            addArc(cpy, i, get(G->lst[i]));
            moveNext(G->lst[i]);
        }
    }
    return cpy; 
}


void printGraph(FILE* out, Graph G) {
    for (int i = 1; i < getOrder(G) + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->lst[i]);
        fprintf(out, "\n");
    }
}

