/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 5
* Sparse.c
* Contains the implementation for Sparse.c which will take two command line arguments
* and initialize and build the Array-of-Lists representation of Matrix A and B
*********************************************************************************/

#include "Matrix.h"
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

	int i, j, size;
	fscanf(in, "%d %d %d", &size, &i, &j); // scanning in graph

	Matrix X = newMatrix(size);
	Matrix Y = newMatrix(size);

	// first Matrix - X
	for (int a = 0; a < i; a++) {
		int row, column;
		double data;
		fscanf(in, "%d %d %lf", &row, &column, &data);
		changeEntry(X, row, column, data);
	}

	fscanf(in, "\n");

	// second Matrix - Y
	for (int b = 0; b < j; b++) {
		int row, column;
		double data;
		fscanf(in, "%d %d %lf", &row, &column, &data);
		changeEntry(Y, row, column, data);
	}

	// A has __ non-zero entries
	fprintf(out, "A has %d non-zero entries:\n", i);
	printMatrix(out, X);
	fprintf(out, "\n");

	// B has __ non-zero entries
	fprintf(out, "B has %d non-zero entries:\n", j);
	printMatrix(out, Y);
	fprintf(out, "\n");	

	// (1.5)*A
	Matrix Scalar = scalarMult(1.5, X);
	fprintf(out, "(1.5)*A =\n");
	printMatrix(out, Scalar);
	fprintf(out, "\n");

	// A + B =
	Matrix Sum = sum(X, Y);
	fprintf(out, "A+B =\n");
	printMatrix(out, Sum);
	fprintf(out, "\n");

	// A + A =
	Matrix Sum_2 = sum(X, X);
	fprintf(out, "A+A =\n");
	printMatrix(out, Sum_2);
	fprintf(out, "\n");

	// B - A =
	Matrix Diff = diff(Y, X);
	fprintf(out, "B-A =\n");
	printMatrix(out, Diff);
	fprintf(out, "\n");

	// A - A = 
	Matrix Diff_2 = diff(X, X);
	fprintf(out, "A-A =\n");
	printMatrix(out, Diff_2);
	fprintf(out, "\n");

	// Transpose(A) = 
	Matrix Transpose = transpose(X);
	fprintf(out, "Transpose(A) =\n");
	printMatrix(out, Transpose);
	fprintf(out, "\n");

	// A * B =
	Matrix Product = product(X, Y);
	fprintf(out, "A*B =\n");
	printMatrix(out, Product);
	fprintf(out, "\n");

	// B * B =	
	Matrix Product_2 = product(Y, Y);
	fprintf(out, "B*B =\n");
	printMatrix(out, Product_2);
	fprintf(out, "\n");

	freeMatrix(&X);
	freeMatrix(&Y);
	freeMatrix(&Scalar);
	freeMatrix(&Sum);
	freeMatrix(&Sum_2);
	freeMatrix(&Diff);
	freeMatrix(&Diff_2);
	freeMatrix(&Transpose);
	freeMatrix(&Product);
	freeMatrix(&Product_2);
	fclose(in);
	fclose(out);
	return 0;
}
