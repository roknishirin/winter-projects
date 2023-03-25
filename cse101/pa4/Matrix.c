/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 4
* Matrix.c
* Contains the implementation of the Matrix coding module. 
*********************************************************************************/ 

#include "Matrix.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

// MatrixObj
typedef struct MatrixObj {
    List* row;
	int NNZ;
	int size;
} MatrixObj;

// EntryObj
typedef struct EntryObj {
	int column;
	double value;
} EntryObj;


// Constructors-Destructors ---------------------------------------------------

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = malloc(sizeof(MatrixObj));
	M->row = malloc((n + 1) * sizeof(List));
	M->size = n;
	M->NNZ = 0;
	for (int i = 1; i <= n; i ++) { // initializing a 2d array
		M->row[i] = newList();
	}
	return M;
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM) {
	Matrix M = *pM;
	if (pM != NULL && *pM != NULL) {
		makeZero (*pM);
		for (int i = 1; i <= M->size; i++)  {
			freeList(&M->row[i]);
			M->row[i] = NULL;
		}
		free(M->row);
	}
	free(*pM);
	M = NULL;
	free(M);
	*pM = NULL;
}

Entry newEntry(int col, double val) { 
	Entry E = malloc(sizeof(EntryObj));
	E->column = col;
	E->value = val;
	return E;
}

void freeEntry(Entry *pE) {
	if (*pE != NULL && pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

// Access functions -----------------------------------------------------------

// Return the size of square Matrix M.
int size(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: caling size() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: calling NNZ() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	return M->NNZ;
}


// pseudocode given by TA
// Return true (1) if matrices A and B are equal, false (0) otherwise
int equals(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: calling equals() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}

	// if you see this, please make a copy and maybe that will solve the problem 
	
	if (size(A) != size(B)) { // return false if sizes don't match
		return 0; 
	}

	if (NNZ(A) != NNZ(B)) { // return false if # of non zero elements don't match
		return 0;
	}

	Matrix Matrix_A = copy(A);
	Matrix Matrix_B = copy(B);

	for (int i = 1; i <= size(A); i++) {
		List a = Matrix_A->row[i];
		List b = Matrix_B->row[i];
		
		if (length(a) != length(b)) { // if length of the lists are not the same
			freeMatrix(&Matrix_A);
			freeMatrix(&Matrix_B);
			return 0;
		}

		moveFront(a);
		moveFront(b);

		while (index(a) >= 0) {

			Entry c = (Entry)get(a);
			Entry d = (Entry)get(b);
		
			if (c->column != d->column) { // columns not the same
				freeMatrix(&Matrix_A);
				freeMatrix(&Matrix_B);
				return 0;
			}

			if (c->value != d->value) { // values not the same
				freeMatrix(&Matrix_A);
				freeMatrix(&Matrix_B);
				return 0;
			}

			moveNext(a);
			moveNext(b);
		}
	}
	freeMatrix(&Matrix_A);
	freeMatrix(&Matrix_B);
	return 1; // is not unequal
}

// Manipulation procedures ----------------------------------------------------

//  Re-sets M to the zero Matrix stat
void makeZero(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: calling makeZero() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= M->size; i++) {
		
		for (moveFront(M->row[i]); index(M->row[i]) != -1; moveNext(M->row[i])) {
			Entry E = get(M->row[i]);
			freeEntry(&E);
		}
		clear(M->row[i]);
	}
	M->NNZ = 0;
}

// Changes the ith row, jth column of M to the value x
void changeEntry(Matrix M, int i, int j, double x) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: calling changeEntry() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	if (i < 1 || i > size(M)) {
		fprintf(stderr, "Matrix Error: calling changeEntry() on an invalid i value");
		exit(EXIT_FAILURE);
	}
	if (j < 1 || j > size(M)) {
		fprintf(stderr, "Matrix Error: calling changeEntry() on an invalid j value");
		exit(EXIT_FAILURE);
	}

	List L = M->row[i]; 

	if (x == 0) { // if there is no data point, remove it

		moveFront(L);

		if (length(L) == 0) { // nothing in the list && nothing in the data point
			return;
		}

		for (moveFront(L); index(L) != -1; moveNext(L)) {

			Entry E = (Entry)get(L);

			if (j == E->column) { //you are at the desired column
			    freeEntry(&E);
				M->NNZ -= 1;

				if (length(L) == 1) { // if there is only one element left, delete the list
					delete(L);
					return;
				}

				delete(L);
				return;
			} 
		}

	} else { // if x != 0

		moveFront(L);

		if (length(L) == 0) { // nothing in the list yet
			Entry E = newEntry(j, x);
			append(L, E);
			M->NNZ += 1;

		} else { // something already in the list

			moveFront(L);

			while (index(L) != -1) { // moving until the location of x	

				Entry E = (Entry)get(L);

				if (E->column == j) {
					E->value = x; // making the new value the x
					return;

				} else if (E->column > j) { // if it's right before
					Entry F = newEntry(j, x);
					insertBefore(L, F);
					M->NNZ += 1;
					return;
				} 

				moveNext(L);
			}

			if (index(L) == -1) { // if you've run off the column
                Entry F = newEntry(j, x);
                append(L, F);
                M->NNZ += 1;

			}
    	}
	}
}


