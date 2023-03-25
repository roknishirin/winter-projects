/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 6
* BigIntegerTest.cpp
* Contains the test of the implementation of the BigInteger coding module.
*********************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>

#include "BigInteger.h"
#include "List.h"
using namespace std;

int main(){

	// testing constructor
	BigInteger value_2 = BigInteger("-78458757845457");
	BigInteger value_1 = BigInteger("-89239872348972398234987");
	
	cout << "Neg value_1: " << value_1 << endl;
	cout << "Neg value_2: " << value_2 << endl;
	
	// testing sign and compare
	cout << "sign: " << value_1.sign() << endl;	
	cout << "comparison: " << value_1.compare(value_2) << endl;

	// testing for if both value_1 and value_2 are positive and negate
	value_1.negate();
	value_2.negate();

	cout << "Pos value_1: " << value_1 << endl;
	cout << "Pos value_2: " << value_2 << endl;

	// testing add 
	cout << "Add: " << value_1.add(value_2) << endl;
	cout << "Add: " << (value_1 + value_2) << endl;
	
	// testing sub
	cout << "Sub: " << value_1.sub(value_2) << endl;
	cout << "Sub: " << (value_1 - value_2) << endl;

	// testing mult
	cout << "Mult: " << value_1.mult(value_2) << endl;
	cout << "Mult: " << (value_1 * value_2) << endl;

	// testing new values that are both negative
	value_1 = BigInteger("-239237832782378327837832783487");
	value_2 = BigInteger("-457854745785478457478547854784578");
        
    cout << "Neg value_1: " << value_1 << endl;
    cout << "Neg value_2: " << value_2 << endl;

    // testing add 
    cout << "Add: " << value_1.add(value_2) << endl;
    cout << "Add: " << (value_1 + value_2) << endl;
        
    // testing sub
    cout << "Sub: " << value_1.sub(value_2) << endl;
    cout << "Sub: " << (value_1 - value_2) << endl;

    // testing mult
    cout << "Mult: " << value_1.mult(value_2) << endl;
    cout << "Mult: " << (value_1 * value_2) << endl;

	// testing ==
	cout << (value_1 == value_2) << endl;

	// testing <
	cout << (value_1 < value_2) << endl;

	// testing < again
	cout << (value_1 > value_2) << endl;

	// testing > 
	cout << (value_1 > value_2) << endl;

	// testing > again
	cout << (value_2 > value_1) << endl;

	// testing <= 
	cout << (value_1 <= value_2) << endl;
	cout << (value_2 <= value_1) << endl;

	// testing >= 
	cout << (value_1 >= value_2) << endl;
	cout << (value_2 <= value_1) << endl;

	// testing +=
	cout << "Before: " << value_1 << endl; 
	cout << "After: "<< (value_1 += value_2) << endl;

	// testing -=
	cout << "Before: " << value_2 << endl; 
	cout << "After: " << (value_2 -= value_1) << endl;

	// testing *=
	cout << "Before: " << value_1 << endl;
	cout << "After: "<< (value_1 *= value_2) << endl;

	// test makezero
	value_1.makeZero();
	value_2.makeZero();

	cout << "zero: " << value_1 << endl;
	cout << "zero: " << value_2 << endl;

	return EXIT_SUCCESS;
}

