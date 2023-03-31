// Header file to define OptionMatrix class
// Brian Wickman

// Header guard
#ifndef option_matrix
#define option_matrix

// Dependencies
#include "Option.h"
#include "EuropeanOption.h"
#include <vector>

using namespace std;

class OptionMatrix
{
public:
	// constructors 
	OptionMatrix();
	OptionMatrix(vector<EuropeanOption>);
	OptionMatrix(const OptionMatrix& source); // copy constructor

	// operatorss
	// assignment
	
};


#endif