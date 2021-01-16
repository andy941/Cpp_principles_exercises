#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void print(const vector<string>& x, const vector<double>& y) 
{
    cout <<  "\n" << "Name" << '\t' << "Age" << "\n";
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << '\t' << y[i] << "\n";
    }
}

int main() 
{
	vector<string> names = {};
	vector<double> ages = {};
	vector<double> ordered(5);
	string name;
	double age;

	cout << "Please insert names of 5 people: \n";
	for (int i = 0; i < 5; i++) {
		cin >> name;
		names.push_back(name);
	}
	
	cout << "Please insert the respective ages: \n";
	for (int i = 0; i < 5; i++) {
		cin >> age;
		ages.push_back(age);
	}

	print(names, ages);

	vector<string> copy = names;

	sort(names.begin(), names.end());
	
	for (int i = 0; i < names.size(); i++) {
		for (int j = 0; j < names.size(); j++) {
			if (copy[i] == names[j]) ordered[j] = ages[i];
		}
	}

	print(names, ordered);


}



