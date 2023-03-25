/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 5
* Shuffle.cpp
* Client file which performing one shuffle operation
*********************************************************************************/

#include "List.h"

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// performing one shuffle operation
void shuffle(List& D) {
	D.moveFront();
	List A, B, C;


	int length = 0;
	// checking if odd of even
	if (D.length() % 2 == 0) {
		length = D.length() / 2;
	} else { // it is odd 
		length = (D.length() - 1) / 2;
	}

	if (D.length() == 1) {
		C.insertBefore(D.peekNext());

	} else {

		D.moveFront();
		for (int i = 0; i < length; i++) {
			A.insertBefore(D.peekNext());
			D.moveNext();
		}

		for (int j = length; j < D.length(); j++) {
			B.insertBefore(D.peekNext());
			D.moveNext();
		}

		while (!(C.length() == D.length())) {
			A.moveFront();
			B.moveFront();
			if (!(B.length() == 0)) {
				C.insertBefore(B.peekNext());
				B.eraseAfter();
			}
            if (!(A.length() == 0)) {
                C.insertBefore(A.peekNext());
                A.eraseAfter();
            }
		}
	}
	D = C;
}




int main(int argc, char * argv[]) {

    if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        exit(EXIT_FAILURE);
    }

	List Reg, Shuf;

	int counter = atoi(argv[1]);

	// printing
	cout << "deck size	 shuffle count" << endl;
	cout << "------------------------------" << endl;

	for (int deck = 1; deck < counter + 1; deck++) {		
		Reg.moveBack();
		Reg.insertBefore(deck - 1);

		Shuf = Reg; // temporary list

		shuffle(Reg); // calling shuffle
		int num = 1;

		while (!(Shuf == Reg)) { // shuffling reg until you get to the beginning
			shuffle(Reg);
			num += 1;
		}

		cout << " " << deck;
		cout << "		" << num << endl;

	}

	return EXIT_SUCCESS;
}
