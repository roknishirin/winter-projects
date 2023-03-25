/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 4
* MatrixTest.h
* Cotains the Test for the Matrix coding module.
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include"Matrix.h"

int main() {

	// testing newMatrix
	Matrix M = newMatrix(10);
	
	// testing changeEntry
	changeEntry(M, 1, 1, 1);
	changeEntry(M, 1, 2, 1);
	changeEntry(M, 3, 1, 1);
	changeEntry(M, 2, 3, 3);
	changeEntry(M, 3, 3, 3);
	changeEntry(M, 1, 1, 3);

	// testing printMatrix
	printMatrix(stdout, M);
	printf("\n");

	// testing changeEntry but 0 version
	changeEntry(M, 1, 1, 0);
	changeEntry(M, 3, 3, 0);
	changeEntry(M, 2, 3, 0);

	printMatrix(stdout, M);
	printf("\n");

	// testing size and NNZ
	printf("size: %d\n", size(M));
	printf("NNZ: %d\n", NNZ(M));

	// testing copy and equals
	Matrix N = copy(M);
	printf("equals\n");
	if (equals(M, N) == 1) {
		printf("true\n");
	} else {
		printf("false\n");
	}	
	changeEntry(N, 1, 2, 3);
	changeEntry(N, 2, 1, 1);

	// testing scalarMult
	Matrix scale = scalarMult(2, N);
	printf("scalar multiplication: 2 * N\n");
	printMatrix(stdout, scale);
	freeMatrix(&scale);
	
	// testing transpose
	Matrix tran = transpose(M);
	printf("transpose: M\n");
	printMatrix(stdout, tran);
	freeMatrix(&tran);

	// testing sum
	Matrix soom = sum(M, N);
	printf("sum: M + N\n");
	printMatrix(stdout, soom);
	freeMatrix(&soom);

	// testing diff
	Matrix deef = diff(M, N);
	printf("diff: M - N\n");
	printMatrix(stdout, deef);
	freeMatrix(&deef);

	// testing product
	Matrix prod = product(M, N);
	printf("product: M * N\n");
	printMatrix(stdout, prod);
	freeMatrix(&prod);

	// testing makeZero
	makeZero(M);

	// testing freeMatrix
	freeMatrix(&N);
	freeMatrix(&M);
	return EXIT_SUCCESS;
}


/*
1: (1, 3.0) (2, 1.0) 
2: (3, 3.0) 
3: (1, 1.0) (3, 3.0) 

1: (2, 1.0) 
3: (1, 1.0) 

size: 10
NNZ: 2
equals
true
scalar multiplication: 2 * N
1: (2, 6.0) 
2: (1, 2.0) 
3: (1, 2.0) 
transpose: M
1: (3, 1.0) 
2: (1, 1.0) 
sum: M + N
1: (2, 4.0) 
2: (1, 1.0) 
3: (1, 2.0) 
diff: M - N
1: (2, -2.0) 
2: (1, -1.0) 
product: M * N
1: (1, 1.0) 
3: (2, 3.0)
*/ 
