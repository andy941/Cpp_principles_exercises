#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Year 
{                                                         // year in [min:max) range
	static const int min = 1800;
	static const int max = 2200;
	int y;

	public:
	class Invalid { };
	Year(int x) : y{x} { if (x<min || max<=x) throw Invalid{}; }
	int year() { return y; }
};

class Date 
{
	int y;       // year
	Month m;     // month in year
	int d;      // day of month

	public:
	Date() : y{2000}, m{Month::jan}, d{1} {}
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

ostream& operator<<(ostream& os, Date& date)
{
	os << date.year() << '-' << int(date.month()) << '-' << date.day();
	return os;
}



// Implement the book class

// Helper function to check isbn code
bool check_isbn(string code) 
{
	int counter = 0;

	for (int i = 0; i < code.size(); i++) {

		if (counter == 3) {
			if ((isdigit(code[i]) || isalpha(code[i])) && i==code.size()-1) return true;
			else return false;
		}

		if (code[i] == '-') {counter +=1; continue;}

		if (!isdigit(code[i])) {return false;}
	}

	cerr << "Weird ISBN ...\n";
	return false;
}

class ISBN 
{
	string code;

	public:
	string name() {return code;}
	class Invalid_ISBN {};
	ISBN(string x) : code{x} {if (!check_isbn(code)) throw Invalid_ISBN{}; return;}
};

enum class GENRE {fiction = 0, nonfiction, periodical, bibliography, children};
 


class Book 
{
	string isbn;
	string title;
	string author;
	GENRE genre;
	Date cr_date;
	bool check;

	public:
	// Class constructor
	Book(ISBN i, string t, string a, GENRE g, Date d, bool c);

	// Return values
	string Isbn() {return isbn;}
	string Title() {return title;}
	string Author() {return author;}
	GENRE Genre() {return genre;}
	Date Cr_date() {return cr_date;}
	bool Check() {return check;}

	// Functions to operate on class variables
	void check_in(bool val) {check = val;};
};

Book::Book(ISBN i, string t, string a, GENRE g, Date d, bool c)
{
	isbn = i.name(); 
	title = t;
	author = a;
	genre = g;
	cr_date = d;
	check = c;
}

ostream& operator<<(ostream& os, Book& b)
{
	Date d {b.Cr_date()};
	os << b.Isbn() << '\n' <<
		b.Title() << '\n' <<
		b.Author() << '\n' <<
		int(b.Genre()) << '\n' <<
		d << '\n' <<
		b.Check() << '\n';

	return os;
}

bool operator==(Book& a, Book& b) 
{
	return a.Isbn() == b.Isbn();
}

bool operator!=(Book& a, Book& b) 
{
	return a.Isbn() != b.Isbn();
}

int main () 
{

	try {

		Date d {2000, Month::dec, 23};

		Book book {ISBN {"3-3-3-a"}, "author", "title", GENRE::bibliography, d, true}; 
		Book book2 {ISBN {"3-3-3-b"}, "author2", "title2", GENRE::fiction, Date {2000, Month::jan, 27}, false}; 

		bool compare = book != book2;
		cout << book << '\n' << "Compare = " << compare << "\n\n" << book2;

		return 0;
	} 

	catch (ISBN::Invalid_ISBN) {
		cerr << "Invalid ISBN\n";
		return 1;
	}

	catch (Year::Invalid) {
		cerr << "Invalid Year\n";
		return 1;
	}

	catch (...) {
		cerr << "Unknown exception...";
		return 2;
	}
}
