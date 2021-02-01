
//
// This is example code from Chapter 9.8 "The Date class" of 
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

// file Chrono.h

namespace Chrono {

	//------------------------------------------------------------------------------

	class Date {
		public:
			enum Month {
				jan=0, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
			};

			class Invalid { };                 // to throw as exception

			Date(int y, Month m, int d);       // check for valid date and initialize
			Date();                            // default constructor
			// the default copy operations are fine

			// non-modifying operations:
			int   day()   const { return d; }
			Month month() const { return m; }
			int   year()  const { return y; }

			// modifying operations:
			void add_day(int n);        
			void add_month(int n);
			void add_year(int n);
		private:
			int   y;
			Month m;
			int   d;
	};

	//------------------------------------------------------------------------------

	bool is_date(int y, Date::Month m, int d); // true for valid date

	//------------------------------------------------------------------------------

	bool leapyear(int y);                  // true if y is a leap year

	//------------------------------------------------------------------------------

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	//------------------------------------------------------------------------------

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);

	//------------------------------------------------------------------------------

} // Chrono

//------------------------------------------------------------------------------

//The definitions go into Chrono.cpp:

// Chrono.cpp

namespace Chrono {

	// member function definitions:

	//------------------------------------------------------------------------------

	Date::Date(int yy, Month mm, int dd)
		: y(yy), m(mm), d(dd)
	{
		if (!is_date(yy,mm,dd)) throw Invalid();
	}

	//------------------------------------------------------------------------------

	const Date& default_date()
	{
		static const Date dd(2001,Date::jan,1); // start of 21st century
		return dd;
	}

	//------------------------------------------------------------------------------

	Date::Date()
		:y(default_date().year()),
		m(default_date().month()),
		d(default_date().day())
	{
	}

	//------------------------------------------------------------------------------
	
	int days_in_month(int y, Date::Month m)
	{
		vector<int> days_per_month = {31,28,31,30,31,30,31,31,30,31,30,31};
		if (leapyear(y)) days_per_month[1] += 1;

		int days = days_per_month[static_cast<int>(m)];

		return days;
	}

	void Date::add_day(int n)
	{
		while (days_in_month(y, m) < n) {
			add_month(1);
			n -= days_in_month(y,m);
		}
		
		d += n;
	}

	//------------------------------------------------------------------------------

	void Date::add_month(int n)
	{
		if (m == Month::dec) m = Month::jan;
		else m = static_cast<Month>(static_cast<int>(m) + n);
	}

	//------------------------------------------------------------------------------

	void Date::add_year(int n)
	{
		if (m==feb && d==29 && !leapyear(y+n)) { // beware of leap years!
			m = mar;        // use March 1 instead of February 29
			d = 1;
		}
		y+=n;
	}

	//------------------------------------------------------------------------------

	// helper functions:

	bool is_date(int y, Date::Month  m, int d)
	{
		// assume that y is valid

		if (d<=0) return false;            // d must be positive

		int days_in_month = 31;            // most months have 31 days

		switch (m) {
			case Date::feb:                        // the length of February varies
				days_in_month = (leapyear(y))?29:28;
				break;
			case Date::apr: case Date::jun: case Date::sep: case Date::nov:
				days_in_month = 30;                // the rest have 30 days
				break;
		}

		if (days_in_month<d) return false;

		return true;
	} 

	//------------------------------------------------------------------------------

	bool leapyear(int y)
	{
		if (y % 4 ==0) return true;
		if (y % 100 ==0 && y%400) return true;
		return false;
	}

	//------------------------------------------------------------------------------

	bool operator==(const Date& a, const Date& b)
	{
		return a.year()==b.year()
			&& a.month()==b.month()
			&& a.day()==b.day();
	}

	//------------------------------------------------------------------------------

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a==b);
	}

	//------------------------------------------------------------------------------

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day() 
			<< ')';
	}

	//------------------------------------------------------------------------------

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
			is.clear(ios_base::failbit);                    // set the fail bit
			return is;
		}
		dd = Date(y,Date::Month(m),d);     // update dd
		return is;
	}

	//------------------------------------------------------------------------------

	enum Day {
		sunday=0, monday, tuesday, wednesday, thursday, friday, saturday
	};

	//------------------------------------------------------------------------------
	// days from Wednesday 1800 Jan 1
	int total_days(const Date& d)
	{
		int years = d.year()-1800;
		int leapyears = years / 4 - years/100 - years/400;
		int months = static_cast<int>(d.month()) + 1;
		int days = d.day();

		int months_days;
		for (int i=0; i < months; i++) {
			months_days += days_in_month(d.year(),static_cast<Date::Month>(i));
		}


		int result = leapyears + years + months_days + days;
		cout << leapyears << '\t'<< years*365 << '\t' << months_days << '\t'<< days << '\n';

		if (leapyear(d.year()) && months >= 2) result += 1;

		return result;
	}


	Day day_of_week(const Date& d)
	{
		// 1800 Jan 1 was a Wednesday! -1 because the enumerator is 0 based,
		// +2 because of the first was a Wednesday
		int day = total_days(d) %7 +3;

		cout << "day of week: " << day << '\t' << static_cast<int>(static_cast<Day>(day)) << '\n';

		if (day < 7) {return static_cast<Day>(day);}
		return static_cast<Day>(day-7);
	}

	//------------------------------------------------------------------------------

	Date next_Sunday(const Date& d)
	{
		Date date = d;
		while (true) {
			cout << "current date: " << date << '\n';
			date.add_day(1);
			if (day_of_week(date) == Day::sunday) return date;
		}
	}

	//------------------------------------------------------------------------------

	Date next_weekday(const Date& d)
	{
		Date date = d;
		while (true) {
			date.add_day(1);
			if (date.day() == Day::saturday || date.day() == Day::sunday) continue; 
			return date;
		}
	}

	//------------------------------------------------------------------------------

} // Chrono

//------------------------------------------------------------------------------

int main()
try
{
    Chrono::Date tuesday(1978, Chrono::Date::jul, 4); // initialization
    Chrono::Date sunday = Chrono::next_Sunday(tuesday);
    Chrono::Day  tue = day_of_week(tuesday);
    Chrono::Day  sun = day_of_week(sunday);
    cout << '\n' << "Date is " << tuesday << " Sunday will be on the " << sunday << endl;
    return tuesday != sunday;
}
catch (Chrono::Date::Invalid&) {
    cerr << "error: Invalid date\n"; 
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n"; 
    return 2;
}

//------------------------------------------------------------------------------
