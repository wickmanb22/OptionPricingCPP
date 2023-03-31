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
	vector<EuropeanOption> option_vector;

public:
	// constructors 
	OptionMatrix();
	OptionMatrix(vector<EuropeanOption> vec_opt);
	OptionMatrix(const OptionMatrix& source); // copy constructor
	~OptionMatrix();

	// operators
	OptionMatrix& operator = (const OptionMatrix& mat); // assignment

	// member functions
	vector<double> matrixPricer() const; // input matrix, output vector of prices
};


#endif

