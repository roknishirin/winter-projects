/********************************************************************************* 
* Shirin Rokni
* 2023 Winter CSE101 PA# 2
* GraphTest.c
* Self Made Test client for Graph ADT 
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(void) {

    // making Graph
    Graph G = newGraph(10);

    // testing addEdge and add Arc
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 5);
    addEdge(G, 3, 10);
    addEdge(G, 5, 10);
    addArc(G, 1, 2);
    addArc(G, 1, 3);
    addArc(G, 2, 5);
    addArc(G, 3, 10);
    addArc(G, 5, 10);

    // testing BFS
    BFS(G, 3);

    // testing printGraph
    printGraph(stdout, G);

    // making List for GetPath
    List L = newList();
    getPath(L, G, 2); 

    // testing access functions
    fprintf(stdout, "order: %d\n", getOrder(G));
    fprintf(stdout, "size: %d\n", getSize(G));
    fprintf(stdout, "source: %d\n", getSource(G));
    fprintf(stdout, "parent: %d\n", getParent(G, 3));
    fprintf(stdout, "dist: %d\n", getDist(G, 2));

    // testing makeNull
    makeNull(G);
    printGraph(stdout, G);


    // freeing and cleaning up
    freeGraph(&G);
    freeList(&L);
    return 0;
}

/*

1: 2 3 
2: 1 5 
3: 1 10 
4: 
5: 2 10 
6: 
7: 
8: 
9: 
10: 3 5 
order: 10
size: 5
source: 3
parent: -1
dist: 2
1: 
2: 
3: 
4: 
5: 
6: 
7: 
8: 
9: 
10: 3 5 

*/
