/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 2
* Graph.c
* Contains the implementation of the Graph coding module. 
*********************************************************************************/ 

#include "Graph.h"
#include <stdint.h>
#include <stdio.h>
#include "List.h"

typedef struct GraphObj{
    List *lst;
    int *color;
    int *parent;
    int *dist;
    int order;
    int size;
    int source;
} GraphObj;


// Constructors-Destructors ---------------------------------------------------


// returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->lst = malloc(sizeof(List) * (n + 1));
    G->color = malloc(sizeof(int) * (n + 1));
    G->parent = malloc(sizeof(int) * (n + 1));
    G->dist = malloc(sizeof(int) * (n + 1));
    G->size = 0;
    G->order = n;
    G->source = NIL;

    for (int i = 1; i < (n + 1); i++ ) {
        G->lst[i] = newList();
        G->color[i] = NIL;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    return G;
}


// frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL. 
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i < getOrder(*pG) + 1; i ++) {
            freeList(&(*pG)->lst[i]);
        }
        free((*pG)->lst);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->dist);
        free(*pG);
        *pG = NULL;
    }
}

// Access functions -----------------------------------------------------------

// return the corresponding field values,
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


//returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called. 
int getSource(Graph G) {
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getSource() on a NULL Graph");
        exit(EXIT_FAILURE);
    }
    return G->source;
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

// returns the distance from
// the most recent BFS source to vertex u
int getDist(Graph G, int u) {
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling getDist() on a NULL Graph");
	exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        fprintf(stderr, "Graph Error: u value in getDist() is invalid");
        exit(EXIT_FAILURE);
    }
    
    return G->dist[u];
}

void getPath(List L, Graph G, int u) {
    if (G == NULL || L == NULL) {
        fprintf(stderr, "Graph Error: calling getPath() on a NULL Graph or List");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: u value in getPath() is invalid");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        fprintf(stderr, "Graph Error: calling getPath() on a NIL source");
        exit(EXIT_FAILURE);
    }
    if (u == getSource(G)) { // you are at the shortest path
        append(L, getSource(G));
    } else if (getParent(G, u) == NIL) {
        //printf("%d is not reachable from %d\n", u, getSource(G));
        clear(L);
        append(L, NIL);
    } else { // keep on going
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

// Manipulation procedures ----------------------------------------------------

// deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling makeNULL() on a NULL graph");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G); i++) {
        clear(G->lst[i]);
        G->parent[i] = NIL;
        G->dist[i] = INF;
        G->color[i] = NIL;
    }
    G->size = 0;
    G->source = NIL;

}


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


// logic from class tutor
/*void addArc(Graph G, int u, int v) { 
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
        insertBefore(G->lst[u], v);

    } else { // empty
        append(G->lst[u], v);
    }    
    G->size++;
}*/


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


// logic from given pseudocode
void BFS(Graph G, int s) { 
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling BFS() on NULL graph");
        exit(EXIT_FAILURE);
    }
    if (s <= 0 || s > getOrder(G)) {
        fprintf(stderr, "Graph Error: BFS() on an invalid s source");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < getOrder(G) + 1; i ++) {
        G->color[i] = 0;
        G->dist[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = 1;
    G->dist[s] = 0;
    G->parent[s] = NIL;
    G->source = s;

    List Q = newList();
    append(Q, s);

    while (length(Q) != 0) {
        moveFront(Q);
	int x = get(Q);
        deleteFront(Q);
        moveFront(G->lst[x]);

        while (index(G->lst[x]) != -1) {
            int y = get(G->lst[x]);
            if (G->color[y] == 0) {
                G->color[y] = 1;
	        G->dist[y] = G->dist[x] + 1;
	        G->parent[y] = x;
 	        append(Q, y);
            }
	    moveNext(G->lst[x]);
        }
        G->color[x] = 2;
    }
    freeList(&Q);
    Q = NULL;
}

// Other operations -----------------------------------------------------------
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i < getOrder(G) + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->lst[i]);
        fprintf(out, "\n");
    }
}
