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
OptionMatrix::OptionMatrix(vector<Option*> vec_opt) : option_vector(vec_opt) {}
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
		option_prices[i] = option_vector[i]->optionPrice();
	}
	return option_prices;
}


vector<double> OptionMatrix::matrixDelta() const
{
	vector<double> option_delta(option_vector.size());
	for (int i = 0; i < option_vector.size(); i++)
	{ // for each option in vector, compute the price
		option_delta[i] = option_vector[i]->deltaSensitivity();
	}
	return option_delta;
}

vector<double> OptionMatrix::matrixApproxDelta(double h) const
{
	vector<double> option_approx_delta(option_vector.size());
	for (int i = 0; i < option_vector.size(); i++)
	{ // for each option in vector, compute the price
		option_approx_delta[i] = option_vector[i]->approxDelta(h);
	}
	return option_approx_delta;
}

vector<double> OptionMatrix::matrixGamma() const
{
	vector<double> option_gamma(option_vector.size());
	for (int i = 0; i < option_vector.size(); i++)
	{ // for each option in vector, compute the price
		option_gamma[i] = option_vector[i]->gammaSensitivity();
	}
	return option_gamma;
}

vector<double> OptionMatrix::matrixApproxGamma(double h) const
{
	vector<double> option_approx_gamma(option_vector.size());
	for (int i = 0; i < option_vector.size(); i++)
	{ // for each option in vector, compute the price
		option_approx_gamma[i] = option_vector[i]->approxGamma(h);
	}
	return option_approx_gamma;
}


#endif

