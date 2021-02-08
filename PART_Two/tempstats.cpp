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
};


// operator overload
istream& operator>>(istream& is, Reading& r)
{
	int x,y;

	is >> x >> y;

	r.hour = x;
	r.temp = y;

	return is;
}

ostream& operator<<(ostream& os, Reading& Read)
{
	os << Read.hour << '\t' << Read.temp << endl;

	return os;
};


double Median (const vector<int>& x)
{
	int result;

	if (x.size()%2 == 1) { 
		result = x[x.size()/2];
	}

	if (x.size()%2 == 0) { 
		result = x[x.size()/2 -1] + ((x[x.size()/2] - x[x.size()/2 -1]) /2);
	}
	return result;
}

double Mean (const vector<int>& x)
{
    double sum;

	for (int n : x) sum += n;    

    return sum / (x.size() + 1);
}


int main () 
{
	vector<int> temps;

	ifstream ifs {"raw_temps.txt"};
	if (!ifs) cerr << "Can't open the file!\n";

	for (Reading Read; ifs >> Read;) {
		temps.push_back(Read.temp);
	}

	int mean = Mean(temps);
	int median = Median(temps);

	cout << "\nMedian = " << median << endl
		<< "Mean = " << mean << endl;

	return 0;
}
