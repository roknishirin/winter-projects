/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 5
* List.cpp
* Contains the implementation of the List coding module. 
*********************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node Construct
// Pseudocode from Queue.cpp
List::Node::Node(ListElement x) {
	data = x ;
	next = nullptr; 
	prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List() {
	frontDummy = new Node(-1);
	backDummy = new Node(-1);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	backDummy->prev = frontDummy;
	frontDummy->next = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    backDummy->prev = frontDummy;
    frontDummy->next = backDummy;
    pos_cursor = 0;
    num_elements = 0;
	
	// load elements of L into this List
	// pseudocode from Queue.cpp
	Node *N = L.frontDummy->next;
	while ( N != L.backDummy) {
		this->insertBefore(N->data);
		N = N->next;
	}
}

// Destructor
List::~List() {
	clear();
	delete frontDummy;
	delete backDummy;
}

// Access functions -----------------------------------------------------------

// Returns the length of this List.
int List::length() const {
	return num_elements;
}

// Returns the front element in this List.
ListElement List::front() const {
	if (num_elements <= 0) {
		// pseudocode from Queue.cpp
		throw std::length_error("List: front(): empty list");
	}
	return frontDummy->next->data;
}


// Returns the back element in this List.
ListElement List::back() const {
    if (num_elements <= 0) {
        // pseudocode from Queue.cpp
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
	return pos_cursor; 	
}

// Returns the element after the cursor.
ListElement List::peekNext() const {
	if (position() >= length()) {
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return afterCursor->data;
}

// Returns the element before the cursor.
ListElement List::peekPrev() const {
	if (position() <= 0) {
		throw std::range_error("List: peekPrev(): cursor at front");
	}
	return beforeCursor->data;
}

// Manipulation procedures ----------------------------------------------------

// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	while (length() > 0) {
		moveFront();
		eraseAfter();
	}
}

// Moves cursor to position 0 in this List.
void List::moveFront() {
	beforeCursor = frontDummy;
	pos_cursor = 0;
	afterCursor = frontDummy->next;
}

// Moves cursor to position length() in this List.
void List::moveBack() {
	afterCursor = backDummy;
	pos_cursor = length();
	beforeCursor = backDummy->prev;
}

// Advances cursor to next higher position. Returns the List element that
// was passed over. 
ListElement List::moveNext() {
	if (position() >= length()) {
		throw std::range_error("List: moveNext(): cursor at back"); 
	}
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	pos_cursor++;
	return beforeCursor->data;
}

// Advances cursor to next lower position. Returns the List element that
// was passed over. 
ListElement List::movePrev() {
	if (position() <= 0) {
		throw std::range_error("List: movePrev(): cursor at front");
	}
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor->prev;
	pos_cursor -= 1;
	return afterCursor->data;	
}

// Inserts x after cursor.
void List::insertAfter(ListElement x) {
	Node *N = new Node(x);

	beforeCursor->next = N;	
	afterCursor->prev = N;

    N->prev = beforeCursor;
    N->next = afterCursor;

    afterCursor->prev = N;
    beforeCursor->next = N; 

	afterCursor = N;
	num_elements++;	
}

// Inserts x before cursor.
void List::insertBefore(ListElement x) {
	Node *N = new Node(x);

	beforeCursor->next = N;
    afterCursor->prev = N;
 
    N->prev = beforeCursor;
    N->next = afterCursor; 
	
	beforeCursor = N;
	pos_cursor++;
	num_elements++;
}


// Overwrites the List element after the cursor with x.
void List::setAfter(ListElement x) {
	if (position() >= length()) {
		throw std::range_error("List: setAfter(): cursor at back");
	}
	afterCursor->data = x;
} 

// Overwrites the List element before the cursor with x.
void List::setBefore(ListElement x) {
	if (position() <= 0) {
		throw std::range_error("List: setBefore(): cursor at front");
	}
	beforeCursor->data = x;
}

// mem leak delete function pseudocode given by tutor
// Deletes element after cursor.
void List::eraseAfter() {
	if (position() >= length() ) {
		throw std::range_error("List: eraseAfter(): cursor at back");
	}

	Node* temp = afterCursor;

	afterCursor->prev->next = afterCursor->next;
	afterCursor->next->prev = beforeCursor;
	afterCursor = afterCursor->next;

	delete temp;

	num_elements -= 1;
}

// mem leak delete function pseudocode given by tutor
// Deletes element before cursor.
void List::eraseBefore() {
	if (position() <= 0) {
		throw std::range_error("List: eraseBefore(): cursor at front");
	}

	Node *temp = beforeCursor;
	
	afterCursor->prev = beforeCursor->prev;
	beforeCursor->prev->next = afterCursor;
	beforeCursor = afterCursor->prev;

	delete temp;

	num_elements -= 1;
	pos_cursor -= 1;
}

// Other Functions ------------------------------------------------------------


// performs a linear seach for the first occurence of x (front-to-back)
int List::findNext(ListElement x) {

	while (afterCursor != backDummy) { // while the cursor is not at the end
		moveNext(); // places the cursor immediately after the found element
		if (peekPrev() == x) { // if the previous position was in the correct location
			return pos_cursor;
		}
	}

	pos_cursor = length();	
	return -1; // x is not found
}

// performs a linear seach for the first occurence of x (back-to-front)
int List::findPrev(ListElement x) {
	
	while (beforeCursor != frontDummy) { // while the cursor has not reached the front
		movePrev(); // places the cursor immediately before the found element
		if (peekNext() == x) { // if the next position was in the correct location
			return pos_cursor;
		}
	}

	pos_cursor = 0;	
	return -1; // x is not found
}

// Removes any repeated elements in this List, leaving only unique elements
void List::cleanup() {
    int counter = 0, counter_2 = 0;
    Node *N, *M, *O;
    N = frontDummy->next;
    M = nullptr;
    O = nullptr;

    // pseudocode from tutor saeed
    for (;N != backDummy; N = N->next) { // starting point
        counter += 1;
        M = N;
        counter_2 = counter;

        for (O = N->next; O != backDummy; O = M->next) { // going through each points' "mirror"

            if (N->data != O->data) { // if they aren't the same, move on

                M = O;

            } else { // if they are the same

                if (O == beforeCursor) { // edge case 
                    beforeCursor = O->prev;
                }

                if (O == afterCursor) { // edge case
                    afterCursor = O->next;
                }

                O->next->prev = M; // reconnection
                M->next = O->next;

                delete O; // delete element

                num_elements -= 1; // one less element

                if (counter_2 <= pos_cursor) { // decrement cursor (found repeeated element) 
                      pos_cursor -= 1;
                }

              }
            
			counter_2 += 1;
        }
    }
}




// Returns a new List consisting of the elements of this List, followed by
// the elements of L.
// Pseudocode from the Queue.cpp join function
List List::concat(const List& L) const {
	List J;
	Node *N = this->frontDummy->next;
	Node *M = L.frontDummy->next;

	while (N != this->backDummy) {
		J.insertBefore(N->data);
		N = N->next;
	}
	
	while (M != L.backDummy) {
		J.insertBefore(M->data);
		M = M->next;
	}

	J.moveFront();
	return J;
}

// Returns a string representation of this List
// pseudocode from Queue.cpp to_string 
std::string List::to_string() const {
	Node *N = nullptr; 
	std::string s = "";
	
	s = "(";

	for (N = frontDummy->next; N != backDummy->prev; N = N->next) {
		s += std::to_string(N->data)+", ";
	}

	s += std::to_string(N->data);
	s += ")";

	return s;
}

// Returns true if and only if this List is the same integer sequence as R.
// pseudocode from Queue.cpp equals function
bool List::equals(const List& R) const {
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = ( this->num_elements == R.num_elements );
	N = this->frontDummy->next;
	M = R.frontDummy->next;
	
	while ( eq && N != nullptr) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Overloaded Operators --------------------------------------------------------
// all pseudocode from Queue.cpp

// operator<<()
// Inserts string representation of L into stream
std::ostream& operator<< (std::ostream& stream, const List& L) {
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. 
bool operator == (const List& A, const List& B) {
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List &List::operator=(const List &L) {
	if (this != &L) {
		List temp = L; // make a copy of List

		// then swap the copy's fields with fields of this
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}

	// return this with the new data installed
	return *this;
}





