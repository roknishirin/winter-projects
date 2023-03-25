/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 4
* FindComponents.c
* Contains the implementation to print the adjacency list representation and the 
* connected outputs
*********************************************************************************/

#include "Graph.h"
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

    // logic from class tutor aarka
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
            addArc(G, v_one, v_two);
	    fscanf(in, "%d %d", &v_one, &v_two);
        }
    }

    // printing out the Adjacency list 
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // the transpose process
    // Run DFS on 𝐺 and 𝐺^𝑇 , processing the vertices 

    List L = newList();
    for (int i = 1; i <= sz; i++) { // decreasing finish times
        append(L, i);
    }
    DFS (G, L); // Run DFS on G
    Graph T = transpose(G); // G^T
    DFS(T, L); // Run DFS on G^T

    // Determine the strong components of 𝐺.
    int strong = 0; 
    for (moveFront(L); index(L) != -1; moveNext(L)) {
        int num = get(L);
        if (getParent(T, num) == NIL) { // parent is NIL 
            strong++;
        }
    }

    // Print the strong components of 𝐺 to the output file in topologically sorted order.
    fprintf(out, "G contains %d strongly connected components:\n", strong);
    moveBack(L); // start from the back and move front
    List output = newList();
	
	// Simon the tutor helped   
    for (int i = 1; i <= strong; i++) { // only need to iterate how scc amount of times
        while (index(L) >= 0) {
            int num = get(L);
            if (getParent(T, num) == NIL) { // you are at the end
	        prepend(output, num);
	        movePrev(L);
	        break;
	    } else { 
	        prepend(output, num);
	        movePrev(L);
	    }
        }
        fprintf(out, "Component %d: ", i);
        printList(out, output);
        clear(output);
        fprintf(out, "\n");
    }


    fclose(in);
    fclose(out);
    freeGraph(&G);
    freeGraph(&T);
    freeList(&L);
    freeList(&output);
    return 0;
}

