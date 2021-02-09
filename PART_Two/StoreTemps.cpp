#include<iostream>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include "../std_lib_facilities.h"
using namespace std;

struct Reading 
{
	char kind {'C'};
	int hour;
	double temp;
};

ostream& operator<<(ostream& os, const Reading& Read)
{
	os << Read.hour << '\t' << Read.temp << '\t' << Read.kind << endl;

	return os;
};

double ToFar(double t)
{
	return t * 9/5 + 32;
}

void WriteReadings (int n, const int max, const int min) 
{
	vector<Reading> vec;
	int true_max = max - min;

	ofstream ofs {"raw_temps.txt"};
	
	for (int i = 0; i < n; i++) {
		
		Reading Read;

		Read.hour = rand() % 24;
		double temp = rand() % true_max + min;
		Read.temp = temp;

		int k = rand() % 2;
		if (k == 0) {
			Read.kind = 'F';
			Read.temp = ToFar(temp);
		}

		ofs << Read;

	}
}

int main() 
{
	int n, max, min;

	cout << "Please insert  number of Readings to generate [n], max temp and min temp. \n"
		"Format: n max min.\n"; 
	cin >> n >> max >> min;

	WriteReadings(n,max,min);

	cout << "Readings written to raw_temps.txt\n";
}
