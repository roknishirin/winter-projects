/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 1
* FindPath.c
* The implementation of the Graph ADT to find the shortest path between the vertices
*********************************************************************************/ 

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *in, *out;

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }


    // logic from class tutor
    int sz;
    fscanf(in, " %d", &sz); // size of graph (first line) 
    Graph G = newGraph(sz); // graph is now fixed size

    int v_one = NIL, v_two = NIL;
    fscanf(in, "%d %d", &v_one, &v_two);

    int check = 0;
    while (check == 0) { // until the end of the file 
        if (v_one == 0 && v_two == 0) {
	    check = 1;
	    break;
        } else {
            addEdge(G, v_one, v_two);
	    fscanf(in, "%d %d", &v_one, &v_two);
        }
    }

    printGraph(out, G);
    List L = newList();

    int source = NIL, dest = NIL;
    while (fscanf(in, "%d %d", &source, &dest) != EOF) {
        if (source == 0 && dest == 0) {
            break;
        }

	BFS(G, source);
	getPath(L, G, dest);

	if (getDist(G, dest) == INF) {
	    fprintf(out, "\nThe distance from %d to %d is infinity\n", source, dest);
	    fprintf(out, "No %d-%d path exists\n", source, dest);

 	} else {
	    fprintf(out, "\nThe distance from %d to %d is %d\n", source, dest, getDist(G, dest));
     	    fprintf(out, "A shortest %d-%d path is: ", source, dest);
	    printList(out, L);
	    fprintf(out, "\n");
	}
	clear(L);
	
    }


    // clear and free
    freeList(&L);
    freeGraph(&G);
    fclose(in);
    fclose(out);
    return 0;
}
