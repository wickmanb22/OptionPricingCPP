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

	// Create sequence of monotonically increasing prices
	vector<double> asset_price_vec;
	double start = 95;
	double end = 115;
	int h = 5;
	asset_price_vec = meshArray(start, end, h);

	// Create vector of options that vary by strike price
	// Vector of European Options
	vector<EuropeanOption> vector_call = { future_call, future_call,future_call,future_call,future_call };

	// Replace asset price of each option
	for (int i = 0; i < vector_call.size(); i++)
	{
		vector_call[i].asset_price = asset_price_vec[i];
	}

	// Assemble vector into OptionMatrix object 
	OptionMatrix opt_matrix(vector_call);
	vector<double> delta_vec = opt_matrix.matrixDelta();

	// Delta prices
	for (int i = 0; i < vector_call.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " delta price: " << delta_vec[i] << endl;
	}

	// Gamma prices
	cout << "Price of gamma calls with asset prices 95, 100, 105, 110, 115, respectively" << endl;
	vector<double> gamma_vec = opt_matrix.matrixGamma();

	// Output prices
	for (int i = 0; i < vector_call.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " gamma price: " << gamma_vec[i] << endl;
	}

	// Part D 
	cout << "-----------Part D ---------" << endl;
	cout << "Approximate delta and gamma options (h = 1 for demonstration purposes)" << endl;

	// Delta and gamma estimations
	cout << "Approximate price of delta call: " << future_call.approxDelta(1) << endl;
	cout << "Apporximate price of delta put: " << future_put.approxDelta(1) << endl;
	cout << "Apporximate price of gamma call: " << future_call.approxGamma(1) << endl;
	cout << "Apporximate price of gamma put: " << future_put.approxGamma(1) << endl;

	// Delta estimations for vector of options
	cout << "Delta approximations for same options as above" << endl;
	vector<double> delta_approx_vec = opt_matrix.matrixApproxDelta(1.0);
	for (int i = 0; i < vector_call.size(); i++)
	{ // Print prices
		cout << "Option #" << i + 1 << " delta price: " << delta_approx_vec[i] << endl;
	}

}