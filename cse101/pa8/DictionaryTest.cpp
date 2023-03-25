/********************************************************************************* 
* Shirin Rokni, shrokni
* 2023 Winter CSE101 PA# 8
* DictionaryTest.cpp
* Contains the test of the implementation of the Dictionary coding module. 
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>

#include"Dictionary.h"

using namespace std;

int main(void){

	Dictionary A;

	// testing setValue	
	A.setValue("a", 1);
	A.setValue("b", 2);
	A.setValue("c", 3);
	A.setValue("d", 4);
	A.setValue("e", 5);

	cout << A << endl;

	// testing begin and remove
	A.begin();
	A.remove("a");
	A.setValue("aa", 1);

	cout << A << endl;

	// testing size
	cout << "size: " << A.size() << endl;

	// testing contains
	if (A.contains("aa")) {
		cout << "Dictionary A does contain aa" << endl;
	} else {
		cout << "Dictionary A does not cintain aa" << endl;
	}
	
	// testing begin and currentkey
	A.begin();
	cout << "CurrentKey: " << A.currentKey() << endl;

	// testing next and currentval
	A.next();
	cout << "CurrentVal: " << A.currentVal() << endl;
	
	// testing end 
	A.end();
	cout << "CurentKey: " << A.currentKey() << endl;

	// testing prev
	A.prev();
	cout << "CurrentVal: " << A.currentVal() << endl;

	// testing getVal
	cout << "GetVal: " << A.getValue("e") << endl;

	// testing = and ==
	Dictionary B = A;
	if (B == A) {
		cout << "they are equal!" << endl;
	} else {
		cout << "they are not equal" << endl;
	}

	// testing clear
	A.clear();
	cout << "Cleared: " << A << endl;

	return(EXIT_SUCCESS);
}

/*

a : 1
b : 2
c : 3
d : 4
e : 5

aa : 1
b : 2
c : 3
d : 4
e : 5

size: 5
Dictionary A does contain aa
CurrentKey: aa
CurrentVal: 2
CurentKey: e
CurrentVal: 4
GetVal: 5
they are equal!
Cleared: 

*/
