// Header file to define MatrixPricer class
// Brian Wickman

// Header guard
#ifndef matrix_pricer_option
#define matrix_pricer_option

// Dependencies
#include "Option.h"
#include "EuropeanOption.h"
#include <vector>

using namespace std;

class MatrixPricer
{
public:
	// constructors 
	MatrixPricer();
	MatrixPricer(const MatrixPricer& source);
	MatrixPricer(const vector<array<double, 5>>& new_mat);

	// how to include matrix pricer 
	
};


#endif