/********************************************************************************* 
* Shirin Rokni
* 2023 Winter CSE101 PA# 3
* GraphTest.c
* Self Made Test client for Graph ADT 
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(void) {

    // making Graph
    Graph G = newGraph(10);
	List L = newList();

	// adding to L and making sure its the graph's order length
	for (int i = 1; i <= getOrder(G); i += 1){
		append(L, i);
	}

	
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

    // testing DFS
    DFS(G, L);

    // testing printGraph
    printGraph(stdout, G);
	printList(stdout, L);
    fprintf(stdout, "\n\n");

    // testing access functions
    fprintf(stdout, "\norder: %d\n", getOrder(G));
    fprintf(stdout, "size: %d\n", getSize(G));
    fprintf(stdout, "parent: %d\n", getParent(G, 3));
    fprintf(stdout, "discover: %d\n", getDiscover(G, 2));
    fprintf(stdout, "finish: %d\n\n", getFinish(G, 2));


	// testing transpose
    Graph T = transpose(G);
	printGraph(stdout, T);
	fprintf(stdout, "\n\n");	

	// testing copyGraph
	Graph C = copyGraph(G);
	printGraph(stdout, C);

    // freeing and cleaning up
    freeGraph(&G);
	freeGraph(&C);
	freeGraph(&T);
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
9 8 7 6 4 1 2 5 10 3 


order: 10
size: 5
parent: 10
discover: 2
finish: 9

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

*/
