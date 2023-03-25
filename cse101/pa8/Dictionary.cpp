/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 8
* Dictionary.cpp
* Contains the implementation of the Dictionary coding module. 
*********************************************************************************/

#include "Dictionary.h"

#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

#define red  1
#define black  0

// Exported types -------------------------------------------------------------

// private node struct
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = black;
}


// Class Constructors & Destructors -------------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
	nil = new Node("\0", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
	nil = new Node("\0", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
	clear();
	delete nil;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if (R != nil) {

		inOrderString(s, R->left);
		s += R->key; // appending "key : value \n" 
		s += " : ";
		s += std::to_string(R->val);
		s += "\n";
		inOrderString(s, R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {

	if (R != nil) {

		s += R->key; // appending string conssiting of keys only
		s += "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {

	if (R != N) { // recursion terminates ay N
		
		setValue(R->key, R->val); // setting the value
		preOrderCopy(R->left, N); // going down left side
		preOrderCopy(R->right, N); // going down right side
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {

	if (R != nil) {

		postOrderDelete(R->left); // deleting all left side
		postOrderDelete(R->right); // delteing all right side
		delete R; // setting R to nil
		num_pairs -= 1;
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {

	if (R == nil || k == R->key) {

		return R;

	} else if (k < R->key) {

		return search(R->left, k);

	} else if (k > R->key) {

		return search(R->right, k);
	}
	
	return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {

	if (R == nil) {
		return nil;
	}
	
	while (R->left != nil) {
	
		R = R->left;
	}
	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {

	if (R == nil) {
		return nil;
	}

	while (R->right != nil) {

		R = R->right;
	}
	return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {

	if (N->right != nil) {		// case 1
		return findMin(N->right);
	}

	Node *y = N->parent;
	while (y != nil && N == y->right) { // case 2
		
		N = y ;
		y = y->parent;
	}

	return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {

	if (N->left != nil) { // case 1
		
		return findMax(N->left);
	}

	Node *y = N->parent;
	while (y != nil && N == y->left) { // case 2
		
		N = y;
		y = y->parent;
	}

	return y;
}

// RBT Helper Functions (Optional) -----------------------------------------


// LeftRotate()
void Dictionary::LeftRotate(Node* N) {

	// set y
	Node *y = N->right;

	// turn y's left subtree into x's right subtree
	N->right = y->left;
	if (y->left != nil) {

		y->left->parent = N;
	}

	// link y's parent to x
	y->parent = N->parent;
	
	if (N->parent == nil) {

		root = y;
	} else if (N == N->parent->left) {

		N->parent->left = y;
	} else {
	
		N->parent->right = y;
	}

	// put x on y's left
	y->left = N;
	N->parent = y;
}


// RightRotate()
void Dictionary::RightRotate(Node* N) {

	// set y
	Node *y = N->left;

	// turn y's right subtree into x's left subtree
	N->left = y->right;

	if (y->right != nil) {

		y->right->parent = N;
	} 

	// link y's parent to x
	y->parent = N->parent;

	if (N->parent == nil) {

		root = y;
	} else if (N == N->parent->right) {

		N->parent->right = y;
	} else {
	
		N->parent->left = y;
	}

	// put x on y's right
	y->right = N;
	N->parent = y;
}

// red == 1
// black == 0
// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {

	while (N->parent->color == red) {

		if (N->parent == N->parent->parent->left) {
	
			Node *y = N->parent->parent->right;
			
			if (y->color == red) { // case red

				N->parent->color = black;
				y->color = black;
				N->parent->parent->color = red;
				N = N->parent->parent;
			}

			else { // case black & 3

				if (N == N->parent->right) {

					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = black;
				N->parent->parent->color = red;
				RightRotate(N->parent->parent);
			}
		} else {

			Node *y = N->parent->parent->left;

			if (y->color == red) { // case 4

				N->parent->color = black;
				y->color = black;
				N->parent->parent->color = red;
				N = N->parent->parent; 
			}

			else { // case 5 & 6

				if (N == N->parent->left) {

					N = N->parent;
					RightRotate(N);
				}

				N->parent->color = black;
				N->parent->parent->color = red;
				LeftRotate(N->parent->parent);
			}
		}
	}
	
	root->color = black;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {

	if (u->parent == nil) {

		root = v;
	} else if (u == u->parent->left) {

		u->parent->left = v;
	} else {

		u->parent->right = v;
	}
	
	v->parent = u->parent;
}

// red == 1
// black == 0
// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {

	while (N != root && N->color == black) {

		if (N == N->parent->left) {

			Node *w = N->parent->right;

			if (w->color == red) { // case red

				w->color = black;
				N->parent->color = red;
				LeftRotate(N->parent);
			}

			if (w->left->color == black && w->right->color == black) { // case 2

				w->color = red;
				N = N->parent;
			} else {

				if (w->right->color == black) { // case 3
					
					w->left->color = black;
					w->color = red;
					RightRotate(w);
					w = N->parent->right;
				}

				// case 4
				w->color = N->parent->color;
				N->parent->color = black;
				w->right->color = black;
				LeftRotate(N->parent);
				N = root;
			}

		} else {

			Node *w = N->parent->left;
			
			if (w->color == red) {  // case 5

				w->color = black;
				N->parent->color = red;
				RightRotate(N->parent);
				w = N->parent->left;
			}

			if (w->right->color == black && w->left->color == black) { // case 6

				w->color = red;
				N = N->parent;
			} else {

				if (w->left->color == black) { // case 7 

					w->right->color = black;
					w->color = red;
					LeftRotate(w);
					w = N->parent->left;
				}

				// case 8
				w->color = N->parent->color;
				N->parent->color = black;
				w->left->color = black;
				RightRotate(N->parent);
				N = root;
			}
		}
	}

	N->color = black;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {

	Node *y = N;
	Node *x;
	int y_original_color = y->color;

	if (N->left == nil) {

		x = N->right;
		RB_Transplant(N, N->right);

	} else if (N->right == nil) {

		x = N->left;
		RB_Transplant(N, N->left);

	} else {

		y = findMin(N->right);
		y_original_color = y->color;
		x = y->right;

		if (y->parent == N) {
			x->parent = y;

		} else {

			RB_Transplant(y, y->right);
			y->right = N->right;
			y->right->parent = y;
		}

		RB_Transplant(N, y);
		y->left = N->left;
		y->left->parent = y;
		y->color = N->color;
	}

	if (y_original_color == black) {

		RB_DeleteFixUp(x);
	}
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	return num_pairs;
}


// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {

	if (search(root, k) != nil) { // there is a pair
		return true;
	}

	return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {

	Node *N = search(root, k); // getting reference to value 

	if (N == nil) {
		throw::logic_error("Dictionary: getValue() key \"blah\" does not exist");
	}

	return (N->val);
}


// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {

	if (current != nil) { // current iterator is defined
		return true;
	} 

	return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {

	if (hasCurrent() == false) {
		throw::logic_error("Dictionary: currentKey(): current undefined");
	}

	return (current->key);
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {

	if (hasCurrent() == false) {
		throw::logic_error("Dictionary: currentVal(): current undefined");
	}
	
	return (current->val);
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {

	postOrderDelete(root);
	root = nil;
	current = nil;
	num_pairs = 0;
}


// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {

	Node *y = nil;
	Node *x = this->root;

	while (x != nil) {

		y = x;
		if (k < x->key) {
	
			x = x->left;
		}

		else if (x->key == k) { // when key == k

			x->val = v; // overrwriting the corresponding value with v
			return;
		}

		else {

			x = x->right;
		}
	}

	Node *z = new Node(k, v);
	z->parent = y;
	z->left = nil;
	z->right = nil;
	z->color = 1;
	
	if (y == nil) {

		root = z;
	}

	else if (z->key < y->key) {

		y->left = z;
	}
	else {

		y->right = z;
	}

	num_pairs ++; 

	RB_InsertFixUp(z);
}


// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {

	if (!(contains(k))) {

		throw std::logic_error("Dictionary: remove(): key \"blah\" does not exist");
	}
	
	Node *z = search(root, k); // the found node

	if (current == z) { // if that pair is current, then current becomes undefined
		current = nil;
	}

	RB_Delete(z);

	delete z; // deleting the pair
	num_pairs -= 1;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {

	if (num_pairs == 0) { // it is empty
		return;
	}

	current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {

	if (num_pairs == 0) { // it is empty
		return;
	}

	current = findMax(root);
}


// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {

	if (!(hasCurrent())) {

		throw std::logic_error("Dictionary: next(): current undefined");
	}

	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {

    if (!(hasCurrent())) {

        throw std::logic_error("Dictionary: prev(): current undefined");
    }

	current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {

	std::string s = "";
	inOrderString(s, root);

	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {

	std::string s = "";
	preOrderString(s, root); // by a pre order walk 

	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {

	if (this->to_string() == D.to_string()) { // they are the same
		
		return true;
	}

	return false;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {

	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {

	if (this != &D) {
		Dictionary temp = D; // make a copy of dictionary

		// then swap the copy's fields with the fields of this
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);

	}

	// return this with the new data installed
	return *this;
}