// Matrix operations ----------------------------------------------------------

//  Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: calling copy() on an NULL A");
		exit(EXIT_FAILURE);
	}
	Matrix N = newMatrix(A->size); // make the new matrix
	for (int i = 1; i <= size(A); i++) { // iterate the columns
		List L = A->row[i]; // create list 
		moveFront(L); 
		for (int j = 1; index(L) != -1; j++) { // iterate through the row 
			Entry E = (Entry)get(L); // get the entry
			append(N->row[i], newEntry(E->column, E->value)); // append
			moveNext(L);
		}
	}
	// redoing the sizes to be accurate
	N->NNZ = A->NNZ;
	N->size = A->size;
	return N;
}


// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	if (A == NULL) {
		fprintf(stderr, "Matrix Error: calling scalarMult() on a NULL A");
		exit(EXIT_FAILURE);
	}
    Matrix N = newMatrix(A->size); // making the new matrix

	if (x != 0) { // ensure that not mult by 0 (just 0)

		for (int i = 1; i <= size(A); i++) { // iterate the columns
			List L = A->row[i]; // create the list
			moveFront(L);
			for (int j = 1; index(L) != -1; j++) { // iterate through the rows
				Entry E = (Entry)get(L); // get the entry
				append(N->row[i], newEntry(E->column, (E->value * x))); // multuiplying value by x
				moveNext(L);
			}
		}

		N->NNZ = A->NNZ;
		N->size = A->size;

	} else {
		makeZero(N);
	}

    return N;
}

// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling transpose() on a NULL A");
        exit(EXIT_FAILURE);
    }
	Matrix N = newMatrix(A->size); // make the new matrix
	for (int i = 1; i <= size(A); i++) { // iterate the columns
		List L = A->row[i]; // create the list
		moveFront(L);
		for (int j = 1; index(L) != -1; j++) { // iterate through the rwos
			Entry E = (Entry)get(L); // get the entry
			append(N->row[E->column], newEntry(i, E->value)); // changing how it is appended
			moveNext(L);
		}
	}
	N->NNZ = A->NNZ;
	N->size = A->size;
	return N;
}

// pseudocode from tutor 
// Returns a reference to a new Matrix object representing A+B
Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling sum() on a NULL A");
        exit(EXIT_FAILURE);
    }
	if (size(A) != size(B)) {
		fprintf(stderr, "Matrix Error: calling sum() on inequal Matrix values");
		exit(EXIT_FAILURE);
	}

	if (A == B) { // if its the same, just mult
		return scalarMult(2, A);
	}

	Matrix M = newMatrix(A->size); // new matrix that will be returned 
	
	for (int i = 1; i <= size(M); i++) { // iterate through the size of the Matrix 

		moveFront(A->row[i]); // move to the front of A
		moveFront(B->row[i]); // move to the front of B

		List List_A = A->row[i];
		List List_B = B->row[i];

		while (index(List_A) >= 0 || index(List_B) >= 0) { // while you are not at the invalid index

			if (index(List_A) >= 0 && index(List_B) >= 0) { // in the case that both of them have valid indices
			
				Entry Entry_A = (Entry)get(List_A); // needs to be in this scope otherwise NULL
				Entry Entry_B = (Entry)get(List_B);

				if (Entry_A->column > Entry_B->column) { // if A > B
					append(M->row[i], newEntry(Entry_B->column, Entry_B->value));
					moveNext(List_B);
					M->NNZ += 1;

				} else if (Entry_B->column > Entry_A->column) { // if B > A
					append(M->row[i], newEntry(Entry_A->column, Entry_A->value));
					moveNext(List_A);
					M->NNZ += 1;

				} else { // if A == B
					if (Entry_A->value + Entry_B->value != 0) { // ensuring you are not adding zero vals
						append(M->row[i], newEntry(Entry_A->column, Entry_A->value + Entry_B->value));
						M->NNZ += 1;
					}
					moveNext(List_A);
					moveNext(List_B);
				}

			} else if (index(List_B) != -1) { // if A has reached the end, but B has not
				Entry Entry_B = (Entry)get(List_B);
				append(M->row[i], newEntry(Entry_B->column, Entry_B->value));
				moveNext(List_B);
				M->NNZ += 1;

			} else if (index(List_A) != -1) { // if B has reached the end but A has not
				Entry Entry_A = (Entry)get(List_A);
				append(M->row[i], newEntry(Entry_A->column, Entry_A->value));
				moveNext(List_A);
				M->NNZ += 1;

			}
		}
	}
	return M; // returning the summed Matrix
}


