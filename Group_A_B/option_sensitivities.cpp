// Program to test Group A Part 2 for level 9
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
	array<double, 6> future_param = { 0.5, 100.0, 0.36, 0.1, 105.0, 0.0 };

	// Construct future options
	EuropeanOption future_call = EuropeanOption(EuropeanOption::optionType::call, future_param);
	EuropeanOption future_put = EuropeanOption(EuropeanOption::optionType::put, future_param);

	// Calculate delta
	cout << "Price of delta call: " << future_call.deltaSensitivity() << endl;
	cout << "Price of delta put: " << future_put.deltaSensitivity() << endl;
	cout << "Price of gamma call: " << future_call.gammaSensitivity() << endl;
	cout << "Price of gamma put: " << future_put.gammaSensitivity() << endl;

	// Part C 
	cout << "-----------Part C ---------" << endl;
	cout << "Price of delta calls with asset prices 95, 100, 105, 110, 115, respectively" << endl;

	// Create vector of European options that vary by strike price
	vector <array<double, 6>> array_future_param = { future_param, future_param, future_param, future_param, future_param };
	vector<double> asset_price_vec = meshArray(95, 115, 5);

	vector<EuropeanOption> euro_option_vec;
	for (int i = 0; i < array_future_param.size(); i++)
	{ // create vector of european options
		array_future_param[i][4] = asset_price_vec[i]; // replace asset price
		EuropeanOption future_call = EuropeanOption(EuropeanOption::optionType::call, array_future_param[i]); // create EuroOption
		euro_option_vec.push_back(future_call);
	}

	// Create vector of option pointers
	vector<Option*> future_call_vec;
	for (int i = 0; i < euro_option_vec.size(); i++)
	{
		Option* future_call_ptr = &euro_option_vec[i]; // create option pointer
		future_call_vec.push_back(future_call_ptr); // add to vector of option pointers
	}

	// Assemble vector into OptionMatrix object 
	OptionMatrix optMat = future_call_vec;
	vector<double> delta_vec = optMat.matrixDelta();

	// Delta prices
	for (int i = 0; i < delta_vec.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " delta price: " << delta_vec[i] << endl;
	}
	
	// Gamma prices
	cout << "Price of gamma calls with asset prices 95, 100, 105, 110, 115, respectively" << endl;
	vector<double> gamma_vec = optMat.matrixGamma();

	// Output prices
	for (int i = 0; i < gamma_vec.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " gamma price: " << gamma_vec[i] << endl;
	}

	// Part D 
	cout << "-----------Part D ---------" << endl;
	cout << "Approximate delta and gamma options (h = 1 for demonstration purposes)" << endl;

	// Delta and gamma estimations
	cout << "Approximate price of delta call: " << future_call.approxDelta(1) << endl;
	cout << "Approximate price of delta put: " << future_put.approxDelta(1) << endl;
	cout << "Approximate price of gamma call: " << future_call.approxGamma(1) << endl;
	cout << "Approximate price of gamma put: " << future_put.approxGamma(1) << endl;

	// Delta estimations for vector of options
	cout << "Delta approximations for same options as above" << endl;
	vector<double> delta_approx_vec = optMat.matrixApproxDelta(1.0);
	for (int i = 0; i < delta_approx_vec.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " delta price: " << delta_approx_vec[i] << endl;
	}
}