/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 8
* WordFrequency.cpp
* It will print the frequencies of each word
*********************************************************************************/


#include "Dictionary.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

// pseudocode from FILE IO
int main(int argc, char * argv[]) {

	ifstream in;
	ofstream out;

	size_t begin, end, len;
	string tokenBuffer;
	string token;
	string line;	

	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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

	Dictionary output;	

	// It will read in each line of a file
	while (getline(in, line)) {
		len = line.length();

		// get tokens in this line
        tokenBuffer = "";		
	
		// get first token
		begin = min(line.find_first_not_of(delim, 0), len);
		end   = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end-begin);

		while( token!="" ){  // we have a token

			// convert each word to all lower case characters
			for (int i = 0; i < (int) token.length(); i++) {
				token[i] = tolower(token[i]);
			}				
			
			// it should first check to see if the word (key) is already present, using contains()

			if (output.contains(token)) { // If it already exists, increment  by calling getValue()
			
				output.getValue(token) += 1;; 

			} else { // If it is a new word, add it using setValue()

				output.setValue(token, 1);
			}

        	// update token buffer
        	tokenBuffer += "   "+token+"\n";

        	// get next token
        	begin = min(line.find_first_not_of(delim, end+1), len);
        	end   = min(line.find_first_of(delim, begin), len);
        	token = line.substr(begin, end-begin);
      	}

	}

	// printing output
	out << output << endl;

	// cleaning up
	in.close();
	out.close();

	return (EXIT_SUCCESS);
}




