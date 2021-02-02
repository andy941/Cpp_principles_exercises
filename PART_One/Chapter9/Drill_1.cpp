#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

// simple Date (too simple?)
struct Date {
	int y;       // year
	int m;     // month in year
	int d;      // day of month
};

// helper functions:

void init_day(Date& dd, int y, int m, int d)
{
	if (!(y <= 2021 && y >= 1800 &&
			m <= 12 && m >= 1 &&
			d <= 31 && d >= 1)) {cerr << "invalid date" << '\n';
		return;}

	dd.y = y;
	dd.m = m;
	dd.d = d;

	// check that (y,m,d) is a valid date
	// if it is, use it to initialize dd
}

void add_day(Date& dd, int n)
{
	dd.d = dd.d +1;
	// increase dd by n days
}

int main() 
{
	Date today, tomorrow, try1, try2;
	

	init_day(try1, 1978, 6, -5);
	init_day(try2, 1978, 16, -5);

	init_day(today, 1978, 6, 25);

	tomorrow = today;
	
	add_day(tomorrow, 1);

	cout << today.d << '\t' << tomorrow.d << '\n';

	return 0;
}
