// Source file to implement the OptionMatrix class
// Brian Wickman

// Header guard
#ifndef option_matrix_cpp
#define option_matrix_cpp

// Dependencies
#include "OptionMatrix.h"
#include "Option.h"
#include <iostream>
#include <vector>

// Namespace
using namespace std;

// Constructors 
OptionMatrix::OptionMatrix() : option_vector() { }
OptionMatrix::OptionMatrix(vector<EuropeanOption> vec_opt) : option_vector(vec_opt) {}
OptionMatrix::OptionMatrix(const OptionMatrix& source) : option_vector(source.option_vector) {}
OptionMatrix::~OptionMatrix() {}

// Operators
OptionMatrix& OptionMatrix::operator= (const OptionMatrix& source)
{
	option_vector = source.option_vector;
	return *this;
}

// Member functions
vector<double> OptionMatrix::matrixPricer() const
{
	vector<double> option_prices(option_vector.size());
	for (int i = 0; i < option_vector.size(); i++)
	{ // for each option in vector, compute the price
		option_prices[i] = option_vector[i].optionPrice();
	}
	return option_prices;
}

#endif

