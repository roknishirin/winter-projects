#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// used FileIO.c

#define MAX_LEN 300

int main(int argc, char *argv[]) {
    FILE *in, *out;
    char line[MAX_LEN];

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

    int line_count = 0;
    while (fscanf(in, " %s", line) != EOF) {
        line_count++;
    }

    rewind(in); // to read the start of the input file

    // allocating array
    /*change?*/
    char* arry[line_count];
    int i;
    for (i=0; i < line_count; i++) {
        arry[i] = malloc(sizeof(char) * MAX_LEN);
        fgets(arry[i], MAX_LEN, in);
    }

    // creating the list
    /*change?*/
    List lst = newList();
    for (int i = 0; i < line_count; i++) {
        moveFront(lst);
        while (index(lst)>= 0 && strcmp(arry[i], arry[get(lst)])>0) {
            // if there are still differences
            moveNext(lst);
        }
        if (index(lst) == -1) {
            // if at the beginning
            append(lst, i);
        } else {
            insertBefore(lst, i);
        }
    }

    // printing
    moveFront(lst);
    for (int i = 0; i < line_count; i++) {
        fprintf(out, "%s", arry[get(lst)]);
        moveNext(lst);
    }

    // freeing 
    for (int i = 0; i < line_count; i++) {
        free(arry[i]);
    }

    // closing
    freeList(&lst);
    fclose(in);
    fclose(out);
    return 0;
}