#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include "../std_lib_facilities.h"
using namespace std;

struct Reading 
{
	int hour;
	double temp;
	char kind {'C'};
};


// operator overload
istream& operator>>(istream& is, Reading& r)
{
	int x;
	double y;
	char z;

	is >> x >> y >> z;

	r.hour = x;
	r.temp = y;
	r.kind = z;

	return is;
}

ostream& operator<<(ostream& os, Reading& Read)
{
	os << Read.hour << '\t' << Read.temp << Read.kind << endl;

	return os;
};


double Median (vector<double> x)
{
	double result;

	sort(x.begin(), x.end());

	if (x.size()%2 == 1) { 
		result = x[x.size()/2];
	}

	if (x.size()%2 == 0) { 
		result = x[x.size()/2 -1] + ((x[x.size()/2] - x[x.size()/2 -1]) /2);
	}
	return result;
}

double Mean (const vector<double>& x)
{
    double sum;

	for (int n : x) sum += n;    

    return sum / (x.size() + 1);
}


int main () 
{
	vector<double> temps;
	vector<char> kinds;

	ifstream ifs {"raw_temps.txt"};
	if (!ifs) cerr << "Can't open the file!\n";

	for (Reading Read; ifs >> Read;) {
		temps.push_back(Read.temp);
		kinds.push_back(Read.kind);
	}
	
	for (int i; i < temps.size(); i++) {
		if (kinds[i] == 'F') temps[i] = (temps[i] - 32) *5/9;
	}

	double mean = Mean(temps);
	double median = Median(temps);

	cout << "\nMedian = " << median << endl
		<< "Mean = " << mean << endl;

	return 0;
}
