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
    while (fgets(line, MAX_LEN, in) != NULL) {
        line_count++;
    }

    // allocating array
    char **arry = malloc(line_count * sizeof(char *));

    fseek(in, 0, SEEK_SET); // to read the start of the input file

    /* need to change ? */
    for (int i = 0; i < line_count; i++) {
        arry[i] = malloc(268 * sizeof(char));
    }

    /* CHANGE PROBABLY*/
    int dex = 0;
    while (fgets(line, MAX_LEN, in) != NULL) {
        strcpy(arry[dex], line);
        dex++;
    }

    // creating the list
    List lst = newList();
    for (int i = 0; i < line_count; i++) {
        if (length(lst) == 0) {
            append(lst, i);
        }
        else {
            if (strcmp(arry[get(lst)], arry[i]) >= 0) {
                prepend(lst, i);
            }
            else {
                while (index(lst) >= 0) {
                    if (strcmp(arry[get(lst)], arry[i]) >= 0) {
                        insertBefore(lst, i);
                        break;
                    }
                    moveNext(lst);
                }
                if (index(lst) == -1) {
                    append(lst, i);
                }
            }
        }
        moveFront(lst);
    }

    // printing
    for (int i = 0; i < line_count; i++) {
        fprintf(out, "%s", arry[get(lst)]);
        moveNext(lst);
    }

    // freeing 
    for (int i = 0; i < line_count; i++) {
        free(arry[i]);
    }

    free(arry);
    freeList(&lst);
    fclose(in);
    fclose(out);
    return 0;
}