// Main program for level 9
// Brian Wickman

// Dependencies
#include "EuropeanOption.h"
#include "Option.h"
#include <array>
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
	EuropeanOption::optionType type = EuropeanOption::optionType::call;
	array<double, 5> batch1_param = { 0.25, 65.0, 0.30, 0.08, 60.0 };
	array<double, 5> batch2_param = { 1.0, 100.0, 0.2, 0.0, 100.0 };
	array<double, 5> batch3_param = { 1.0, 10.0, 0.50, 0.12, 5.0 };
	array<double, 5> batch4_param = { 30.0, 100.0, 0.30, 0.08, 100.0 };

	// Construct calls
	EuropeanOption batch1_call = EuropeanOption(type, batch1_param);
	EuropeanOption batch2_call = EuropeanOption(type, batch2_param);
	EuropeanOption batch3_call = EuropeanOption(type, batch3_param);
	EuropeanOption batch4_call = EuropeanOption(type, batch4_param);

	// Construct puts
	EuropeanOption::optionType type_put = EuropeanOption::optionType::put;
	EuropeanOption batch1_put = EuropeanOption(type_put, batch1_param);
	EuropeanOption batch2_put = EuropeanOption(type_put, batch2_param);
	EuropeanOption batch3_put = EuropeanOption(type_put, batch3_param);
	EuropeanOption batch4_put = EuropeanOption(type_put, batch4_param);

/*
	// Check prices
	cout << "Batch 1; Call: " << batch1_call.optionPrice() << " Put: " << batch1_put.optionPrice() << endl;
	cout << "Batch 2; Call: " << batch2_call.optionPrice() << " Put: " << batch2_put.optionPrice() << endl;
	cout << "Batch 3; Call: " << batch3_call.optionPrice() << " Put: " << batch3_put.optionPrice() << endl;
	cout << "Batch 4; Call: " << batch4_call.optionPrice() << " Put: " << batch4_put.optionPrice() << endl;


	// Put-call parity
	cout << "This should satisfy the put-call parity: " << endl;
	double batch1_put_price = batch1_call.pcParity();
	cout << "Price of batch 1 corresponding put: " << batch1_put_price << endl;
	batch1_call.pcParity(batch1_put_price);
	
	cout << "This should not satisfy the put-call parity: " << endl;
	double bad_price = batch1_put_price + 1.0;
	batch1_call.pcParity(bad_price);

	
	// Create sequence of monotonically increasing prices
	vector<double> strike_price_vec;
	double start = 5;
	double end = 25;
	int h = 5;
	strike_price_vec = meshArray(start, end, h);
	cout << "Size of strike price sequence: " << strike_price_vec.size() << endl;

	// Create matrix of options that vary by strike price
	vector<array<double, 5>> strike_price_matrix = { batch3_param, batch3_param, batch3_param, batch3_param, batch3_param };

	// Replace 5th element (strike price) of each array
	for (int i = 0; i < strike_price_matrix.size(); i++)
	{
		strike_price_matrix[i][4] = strike_price_vec[i];
	}

	// Print matrix to verify
	for (int i = 0; i < strike_price_matrix.size(); i++) {
		cout << "Option #" << (i+1) << " parameters: ";
		for (int j = 0; j < strike_price_matrix[i].size(); j++) {
			cout << strike_price_matrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;


	// Part C: Option prices for different asset prices
	// define option parameters with array
	vector<double> price_vector = meshArray(50, 70, 5); // vector of stock prices
	vector<double> option_prices(price_vector.size()); // vector to hold option prices

	for (int i = 0; i < price_vector.size(); i++)
	{ // price options at different stock prices		
		// create option
		array<double, 5> opt_param = { 0.25, 65.0, 0.30, 0.08, price_vector[i] };
		EuropeanOption opt = EuropeanOption(type, opt_param);

		// calc price
		option_prices[i] = opt.optionPrice();
	}
	
	cout << "Option prices: " << endl;
	for (int i = 0; i < option_prices.size(); i++)
	{
		cout << option_prices[i] << ' ';
	}
	*/
	
	// Part D: Option prices as a function of any parameter

}