// Program to test optionMatrix class for level 9
// Brian Wickman

// Dependencies
#include "EuropeanOption.h"
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
	// define batch parameters
	array<double, 6> stock_param = { 0.5, 100.0, 0.36, 0.1, 105.0, 0.0 };
	vector <array<double, 6>> array_stock_param = { stock_param, stock_param, stock_param };

	// Replace each option asset prices, create option pointer vector
	vector<double> asset_price_vec = meshArray(90, 100, 5);
	vector<EuropeanOption> euro_option_vec;
	for (int i = 0; i < array_stock_param.size(); i++)
	{ // create vector of european options
		array_stock_param[i][4] = asset_price_vec[i]; // replace asset price
		EuropeanOption stock_call = EuropeanOption(EuropeanOption::optionType::call, array_stock_param[i]); // create EuroOption
		euro_option_vec.push_back(stock_call);
	}

	// Create vector of option pointers
	vector<Option*> stock_call_vec;
	for (int i = 0; i < euro_option_vec.size(); i++)
	{
		Option* stock_call_ptr = &euro_option_vec[i]; // create option pointer
		stock_call_vec.push_back(stock_call_ptr); // add to vector of option pointers
	}

	// Price options
	OptionMatrix optMat = stock_call_vec;
	vector<double> matrixPrices = optMat.matrixPricer();
	for (int i = 0; i < matrixPrices.size(); i++)
	{ // Print prices
		cout << matrixPrices[i] << endl;
	}
}