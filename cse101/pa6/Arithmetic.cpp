/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 6
* Arithmetic.cpp
* performing arithmetic operations on arbitrarily large signed integers
*********************************************************************************/

#include "BigInteger.h" 

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

// pseudocode from FILE IO from tantalo
int main(int argc, char * argv[]) {

    ifstream in;
    ofstream out;

    // check command line for correct number of arguments
    if( argc != 3 ){
       cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
       return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
       cerr << "Unable to open file " << argv[1] << " for reading" << endl;
       return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
       cerr << "Unable to open file " << argv[2] << " for writing" << endl;
       return(EXIT_FAILURE);
    }

	// parsing through the first three lines
	string a, useless, b;
	getline(in, a);
	getline(in, useless);
	getline(in, b);

	// conversion
	BigInteger A = BigInteger(a);
	BigInteger B = BigInteger(b);

	// string dictionary
	BigInteger two = BigInteger("2");
	BigInteger three = BigInteger("3");
	BigInteger nine = BigInteger("9");
	BigInteger sixteen = BigInteger("16");

	// printing A
	out << A << endl << endl;

	// priting B;
	out << B << endl << endl;

	// printing A + B;
	out << (A+B) << endl << endl;

	// printing A-B
	out << (A-B) << endl << endl;

	// printing A-A
	out << (A-A) << endl << endl;

	// printing 3A-2B
	out << (three * A) - (two * B) << endl << endl;

	// printing A*B
	out << (A * B) << endl << endl;

	// printing A*A
	out << (A * A) << endl << endl;

	// printing B*B
	out << (B * B) << endl << endl;

	// printing 9 * A^4 + 16 * B^5
	out << (nine * (A * A * A * A)) + (sixteen * (B * B * B * B * B)) << endl;

	// closing ceremony
	in.close();
	out.close();

	return EXIT_SUCCESS;

}

