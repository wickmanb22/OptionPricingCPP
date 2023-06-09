// Header file to define European option class
// Brian Wickman

// Header guard
#ifndef euro_option
#define euro_option

// Dependencies
#include "Option.h"
#include <iostream>
#include <cmath>
#include <array>

using namespace std;

class EuropeanOption : public Option
{
public:
	// constructors
	EuropeanOption(); // default
	EuropeanOption(optionType option_type, double expiry, double strike, double sig, double rf_rate, double asset_price);
	EuropeanOption(optionType option_type, double expiry, double strike, double sig, double rf_rate, double asset_price, double cost_of_carry);
	EuropeanOption(optionType option_type, array<double, 5>);
	EuropeanOption(optionType option_type, array<double, 6>);
	EuropeanOption(const EuropeanOption& opt); // copy constructor
	virtual ~EuropeanOption(); // destructor

	// operators
	EuropeanOption& operator = (const EuropeanOption& opt); // assignment operator

	// member functions
	double optionPrice() const; 
	double pcParity() const; // calculate corresponding option price
	void pcParity(double option_price) const; // check if parity satisfied
	double deltaSensitivity() const;
	double approxDelta(double h) const;
	double gammaSensitivity() const;
	double approxGamma(double h) const;
};

#endif