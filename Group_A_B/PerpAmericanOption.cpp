// Source file to implement the Perp American option class
// Brian Wickman

// Header guard
#ifndef american_option_cpp
#define perp_american_cpp

// Dependencies
#include "Option.h"
#include "PerpAmericanOption.h"

// Namespace
using namespace std;

// Constructors
PerpAmericanOption::PerpAmericanOption() : Option() { }

PerpAmericanOption::PerpAmericanOption(optionType option_type, double strike, double sig, double rf_rate, double asset_price, double cost_of_carry) : Option(option_type, 0.0, strike, sig, rf_rate, asset_price, cost_of_carry) { }

PerpAmericanOption::PerpAmericanOption(optionType option_type, array<double, 5> option_input) : Option(option_type, 0.0, option_input[0], option_input[1], option_input[2], option_input[3], option_input[4]) { }

PerpAmericanOption::PerpAmericanOption(const PerpAmericanOption& opt) : Option(opt) {}

PerpAmericanOption::~PerpAmericanOption() {}

// operators
PerpAmericanOption& PerpAmericanOption::operator = (const PerpAmericanOption& opt)
{
	Option::operator=(opt);
	return *this;
}

// member functions
double PerpAmericanOption::optionPrice() const
{ // price of perpetual american option

	double option_price = 0.0;
	if (option_type == call)
	{ // call formula
		double y_1 = 0.5 - cost_of_carry / (sig * sig) + sqrt((cost_of_carry / (sig * sig) - 0.5) * (cost_of_carry / (sig * sig) - 0.5) + 2 * rf_rate / (sig * sig));
		option_price = (strike / (y_1 - 1)) * pow(((y_1 - 1) / (y_1 * strike) * asset_price), y_1);
	}
	else if (option_type == put)
	{
		double y_2 = 0.5 - cost_of_carry / (sig * sig) - sqrt((cost_of_carry / (sig * sig) - 0.5) * (cost_of_carry / (sig * sig) - 0.5) + 2 * rf_rate / (sig * sig));
		option_price = (strike / (1 - y_2)) * pow(((y_2 - 1) / (y_2 * strike) * asset_price), y_2);
	}
	else {
		cout << "Invalid option type.";
		return 0;
	}

	return option_price;
}

double PerpAmericanOption::deltaSensitivity() const
{
	cout << "Not meaningful for perpetual american options" << endl;
	return 0.0;
}

double PerpAmericanOption::approxDelta(double h) const
{
	cout << "Not meaningful for perpetual american options" << endl;
	return 0.0;
}

double PerpAmericanOption::gammaSensitivity() const
{
	cout << "Not meaningful for perpetual american options" << endl;
	return 0.0;
}

double PerpAmericanOption::approxGamma(double h) const
{
	cout << "Not meaningful for perpetual american options" << endl;
	return 0.0;
}


#endif