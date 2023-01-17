
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

    for (int i = 0; i < (n + 1); i++ ) {
        G->lst[i] = newList();
        G->color[i] = NIL;
        G->parent[i] = NIL;
        G->dist[i] = NIL;
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
		fprintf(stderr, "Graph Error: u value in getParent() is invalid");
		exit(EXIT_FAILURE);
	}
    
    if (G->parent[u] == NIL) {
        return NIL;
    }
    return G->dist[u];
}

void getPath(List L, Graph G, int u) {

}