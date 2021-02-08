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
	int hour;
	double temp;
};

ostream& operator<<(ostream& os, Reading& Read)
{
	os << Read.hour << '\t' << Read.temp << endl;

	return os;
};


void WriteReadings (int n, const int max, const int min) 
{
	vector<Reading> vec;
	Reading Read;
	int true_max = max - min;

	ofstream ofs {"raw_temps.txt"};
	
	for (int i = 0; i < n; i++) {
		Read.hour = rand() % 24;
		Read.temp = rand() % true_max + min;
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
