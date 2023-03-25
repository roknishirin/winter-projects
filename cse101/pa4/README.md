# Programming Assignment 4: Matrix Operations

The purpose of this assignment is to implement a Matrix ADT which acts as a calculator for performing matrix operations that exploits the (expected) sparseness of its matrix operands.

# File Descriptions

List.h : This file contains the List coding module interface.  

List.c : This file contains the implementation of the List coding module.  

ListTest.c : This file contains a test for the List.c module.  

Matrix.h : This file contains the Matrix coding module interface.  

Matrix.c : This file contains the implementation of the Matrix coding module.  

MatrixTest.c : This file contains a test for the Matrix.c module.  

Sparse.c : This file contains the implementation of the Matrix coding module which will initialize and build the Array-of-Lists representation of the matrices A and B, then calculate and print various matrices to an output file.  

Makefile : This file is responsible for doing the compilation process for the executable files.   

README.md : This file contains instructions on how to build and run the executables.  

# Building

Run ```make``` to build the Sparse program.  
Run ```make MatrixTest``` to build the MatrixTest program.  
Run ```make ListTest``` to build the ListTest program.  
Run ```make clean``` to remove all binaries.  
Run ```make SparseCheck``` to run the Sparse program in valgrind on in5.  
Run ```make MatrixCheck``` to run the MatrixTest program in valgrind.  


