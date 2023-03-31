// Program to test Group A Part 1 for level 9
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
	// Part A
	cout << "-------------Part A-----------" << endl;
	
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


	// Check prices
	cout << "Batch 1 Call: " << batch1_call.optionPrice() << " Put: " << batch1_put.optionPrice() << endl;
	cout << "Batch 2 Call: " << batch2_call.optionPrice() << " Put: " << batch2_put.optionPrice() << endl;
	cout << "Batch 3 Call: " << batch3_call.optionPrice() << " Put: " << batch3_put.optionPrice() << endl;
	cout << "Batch 4 Call: " << batch4_call.optionPrice() << " Put: " << batch4_put.optionPrice() << endl;

	// Part B
	cout << "-------------Part B-----------" << endl;

	// Put-call parity
		cout << "This should satisfy the put-call parity: " << endl;
		double batch1_put_price = batch1_call.pcParity();
		cout << "Price of batch 1 corresponding put: " << batch1_put_price << endl;
		batch1_call.pcParity(batch1_put_price);

		cout << "This should not satisfy the put-call parity: " << endl;
		double bad_price = batch1_put_price + 1.0;
		batch1_call.pcParity(bad_price);

	// Part C & D
	cout << "-----------Part C & D ---------" << endl;
	cout << "Price of Batch 3 Calls with asset price 5, 10, 15, 20, respectively" << endl;

	// Create sequence of monotonically increasing prices
	vector<double> asset_price_vec;
	double start = 5;
	double end = 20;
	int h = 5;
	asset_price_vec = meshArray(start, end, h);

	// Create vector of options that vary by strike price
	// Vector of European Options
	vector<EuropeanOption> vector_call = { batch3_call, batch3_call, batch3_call, batch3_call };

	// Replace asset price of each array
	for (int i = 0; i < vector_call.size(); i++)
	{
		vector_call[i].asset_price = asset_price_vec[i];
	}

	// Assemble vector into OptionMatrix object 
	OptionMatrix opt_matrix(vector_call);
	vector<double> price_vec = opt_matrix.matrixPricer();

	// Calculate prices
	for (int i = 0; i < vector_call.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " Price: " << price_vec[i] << endl;
	}
}