#include "List.h"

int main(void){
    // making the lists
    List A = newList();
    List B = newList();

    // append and prepend test
    append(A, 1);
    append(A, 3);
    prepend(A, 0);
    append(A, 4);
    append(A, 5);
    prepend(A, 0);

    // print output of append/prepend test
    // 0 0 1 3 4 5 
    printList(stdout, A);
    printf("\n");

    // moveFront and insertAfter test
    // 0 9 0 1 3 4 5 
    moveFront(A);
    insertAfter(A, 9);
    printList(stdout, A);
    printf("\n");

    // moveFront and insertBefore test
    // 7 0 9 0 1 3 4 5 
    moveFront(A);
    insertBefore(A, 7);
    printList(stdout, A);
    printf("\n");

    // moveFront and deleteFront test
    // 7 0 9 0 1 3 4 5 
    moveFront(A);
    insertBefore(A, 6);
    deleteFront(A);
    printList(stdout, A);
    printf("\n");

    // movefront, and deleteBack test
    // 7 8 0 9 0 1 3 
    deleteBack(A);
    moveFront(A);
    insertAfter(A, 8);
    deleteBack(A);
    printList(stdout, A);
    printf("\n");

    // command tests
    // Length = 7 Index = 3 front = 7 back = 3 get = 9
    printf("Length = %d\n", length(A));
    moveFront(A);
    moveNext(A);
    moveNext(A);
    moveNext(A);
    printf("Index = %d\n", index(A));
    printf("front = %d\n", front(A));
    printf("back = %d\n", back(A));
    printf("get = %d\n", get(A));

    // delete test 
    // 8 0 9 0 1 3 
    moveFront(A);
    delete(A);
    printList(stdout, A);
    printf("\n");

    // concatinating the tests
    // 9 0 1 2 
    // 8 0 9 0 1 3 9 0 1 2    
    append(B, 0);
    append(B, 1);
    append(B, 2);
    prepend(B, 9);
    delete(B);
    printList(stdout, B);
    printf("\n");
    List C = concatList(A, B);
    printList(stdout, C);
    printf("\n");

    // freeList test
    freeList(&A);
    freeList(&B);
    freeList(&C);
}

/*
0 0 1 3 4 5 
0 9 0 1 3 4 5 
7 0 9 0 1 3 4 5 
7 0 9 0 1 3 4 5 
7 8 0 9 0 1 3 
Length = 7
Index = 3
front = 7
back = 3
get = 9
8 0 9 0 1 3 
9 0 1 2 
8 0 9 0 1 3 9 0 1 2 
*/