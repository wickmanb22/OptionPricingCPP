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

	// Create vector of options that vary by strike price
	// Matrix of option parameters (vector of arrays)
	vector<array<double, 5>> call_param = { batch3_param, batch3_param, batch3_param, batch3_param };

	// Create vector of European options with varying asset price
	vector<double> asset_price_vec = meshArray(5, 20, 5);
	vector<EuropeanOption> euro_option_vec;
	for (int i = 0; i < call_param.size(); i++)
	{ 
		call_param[i][4] = asset_price_vec[i]; // replace asset price
		EuropeanOption stock_call = EuropeanOption(EuropeanOption::optionType::call, call_param[i]); // create EuroOption
		euro_option_vec.push_back(stock_call);
	}

	// Create vector of option pointers for OptionMatrix class
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
		cout << "Option #" << i + 1 << " Price: " << matrixPrices[i] << endl;
	}
	
}