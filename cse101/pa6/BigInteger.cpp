/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 6
* BigInteger.cpp
* Contains the implementation of the BigInteger coding module.
*********************************************************************************/

#include "List.h"
#include "BigInteger.h"

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

#define power 9
#define base 1000000000

// Class Constructors & Destructors -------------------------------------------

// Constructor that creates a new BigInteger in the zero state
BigInteger::BigInteger() {
	signum = 0;
	// digits already has allocated memory 
}

// Constructor that creates a new BigInteger from the string s.
BigInteger::BigInteger(std::string s) {

	// Pre: s is a non-empty string consisting of (at least one) base 10 digit		
	if (s.length() == 0) {
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}

	if ((s.length() == 1) && ((s[0] == '-') || (s[0] == '+'))) {
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}

	if (s[0] == '+') {
		signum = 1;
		s.erase(0, 1);

	} else if (s[0] == '-') {
		signum = -1;
		s.erase(0, 1);

	} else { // its a val 
		signum = 1;

	}

	// eliminate all zeros
	digits.moveFront();
	// function idea from tutor 
	std::size_t evil = s.find_first_not_of("0");
	s.erase(0, evil);

	for (unsigned long i = 0; i < s.length(); i++) {
		if (std::isdigit(s[i]) == 0) {
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}

	// convert string into List
	// storing beginning to end
	digits = List();
	digits.moveFront();

	// pseudocode from tutor Sidarth
	for (long int i = s.length() - power; ; i-=power) {
		
		if (i < 0) {
			ListElement val = stol(s.substr(0, i + power));
			digits.insertAfter(val);
			break;
		}
	
		else if (i == 0) {
			ListElement val = stol(s.substr(i, power));
			digits.insertAfter(val);	
			break;
		}	

		else if (i > 0) {
			ListElement val = stol(s.substr(i, power));
			digits.insertAfter(val);
		}

	}

}


// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
	signum = N.signum;
	digits = N.digits;	
}


// Access functions -----------------------------------------------------------

// Returns -1, 1 or 0 according to whether this BigInteger is negative
int BigInteger::sign() const {
	return signum;	
}

// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
int BigInteger::compare(const BigInteger& N) const {

	// compare signs (return stuff)
	if (this->signum > N.signum) { 
		return 1;

	} else if (this->signum < N.signum) {
		return -1;
	} 

	List Ndig = N.digits;
	List thisdig = this->digits;

	Ndig.moveFront();
	thisdig.moveFront();

	// compare lengths
	if (thisdig.length() > Ndig.length()) {
		if (this->signum > 0) {
			return 1;
		} else {
			return -1;
		}

	} else if (thisdig.length() < Ndig.length()) {
		if (this->signum < 0) {
			return 1;
		} else {
			return -1;
		}
	}

	// everything is equal so now you need to compare each node
	while ((thisdig.position() < thisdig.length()) && (Ndig.position() < Ndig.length())) {
	
		ListElement N_dig = Ndig.moveNext();
		ListElement this_dig = thisdig.moveNext();	
		if (N_dig > this_dig) {
			return -1;

		} else if (N_dig < this_dig) {
			return 1;
		}

	} 

	// everything is equal
	return 0;
}


// Manipulation procedures -------------------------------------------------

// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {

	if (digits.length() != 0) { // as long as digits isn't zero	
	
		digits.clear();
		signum = 0; // set signum to 0
	}
}

// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
void BigInteger::negate() {

	if (signum != 0) {

		signum *= -1; // easy way to reverse sign
	}
}

// Helper Functions-----------------------------------------------------------
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {

	for (L.moveFront(); L.position() < L.length();) {

		ListElement sign = L.moveNext();
		L.setBefore(sign * -1);
	}
}


// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {

	S.clear(); // ensuring it is empty

	A.moveBack(); // adding fromt back to front
	B.moveBack(); 

	// while they both have elements 
	while ((A.position() > 0) && (B.position() > 0)) {
		long num = A.movePrev() + (sgn * B.movePrev());
		S.insertAfter(num);
	}

	// while A still has something left
	while (A.position() > 0) {
		long num = A.movePrev();
		S.insertAfter(num);
	}

	// while B still has something left
	while (B.position() > 0) {
		long num = B.movePrev() * sgn;
		S.insertAfter(num);
	}
}


// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
// pseducode from tutor
int normalizeList(List& L){
	int sign = 1;

	// truely nothing in the list
	if (L.length() == 0) {
		return 1;	
	}
	
	L.moveFront();
	// getting rid of preceeding zeroes
	while (L.front() == 0) {
		L.eraseAfter();
	}
	
	// no need to do much if the length is zero
	if (L.length() == 0) {
		return 1;
	}

	// deciding what the sign is 
	if (L.front() < 0) { // first dig is neg
		negateList(L);
		sign = -1;

	} else if (L.front() > 0) {
		sign = 1;
	}

	// performing the carry
	L.moveBack();

	ListElement CarryOut = 0;
	ListElement val;
	ListElement len = L.length();

	for (ListElement i = len; i > 1; i -= 1) {

		val = L.movePrev();
		CarryOut = 0;
		
		if (val < 0) {

			CarryOut = val / base - 1;
			val = val - (CarryOut * base);
			L.setAfter(val);
			L.setBefore(L.peekPrev() + CarryOut);

		} else if (val >= base) { 

			CarryOut = val / base;
			val = val - (CarryOut * base);
			L.setAfter(val);
			L.setBefore(L.peekPrev() + CarryOut);
		}
	}	

	// getting the first value
	// changing the vals of the List
	ListElement movement = L.movePrev();
	ListElement temp = movement / base;

	if (movement < 0) { // if val < 0

		temp -= 1;
		movement = movement - ((movement / base - 1) * base);
		L.setAfter(movement);
		
		if (temp > 0 || temp < 0) { // insert the carry out as long as its not zer0
			L.insertAfter(temp);
		}

	} else if (movement >= base) { // if val >= base

		movement = movement - ((movement / base) * base);
		L.setAfter(movement);
		
		if (temp > 0 || temp < 0) { // insert the carry as long as its not zer0
			L.insertAfter(temp);
		}
	}

	// final check in case of adding more zeroes to front
    L.moveFront();
    while (L.front() == 0) {
        L.eraseAfter();
    }

    return sign;

}



// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {

	L.moveBack(); // starting from the end 

	for (int i = 0; i < p; i ++) {
		L.insertAfter(0);
	}
}


// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
// pseudocode given by TA
void scalarMultList(List& L, ListElement m) {

	L.moveBack(); // startin from the end

	long val;
	while (L.position() > 0) { // as long as your not at the beginning

		val = L.movePrev();
		L.setAfter(val * m);
	}
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {

	BigInteger Out;
	List A = this->digits;
	List B = N.digits;
	List Sum = List();

	int sign_1 = this->signum;
	int sign_2 = N.signum;

	// adding two pos
	if (sign_1 == 1 && sign_2 == 1) {

		sumList(Sum, A, B, 1);
		Out.signum = normalizeList(Sum);
		if (Out.signum == 0) {
			Out.signum = 1;
		}
		Out.digits = Sum;
		return Out;

	} else if (sign_1 == 1 && sign_2 == -1) { // one is pos

		if (A == B) {
			Out.digits = Sum;
			return Out;
		}
		sumList(Sum, A, B, -1);

		BigInteger temp = BigInteger();
		temp.digits = B;
	
/*		if (this->compare(N) == 1) {
			Out.signum = 1;
		} else {
			Out.signum = -1;
		}
*/
		Out.digits = Sum;
		Out.signum = normalizeList(Out.digits);
		return Out;

	} else if (sign_1 == -1 && sign_2 == 1) { // other is pos

        if (A == B) {
            Out.digits = Sum;
            return Out;
        }
        sumList(Sum, A, B, -1);
		Out.signum = normalizeList(Sum);

        BigInteger temp = BigInteger();
        temp.digits = B;

/*        if (this->signum == 0) {

			if (this->compare(N) == 1) {
				Out.signum = -1;
			} else {
				Out.signum = 1;
			} 

        } else {
            Out.signum = -1;
        }   
*/
		Out.signum = normalizeList(Out.digits);
        Out.digits = Sum;
        return Out;

	} else { // adding two neg 

        sumList(Sum, A, B, 1);
        normalizeList(Sum);
		Out.signum = -1;
        Out.digits = Sum;
        return Out;

	}
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {

	BigInteger Out;
	List A = this->digits;
	List B = N.digits;
	List Sub = List();

	int sign_1 = this->signum;
	int sign_2 = N.signum;

	if (this->compare(N) == 0) { // if thye are the same
		Out.digits.insertBefore(0);
		Out.signum = 0;
		return Out;
	}

	else if (sign_1 == -1 && sign_2 == 1) { // first val is neg
		negateList(A);
		sumList(Sub, A, B, -1);
		Out.digits = Sub;
		Out.signum = normalizeList(Out.digits);
		return Out;
	}

	else if (sign_1 == 1 && sign_2 == -1) { // second val is neg
		negateList(B);
		sumList(Sub, A, B, -1);
		Out.digits = Sub;
		Out.signum = normalizeList(Out.digits);
		return Out;
	}

	else if (sign_1 == 1 && sign_2 == 1) { // both pos
		sumList(Sub, A, B, -1);
		Out.digits = Sub;
		Out.signum = normalizeList(Out.digits);
		return Out;
	}

	else if (sign_1 == -1 && sign_2 == -1) { // both neg
		negateList(A);
		negateList(B);
		sumList(Sub, A, B, -1);
		Out.digits = Sub;
		Out.signum = normalizeList(Out.digits);
		return Out;
	}

	return Out;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
// pseudocode from tutor bhaswati
BigInteger BigInteger::mult(const BigInteger& N) const {

    BigInteger Out = BigInteger();
    List A = this->digits;
    List B = N.digits;
	List AA = this->digits; // copy
    List Mult = List();

    int sign_1 = this->signum;
    int sign_2 = N.signum;

	// if there is nothing, do not mutliply
	if (sign_1 == 0) { 
		return Out;
	}	

	if (sign_2 == 0) {
		return Out;
	}

	B.moveBack();
	int shift = 0; // counter for the shift

	while (B.position() > 0) {

		AA = A;

		scalarMultList(AA, B.movePrev()); // multiplication 

		shiftList(AA, shift); // shifting 
		sumList(Mult, Out.digits, AA, 1); // summing 

		normalizeList(Mult); // normalize to get the sign
		Out.digits = Mult;

		shift += 1;
	}

	// setting the signs based off of the sign
	if (sign_1 == sign_2) {
		Out.signum = 1;
		return Out;

	} else {
		Out.signum = -1;
		return Out;
	}

}


// Other Functions ---------------------------------------------------------

std::string BigInteger::to_string() {

	std::string s = "";
	
	if (this->signum == 0) { // return 0 only if the BigInteger is 0
		s = "0";
		return s;
	}

	if (this->signum == -1) { //if negative, start with '-'
		s += "-";
	}

	List D = this->digits;
	D.moveFront();

	std::string temp;

	// pseudocode given by tutor norton choy
	for (s += std::to_string(D.moveNext()); D.position() < D.length(); s += temp) {
		temp = std::to_string(D.moveNext());
		temp.insert(temp.begin(), (power - temp.length()), '0');

	}
	return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {

	return stream << N.BigInteger::to_string();
}


// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {

	return (A.compare(B) == 0);
}


// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {

	return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
	
	return (A.compare(B) <= 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) { 

	return (A.compare(B) == 1);
}


// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {

	return (A.compare(B) >= 0);
}


// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {

	return (A.add(B));
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
	
	A = (A.add(B));
	return A; 
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {

	return (A.sub(B));
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {

	A = (A.sub(B));
	return A;
}


// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
	
	return (A.mult(B));
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {

	A = A.mult(B);
	return A;
}


