// Header file to define European option class
// Brian Wickman

// Header guard
#ifndef euro_option
#define euro_option

// Dependencies
#include <iostream>
#include <cmath>
#include <array>

using namespace std;

class EuropeanOption
{
public:
	// parameters
	enum optionType { call, put }; // custom data type to avoid code inefficiences
	double expiry;
	double strike;
	double sig;
	double rf_rate;
	double asset_price;
	optionType option_type;

public:
	// constructors
	EuropeanOption(); // default
	EuropeanOption(optionType option_type, double expiry, double strike, double sig, double rf_rate, double asset_price);
	EuropeanOption(optionType option_type, array<double, 5>); // constructor with fixed-size array
	EuropeanOption(const EuropeanOption& option); // copy constructor
	virtual ~EuropeanOption(); // destructor

	// operators
	EuropeanOption& operator = (const EuropeanOption& option); // assignment operator

	// member functions
	double optionPrice() const; // vanilla price
	// vector<double> optionPrice() const; 
	double pcParity() const; // calculate corresponding option price
	void pcParity(double option_price) const; // check if parity satisfied
};

#endif