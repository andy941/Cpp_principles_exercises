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
	Date(int y, int m, int d);
	void add_day(int n);

};

// helper functions:

Date::Date(int yy, int mm, int dd)
{
	if (!(yy <= 2021 && yy >= 1800 &&
			mm <= 12 && mm >= 1 &&
			dd <= 31 && dd >= 1)) {cerr << "invalid date" << '\n';
		return;}

	y = yy;
	m = mm;
	d = dd;

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

	Date try1 {1978, 6, -5};
	Date try2 {1978, 6, -5};

	Date today {1978, 6, 25};

	Date tomorrow = today;
	
	add_day(tomorrow, 1);

	cout << today.d << '\t' << tomorrow.d << '\n';

	return 0;
}
