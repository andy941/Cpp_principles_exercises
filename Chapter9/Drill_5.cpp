#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Year {                                                         // year in [min:max) range

	static const int min = 1800;
	static const int max = 2200;

	public:
	class Invalid { };
	Year(int x) : y{x} { if (x<min || max<=x) throw Invalid{}; }
	int year() { return y; }

	private:
	int y;
};

// simple Date (too simple?)
class Date {

	private:
	int y;       // year
	Month m;     // month in year
	int d;      // day of month

	public:
	Date(Year y, Month m, int d);

	void add_day(int n);

	int year() const {return y;}
	Month month() const {return m;}
	int day() const {return d;}

};


// helper functions:

Date::Date(Year yy, Month mm, int dd)
{
	if (!(dd <= 31 && dd >= 1)) {cerr << "invalid date" << '\n';
		return;}

	y = yy.year();
	m = mm;
	d = dd;

	// check that (y,m,d) is a valid date
	// if it is, use it to initialize dd
}

void Date::add_day(int n)
{
	d +=1;
	// increase dd by n days
}

int main() 
{

	Date try1 {1978, Month::jun, 1905};
	Date try2 {1978, Month::jun, -5};

	Date today {1978, Month::jun, 25};

	Date tomorrow = today;
	
	tomorrow.add_day(1);

	cout << today.day() << '\t' << tomorrow.day() << '\n';

	return 0;
}
