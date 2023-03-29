// Source file to implement the European Option class
// Brian Wickman

// Header guard
#ifndef euro_option_cpp
#define euro_option_cpp

// Dependencies
#include "EuropeanOption.h"
#include <boost/random.hpp>
#include <boost/math/distributions/normal.hpp>

// Namespace
using namespace std;
using namespace boost::math;

// Define array with names for optionType
const char* optionType_names[] = { "call", "put" };

// Constructors
EuropeanOption::EuropeanOption() : option_type(call), expiry(0.25), strike(65.0), sig(0.30), rf_rate(0.08), asset_price(60.0) { }

EuropeanOption::EuropeanOption(optionType option_type, double expiry, double strike, double sig,
	double rf_rate, double asset_price) : option_type(option_type), expiry(expiry), strike(strike), sig(sig), rf_rate(rf_rate), asset_price(asset_price) { }

EuropeanOption::EuropeanOption(optionType option_type, array<double, 5> option_input) : option_type(option_type), expiry(option_input[0]), strike(option_input[1]), sig(option_input[2]), rf_rate(option_input[3]), asset_price(option_input[4]) { }

EuropeanOption::EuropeanOption(const EuropeanOption& option) : option_type(option.option_type), expiry(option.expiry), strike(option.strike), sig(option.sig), rf_rate(option.rf_rate), asset_price(option.asset_price) { }

EuropeanOption::~EuropeanOption() { }

// Operators
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option) 
{ // assignment operator
	option_type = option.option_type;
	expiry = option.expiry;
	strike = option.strike;
	sig = option.sig;
	rf_rate = option.rf_rate;
	asset_price = option.asset_price;

	return *this;
}

// Member functions
double EuropeanOption::optionPrice() const
{ // price of european option
	// calculate d1, d2
	double d1, d2;
	double b = rf_rate; // for black-scholes stock options
	d1 = (log(asset_price / strike) + (b + (sig * sig) / 2) * expiry) / (sig * sqrt(expiry));
	d2 = d1 - (sig * sqrt(expiry));
	
	// standard normal CDF
	normal_distribution<double> standardNormal(0.0, 1.0);

	double option_price = 0.0;
	if (option_type == call)
	{ // call formula
		option_price = (asset_price * cdf(standardNormal, d1)) - (strike * exp(-1 * rf_rate * expiry) * cdf(standardNormal, d2));
	}
	else if (option_type == put)
	{
		option_price = (strike * exp(-1 * rf_rate * expiry) * cdf(standardNormal, (-1 * d2))) - (asset_price * cdf(standardNormal, (-1 * d1)));
	}
	else {
		cout << "Invalid option type.";
		return 0;
	}

	return option_price;
}

double EuropeanOption::pcParity() const
{ // Put-call parity with one input
	double pc_answer;
	if (option_type == call)
	{ // if input is call, return price of put
		double call_price = optionPrice(); // option price
		pc_answer = call_price + (strike * exp(-1 * rf_rate * expiry)) - asset_price; // formula
		return pc_answer;
	}
	else if (option_type == put)
	{ // if input is put, return price of call
		double put_price = optionPrice(); // price of option
		pc_answer = put_price + asset_price - (strike * exp(-1 * rf_rate * expiry));
		return pc_answer;
	}
	else 
	{
		cout << "Invalid option type." << endl; 
		return 0;
	}
}

void EuropeanOption::pcParity(double option_price) const
{ // Compare two options with the put-call parity
	if (option_type == call)
	{
		double lhs, rhs;
		lhs = optionPrice() + (strike * exp(-1 * rf_rate * expiry));
		rhs = option_price + asset_price;

		if (lhs == rhs)
			cout << "These prices do satisfy the put call parity" << endl;
		else
			cout << "The price of the corresponding put does not satisfy the put-call parity" << endl;
	}
	else if (option_type == put)
	{
		double lhs, rhs;
		lhs = option_price + (strike * exp(-1 * rf_rate * expiry));
		rhs = optionPrice() + asset_price;

		if (lhs == rhs)
			cout << "These prices do satisfy the put call parity" << endl;
		else
			cout << "The price of the corresponding call does not satisfy the put-call parity" << endl;
	}
	else
	{
		cout << "Invalid option type." << endl;
	}
}

#endif