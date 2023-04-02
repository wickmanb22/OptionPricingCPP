// Header file to define European option class
// Brian Wickman

// Header guard
#ifndef american_option
#define american_option

// Dependencies
#include "Option.h"
#include <iostream>
#include <cmath>
#include <array>

using namespace std;

class PerpAmericanOption : public Option
{
public:
	// constructors
	PerpAmericanOption(); // default
	PerpAmericanOption(optionType option_type, double strike, double sig, double rf_rate, double asset_price, double cost_of_carry);
	PerpAmericanOption(optionType option_type, array<double, 5>);
	PerpAmericanOption(const PerpAmericanOption& opt); // copy constructor
	virtual ~PerpAmericanOption(); // destructor

	// operators
	PerpAmericanOption& operator = (const PerpAmericanOption& opt); // assignment operator

	// member functions
	double optionPrice() const;
	double deltaSensitivity() const; // need to implement these pvmf's 
	double approxDelta(double h) const;
	double gammaSensitivity() const;
	double approxGamma(double h) const;
};

#endif