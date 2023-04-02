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
	vector<Option*> option_vector;

public:
	// constructors 
	OptionMatrix();
	OptionMatrix(vector<Option*> vec_opt);
	OptionMatrix(const OptionMatrix& source); // copy constructor
	virtual ~OptionMatrix();

	// operators
	OptionMatrix& operator = (const OptionMatrix& mat); // assignment

	// member functions
	vector<double> matrixPricer() const; // input vector of options, output vector of prices
	vector<double> matrixDelta() const;
	vector<double> matrixApproxDelta(double h) const;
	vector<double> matrixGamma() const;
	vector<double> matrixApproxGamma(double h) const;
};


#endif

