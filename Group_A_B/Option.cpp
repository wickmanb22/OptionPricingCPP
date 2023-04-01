// Source file to implement the virtual Option base class
// Brian Wickman

// Header guard
#ifndef option_cpp
#define option_cpp

// Dependencies
#include "Option.h"
#include <iostream>
#include <vector>

// Namespace
using namespace std;

// Define array with names for optionType
//const char* optionType_names[] = { "call", "put" };

// Constructors 
Option::Option() : option_type(call), expiry(0.25), strike(65.0), sig(0.30), rf_rate(0.08), asset_price(60.0), cost_of_carry(0.08) { }

Option::Option(optionType option_type, double expiry, double strike, double sig,
	double rf_rate, double asset_price) : option_type(option_type), expiry(expiry), strike(strike), sig(sig), rf_rate(rf_rate), asset_price(asset_price), cost_of_carry(rf_rate) { }

Option::Option(optionType option_type, double expiry, double strike, double sig,
	double rf_rate, double asset_price, double cost_of_carry) : option_type(option_type), expiry(expiry), strike(strike), sig(sig), rf_rate(rf_rate), asset_price(asset_price), cost_of_carry(cost_of_carry) {}

Option::Option(optionType option_type, array<double, 5> option_input) : option_type(option_type), expiry(option_input[0]), strike(option_input[1]), sig(option_input[2]), rf_rate(option_input[3]), asset_price(option_input[4]), cost_of_carry(option_input[3]) { }

Option::Option(optionType option_type, array<double, 6> option_input) : option_type(option_type), expiry(option_input[0]), strike(option_input[1]), sig(option_input[2]), rf_rate(option_input[3]), asset_price(option_input[4]), cost_of_carry(option_input[5]) { }

Option::Option(const Option& opt) : option_type(opt.option_type), expiry(opt.expiry), strike(opt.strike), sig(opt.sig), rf_rate(opt.rf_rate), asset_price(opt.asset_price), cost_of_carry(opt.cost_of_carry) { }

Option::~Option() { } // destructor

// Operators
Option& Option::operator= (const Option& opt)
{ // assignment
	option_type = opt.option_type;
	expiry = opt.expiry;
	strike = opt.strike;
	sig = opt.sig;
	rf_rate = opt.rf_rate;
	asset_price = opt.asset_price;
	return *this;
}

// Member functions
// optionPrice() is pure virtual so no implementation

#endif