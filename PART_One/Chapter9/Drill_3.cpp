#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

class Date {
	int y;       // year
	int m;     // month in year
	int d;      // day of month

	public:
	Date(int y, int m, int d);
	void add_day(int n);
	int year() {return y;}
	int month() {return m;}
	int day() {return d;}

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

void Date::add_day(int n)
{
	d += 1;
	// increase dd by n days
}

int main() 
{

	Date try1 {1978, 6, -5};
	Date try2 {1978, 6, -5};

	Date today {1978, 6, 25};

	Date tomorrow = today;
	
	tomorrow.add_day(1);

	cout << today.day() << '\t' << tomorrow.day() << '\n';

	return 0;
}
