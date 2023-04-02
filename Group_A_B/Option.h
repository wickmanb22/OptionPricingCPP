// Header file to define abstract option base class
// Brian Wickman

// Header guard
#ifndef option
#define option

// Dependencies
#include <iostream>
#include <cmath>
#include <array>
#include <vector>

using namespace std;

class Option
{
public:
	// option parameters
	enum optionType { call, put }; // custom data type to avoid code inefficiences
	double expiry;
	double strike;
	double sig;
	double rf_rate;
	double asset_price;
	double cost_of_carry;
	optionType option_type;

public:
	// constructors
	Option(); // default
	Option(optionType option_type, double expiry, double strike, double sig, double rf_rate, double asset_price);
	Option(optionType option_type, double expiry, double strike, double sig, double rf_rate, double asset_price, double cost_of_carry);
	Option(optionType option_type, array<double, 5>); // constructor with fixed-size array
	Option(optionType option_type, array<double, 6>); // constructor with fixed-size array

	Option(const Option& option); // copy constructor
	virtual ~Option(); // destructor

	// operators
	Option& operator = (const Option& opt); // assignment operator

	// pure virtual member functions
	virtual double optionPrice() const = 0; // pure virtual functions
	virtual double deltaSensitivity() const = 0;
	virtual double approxDelta(double h) const = 0;
	virtual double gammaSensitivity() const = 0;
	virtual double approxGamma(double h) const = 0;
};

#endif