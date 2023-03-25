/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 6
* ListTest.cpp
* Contains the test file for the List coding module.
*********************************************************************************/


#include<iostream>
#include<string>
#include<stdexcept>

#include"List.h"

using namespace std;

int main(){ 

	List A, B;

	// testing front
	A.moveFront();

	// testing insertAfter
	A.insertAfter(3);
	A.insertAfter(2);
	A.insertAfter(1);

	// testing moveBack and insertBefore
	A.moveBack();
	A.insertBefore(4);
	
	cout << A << endl;		

	// testing movePrev
	A.movePrev();
	A.insertAfter(4);

	// testing movenext
	A.moveNext();
	A.moveNext();
	A.insertAfter(5);

	// testing cleanup
	A.cleanup();
	cout << A << endl;

	// testing peeknext and peekprev
	A.movePrev();
	cout << "Peek Next: " << A.peekNext() << endl;
	cout << "Peek Prev: " << A.peekPrev() << endl;
	cout << "Front: " << A.front() << endl;
	cout << "Back: " << A.back() << endl;
	cout << "Position:  " << A.position() << endl;
	cout << "Length: " << A.length() << endl;

	cout << A << endl;

	// testing setAfter and setBefore
	A.moveBack();
	A.movePrev();
	A.setAfter(6);
	A.setBefore(5);

	cout << A << endl;

	// testing erasebefore and eraseafter
	A.eraseAfter();
	A.eraseBefore();

	cout << A << endl;

	// testing findnext and findprev
	B.insertBefore(4);
	B.insertBefore(5);
	B.insertBefore(6);
	cout << "Find next: " << B.findNext(4) << endl;
	cout << "Find prev: " << B.findPrev(5) << endl;

	cout << B << endl;
	
	// testing concat
	List C;
	C = A.concat(B);

	cout << C << endl;

	// testing equals
	if (A.equals(B)) {
		cout << "they are equal" << endl;
	} else { 
		cout << "they are not equal" << endl;
	}

	// testing to_string, << and == 
	if (A == B) {
		cout << "they are equal" << endl;
	} else {
		cout << "they are not equaal" << endl;
	}

	return EXIT_SUCCESS;
}



/*

(1, 2, 3, 4)
(1, 2, 3, 4, 5)
Peek Next: 4
Peek Prev: 3
Front: 1
Back: 5
Position:  3
Length: 5
(1, 2, 3, 4, 5)
(1, 2, 3, 5, 6)
(1, 2, 3)
Find next: -1
Find prev: 1
(4, 5, 6)
(1, 2, 3, 4, 5, 6)
they are not equal
they are not equaal

*/

