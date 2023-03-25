/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 4
* ListTest.h
* Contains the test file for the List coding module.
*********************************************************************************/

#include "List.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	
	// testing newList
	List L = newList();

	// testing append and prepend
	int x = 1;
	int y = 2;
	int z = 0;
	int zz = 3;
	append(L, &x);
	append(L, &y);
	prepend(L, &z);
	append(L, &zz);

	// testing printList
	printList(stdout, L);
	fprintf(stdout, "\n");

	// testing index and length
	printf("length: %d\n", length(L));
	printf("index: %d\n", index(L));

	// testing get and movefront and movenext
	for (moveFront(L); index(L) != 0; moveNext(L)) {
		printf("get: %d\n", *(int *)get(L));
	}

	// testing front and back
	printf("front: %d\n", *(int *)front(L));
	printf("Back: %d\n", *(int *)back(L));

	// testing moveback and movePrev
	moveBack(L);	
	movePrev(L);
	printf("new index: %d\n", index(L));

	// testing clear
	clear(L);

	append(L, &z);
	append(L, &x);
	append(L, &y);
	append(L, &zz);

	// testing insertbefore and insertafter
	moveFront(L);
	moveNext(L);
	insertBefore(L, &zz);
	insertAfter(L, &z);
	printf("new get: %d\n", *(int *)get(L));

	// testing deletefront and deletetback
	deleteFront(L);
	deleteBack(L);
	printf("new length: %d\n", length(L));

	// testing set
	set(L, &x);

	// testing copyList(L) and concatList();
	List N = copyList(L);
	List M = concatList(L, N);
	printf("new get: %d\n", *(int *)get(L));
	
	// testing delete
	delete(L);

	// testing freeList
	freeList(&L);
	freeList(&N);
	freeList(&M);

	return EXIT_SUCCESS;
}


/* 
0x7fff5a1ea7dc 0x7fff5a1ea7e4 0x7fff5a1ea7e0 0x7fff5a1ea7d8 
length: 4
index: -1
front: 0
Back: 3
new index: 2
new get: 1
new length: 4
new get: 1
*/
