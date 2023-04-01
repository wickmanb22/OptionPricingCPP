// Source file to implement the European Option class
// Brian Wickman

// Header guard
#ifndef euro_option_cpp
#define euro_option_cpp

// Dependencies
#include "Option.h"
#include "EuropeanOption.h"
#include <boost/random.hpp>
#include <boost/math/distributions/normal.hpp>

// Namespace
using namespace std;
using namespace boost::math;

// Define array with names for optionType
//const char* optionType_names[] = { "call", "put" };

// Constructors
EuropeanOption::EuropeanOption() : Option() { }

EuropeanOption::EuropeanOption(optionType option_type, double expiry, double strike, double sig,
	double rf_rate, double asset_price) : Option(option_type, expiry, strike, sig, rf_rate, asset_price) { }

EuropeanOption::EuropeanOption(optionType option_type, double expiry, double strike, double sig,
	double rf_rate, double asset_price, double cost_of_carry) : Option(option_type, expiry, strike, sig, rf_rate, asset_price, cost_of_carry) { }

EuropeanOption::EuropeanOption(optionType option_type, array<double, 5> option_input) : Option(option_type, option_input) { }

EuropeanOption::EuropeanOption(optionType option_type, array<double, 6> option_input) : Option(option_type, option_input) { }

EuropeanOption::EuropeanOption(const EuropeanOption& opt) : Option(opt) { }

EuropeanOption::~EuropeanOption() { }

// Operators
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& opt) 
{ // assignment operator
	Option::operator=(opt);
	return *this;
}

// Member functions
double EuropeanOption::optionPrice() const
{ // price of european option
	// calculate d1, d2
	double d1, d2;
	d1 = (log(asset_price / strike) + (cost_of_carry + (sig * sig) / 2) * expiry) / (sig * sqrt(expiry));
	d2 = d1 - (sig * sqrt(expiry));
	
	// standard normal CDF
	normal_distribution<double> standardNormal(0.0, 1.0);

	double option_price = 0.0;
	if (option_type == call)
	{ // call formula
		option_price = (asset_price * exp((cost_of_carry - rf_rate) * expiry) * cdf(standardNormal, d1)) - (strike * exp(-1 * rf_rate * expiry) * cdf(standardNormal, d2));
	}
	else if (option_type == put)
	{
		option_price = (strike * exp(-1 * rf_rate * expiry) * cdf(standardNormal, (-1 * d2))) - (asset_price * exp((cost_of_carry - rf_rate) * expiry) * cdf(standardNormal, (-1 * d1)));
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

double EuropeanOption::deltaSensitivity() const
{
	// Define parameters
	double d1 = 0.0, delta = 0.0;
	d1 = (log(asset_price / strike) + (cost_of_carry + (sig * sig) / 2) * expiry) / (sig * sqrt(expiry));

	// standard normal CDF
	normal_distribution<double> standardNormal(0.0, 1.0);

	if (option_type == call)
	{
		delta = exp((cost_of_carry - rf_rate) * expiry) * cdf(standardNormal, d1);
	}
	if (option_type == put)
	{
		delta = -1 * exp((cost_of_carry - rf_rate) * expiry) * cdf(standardNormal, (-1 * d1));
	}
	return delta;
}

double EuropeanOption::approxDelta(double h_val) const
{
	// define parameters
	double estDelta = 0.0, h = h_val;
	EuropeanOption bigCopy(*this), littleCopy(*this); // create two copies

	// Modify asset prices
	bigCopy.asset_price = this->asset_price + h;
	littleCopy.asset_price = this->asset_price - h;

	// Delta formula
	estDelta = (bigCopy.optionPrice() - littleCopy.optionPrice()) / (2 * h);
	return estDelta;
}

double EuropeanOption::gammaSensitivity() const
{
	// standard normal CDF
	normal_distribution<double> standardNormal(0.0, 1.0);

	// Define parameters
	double d1;
	d1 = (log(asset_price / strike) + (cost_of_carry + (sig * sig) / 2) * expiry) / (sig * sqrt(expiry));

	// Calculate gamma
	double gamma = 0.0;
	gamma = pdf(standardNormal, d1) * exp((cost_of_carry - rf_rate) * expiry) / (asset_price * sig * sqrt(expiry));

	return gamma;
}

double EuropeanOption::approxGamma(double h_val) const
{
	// define parameters
	double estGamma = 0.0, h = h_val;
	EuropeanOption bigCopy(*this), littleCopy(*this), origCopy(*this); // create two copies

	// Modify asset prices
	bigCopy.asset_price = this->asset_price + h;
	littleCopy.asset_price = this->asset_price - h;

	// Delta formula
	estGamma = (bigCopy.optionPrice() - 2 * origCopy.optionPrice() + littleCopy.optionPrice()) / (h * h);
	return estGamma;
}


#endif