Matrix diff (Matrix A, Matrix B) {

    if (A == B) { // if its the same, just mult
        return scalarMult(0, A);
    }

    Matrix M = newMatrix(A->size); // new matrix that will be returned 

    for (int i = 1; i <= size(M); i++) { // iterate through the size of the Matrix 

        moveFront(A->row[i]); // move to the front of A
        moveFront(B->row[i]); // move to the front of B

        List List_A = A->row[i];
        List List_B = B->row[i];

        while (index(List_A) >= 0 || index(List_B) >= 0) { // while you are not at the invalid index

            if (index(List_A) >= 0 && index(List_B) >= 0) { // in the case that both of them have valid indices
            
                Entry Entry_A = (Entry)get(List_A); // needs to be in this scope otherwise NULL
                Entry Entry_B = (Entry)get(List_B);

                if (Entry_A->column > Entry_B->column) { // if A > B
                    append(M->row[i], newEntry(Entry_B->column, -1 * Entry_B->value)); // making val -1
                    moveNext(List_B);
                    M->NNZ += 1;

                } else if (Entry_B->column > Entry_A->column) { // if B > A
                    append(M->row[i], newEntry(Entry_A->column, Entry_A->value));
                    moveNext(List_A);
                    M->NNZ += 1;

                } else { // if A == B
                    if (Entry_A->value - Entry_B->value != 0) { // ensuring that you are not adding zero vals
                        append(M->row[i], newEntry(Entry_A->column, Entry_A->value - Entry_B->value));
                        M->NNZ += 1;
                    }
                    moveNext(List_A);
                    moveNext(List_B);
                }

            } else if (index(List_B) != -1) { // if A has reached the end, but B has not
                Entry Entry_B = (Entry)get(List_B);
                append(M->row[i], newEntry(Entry_B->column, -1 * Entry_B->value)); // making value negative
                moveNext(List_B);
                M->NNZ += 1;

            } else if (index(List_A) != -1) { // if B has reached the end but A has not
                Entry Entry_A = (Entry)get(List_A);
                append(M->row[i], newEntry(Entry_A->column, Entry_A->value));
                moveNext(List_A);
                M->NNZ += 1;

            }
        }
    }
    return M; // returning the differenced Matrix

}

// computes the vector dot product of two matrix rows represented by Lists P and Q
double vectorDot(List P, List Q) { 

	if (P == NULL || Q == NULL) {
		fprintf(stdout, "calling vectorDot() on NULL List P or Q\n");
		exit(EXIT_FAILURE);
	}

	double output = 0; 
	
	Entry Entry_P;
	Entry Entry_Q;

	moveFront(P);
	moveFront(Q);

	while (index(P) != -1 && index(Q) != -1) { //as long as the indices are valid

		Entry_P = (Entry)get(P);
		Entry_Q = (Entry)get(Q);

		if (Entry_P->column > Entry_Q->column) { // column p > column q
			moveNext(Q);

		} else if (Entry_Q->column > Entry_P->column) { // columns q > column p
			moveNext(P);

		} else { // they are equal
			output += (Entry_P->value * Entry_Q->value);
			moveNext(P);
			moveNext(Q);
		}
	}

	return output;
}

// Returns a reference to a new Matrix object representing AB
Matrix product(Matrix A, Matrix B) { 

    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix Error: calling product() on a NULL A");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: calling product() on inequal Matrix values");
        exit(EXIT_FAILURE);
    }

	Matrix M = newMatrix(A->size);
	Matrix T = transpose(B);
	double dot = 0;

	for (int i = 1; i <= size(A); i++) { // going through rows

		List a = A->row[i];
		if (length(a) > 0) { // want to make sure row is a nonzero row
			for (int j = 1; j <= size(T); j++) {  // going through transpose 

				List b = T->row[j]; // making sure that the transposed row is not 0 because you dont want to add 0
				if (length(b) > 0) {

					dot = vectorDot(A->row[i], T->row[j]);
					if (dot != 0) {
						append(M->row[i], newEntry(j, dot));
						M->NNZ += 1;
					}
				}
			}
		}
	}
	freeMatrix(&T);
	return M;
}

// Other operations -----------------------------------------------------------
void printMatrix(FILE *out, Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "NULL ERROR: calling printMatrix() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= size(M); i ++) {
		List L = M->row[i];
		if (length(L) > 0) { // do not print the zero rows
			fprintf(out, "%d: ", i);
			for (moveFront(L); index(L) != -1; moveNext(L)) {
				Entry E = (Entry)get(L);
				fprintf(out, "(%d, %0.1f) ", E->column, E->value);
			}
			fprintf(out, "\n");
		}
	}
}
