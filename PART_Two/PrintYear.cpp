#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include "../std_lib_facilities.h"
using namespace std;

const int not_a_reading = -7777;       // less than absolute zero
const int not_a_month = -1;


struct Day {
	vector<double> hour {vector<double>(24,not_a_reading)};
};

struct Month {                                         // a month of temperature readings
	int month {not_a_month};         // [0:11] January is 0
	vector<Day> day {32};                // [1:31] one vector of readings per day
};

struct Year {               // a year of temperature readings, organized by month
	int year;                                         // positive == A.D.
	vector<Month> month {12};    // [0:11] January is 0
};

void print_year (ofstream& ofs, Year y)
	// This prints a tab delimited file in long format very easy to use
	// The obvious simple improvement would be to not print missing data
{
	for (Month m : y.month) {
		for (int i = 1; i < m.day.size(); i++) {
			int d = i;
			for (int j = 0; j < m.day[i].hour.size(); j++) {
				int h = j + 1;
				ofs << y.year << '\t' << m.month << '\t' << d << '\t' << h << '\t' << m.day[i].hour[j] << endl;
			}
		}
	}
	
}
int main()
{
	vector<Year> ys(1);

	ofstream ofs {"years.txt"};
	if (!ofs) error("can't open file");

	for (Year& y : ys) print_year(ofs,y);

	return 0;
}

