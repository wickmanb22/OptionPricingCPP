// Program to test Group A Part 1 for level 9
// Brian Wickman

// Dependencies
#include "EuropeanOption.h"
#include "PerpAmericanOption.h"
#include "OptionMatrix.h"
#include "Option.h"
#include <vector>
#include <cmath>
#include <iostream>

// Namespaces
using namespace std;

// Global mesh array function
vector<double> meshArray(double start, double end, int h)
{ // returns sequential vector
	int length = floor((h + end - start) / h);
	vector<double> v(length);
	for (int i = 0; i < length; i++)
	{ // create sequence
		v[i] = start + (i * h);
	}
	return v;
}

int main()
{
	// Parts A & B
	cout << "-------------Part A & B-----------" << endl;

	// Define PerpAmericanOption
	array<double, 5> batch_param = { 100.0, 0.1, 0.1, 110, 0.02 };

	PerpAmericanOption call = PerpAmericanOption(PerpAmericanOption::optionType::call, batch_param);
	PerpAmericanOption put = PerpAmericanOption(PerpAmericanOption::optionType::put, batch_param);

	 // Calculate Prices
	cout << "Price of perpetual american call:" << call.optionPrice() << endl;
	cout << "Price of perpetual american put:" << put.optionPrice() << endl;

	// Parts C & D
	cout << "-------------Part C & D-----------" << endl;
	cout << "Price of Perpetual American calls with asset prices 95, 100, 105, 110, 115, respectively" << endl;


	// Create vector of Perp american options that vary by asset price
	vector <array<double, 5>> array_future_param = { batch_param, batch_param, batch_param, batch_param, batch_param };
	vector<double> asset_price_vec = meshArray(95, 115, 5);

	vector<PerpAmericanOption> american_option_vec;
	for (int i = 0; i < array_future_param.size(); i++)
	{ // create vector of perp american options
		array_future_param[i][3] = asset_price_vec[i]; // replace asset price
		PerpAmericanOption future_call = PerpAmericanOption(PerpAmericanOption::optionType::call, array_future_param[i]);
		american_option_vec.push_back(future_call);
	}

	// Create vector of option pointers
	vector<Option*> option_vec;
	for (int i = 0; i < american_option_vec.size(); i++)
	{
		Option* american_call_ptr = &american_option_vec[i]; // create option pointer
		option_vec.push_back(american_call_ptr); // add to vector of option pointers
	}

	// Assemble vector into OptionMatrix object 
	OptionMatrix optMat = option_vec;
	vector<double> prices_vec = optMat.matrixPricer();

	// Call prices
	for (int i = 0; i < prices_vec.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " call price: " << prices_vec[i] << endl;
	}

}