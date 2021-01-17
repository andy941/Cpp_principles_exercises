#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void print(const vector<double>& x, const vector<double>& y) 
{
    cout <<  "\n" << "Price" << '\t' << "Weight" << "\n";
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << '\t' << y[i] << "\n";
    }
}

int main() 
{
	vector<double> prices = {};
	vector<double> weights = {};
	double price {};
	double weight {};
	char tmp {};


	cout << "Please insert the prices vector (spaced numbers, in one line):\n";
	while (true) {
		tmp = cin.get();

		if (tmp == '\n') break;
		if (isspace(tmp)) continue;

		cin.putback(tmp);
		
		cin >> price;
		prices.push_back(price);
	}
	
	cout << "Please insert the weights vector (spaced numbers, in one line):\n";
	while (true) {
		tmp = cin.get();

		if (tmp == '\n') break;
		if (isspace(tmp)) continue;

		cin.putback(tmp);
		
		cin >> weight;
		weights.push_back(weight);
	}
	
	if (weights.size() != prices.size()) {
		cerr << "vector sizes are not the same.\n"; 
		return 1;
	}

	print(prices, weights);

	double sum = 0;
	for (int i = 0; i < prices.size(); i++) sum += prices[i]*weights[i];

	cout << "The sum is: " << sum << "\n";

	return 0;
}




