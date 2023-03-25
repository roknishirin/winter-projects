/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 8
* Order.cpp
* It will read in the lines of an input file, each
* line being a (unique) single string, then insert these strings (as keys) 
* into a Dictionary. The corresponding
* values will be the line number in the input file where the string was read.
*********************************************************************************/

#include "Dictionary.h"

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

	// empty Dictionary
	Dictionary D;
	
	// read in the lines of an input file 
	int counter = 1;

	// insert the strings as keys
	string key;

	while (getline(in, key)) { // while there is something to read

		D.setValue(key, counter);
		counter += 1;
	}

	// keys in alphabetical order
	out << D << endl;

	// keys in pre-order tree walk
	out << D.pre_string() << endl;


	// clean up
	in.close();
	out.close();


	// return succes
	return (EXIT_SUCCESS);
}

