/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 4
* Matrix.h
* Contains the Matrix coding module interface. 
*********************************************************************************/

#pragma once

#include "List.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct MatrixObj *Matrix;
typedef struct EntryObj *Entry;

// Constructors-Destructors ---------------------------------------------------
Matrix newMatrix(int n);
void freeMatrix(Matrix *pM);

// Access functions -----------------------------------------------------------
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);

// Manipulation procedures ----------------------------------------------------
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

// Matrix operations ----------------------------------------------------------
Matrix copy(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix transpose(Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);

// Other operations -----------------------------------------------------------
void printMatrix(FILE *out, Matrix M);

