#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

//______________________________________________________________________________________________________
// Date class implementation

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

	int year() const {return y;}
	Month month() const {return m;}
	int day() const {return d;}

	void add_day(int n);
};


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

bool leapyear(int y) 
{
	if (y % 4 ==0) return true;
	else return false;
}

ostream& operator<<(ostream& os, Date& date)
{
	os << date.year() << '-' << int(date.month()) << '-' << date.day();
	return os;
}



//______________________________________________________________________________________________________
// Implement the book class (from ex05 on)

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
	GENRE genre {GENRE::bibliography};
	Date cr_date;
	bool check {true};

	public:
	// Class constructor
	Book();
	Book(ISBN i, string t, string a, GENRE g, Date d, bool c);

	// Return values
	string Isbn() const {return isbn;}
	string Title() const {return title;}
	string Author() const {return author;}
	GENRE Genre() const {return genre;}
	Date Cr_date() const {return cr_date;}
	bool Check() const {return check;}

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

// Operator overloads
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

//______________________________________________________________________________________________________
// Implement the Patron class (ex08)

class Patron 
{
	string name;
	int card;
	double fees;

	public:
	Patron();
	Patron(string, int, double);

	string Name() const {return name;}
	int Card() const {return card;}
	double Fees() const {return fees;}
};

Patron::Patron(string n, int c, double f) 
{
	name = n;
	card = c;
	fees = f;
}

// Helper function to check if the user owes fees
bool Debt(Patron& patron) 
{
	if (patron.Fees() == 0) return false;
	else return true;
}

bool operator==(Patron& a, Patron& b) 
{
	return a.Name() == b.Name();
}

bool operator!=(Patron& a, Patron& b) 
{
	return a.Name() != b.Name();
}

//______________________________________________________________________________________________________
// Implement the Library class (ex08)
struct Transaction 
{
	Book book;
	Patron patron;
	Date date;

	Transaction() {};
	Transaction(Book b, Patron p, Date d) :book{b}, patron{p}, date{d} {};
};

class Library 
{
	vector<Transaction> trans;
	vector<Patron> patrons;
	vector<Book> books;

	public:
	Library() {};
	Library(vector<Transaction>, vector<Patron>, vector<Book>);
	void AddBook(Book b) {books.push_back(b);}
	void AddPatron(Patron p) {patrons.push_back(p);}
	void AddTrans(Transaction t) {trans.push_back(t);}

	vector<Transaction> Transactions() const {return trans;}
	vector<Patron> Patrons() const {return patrons;}
	vector<Book> Books() const {return books;}

	class checkout_error {};
	void CheckOut(Book, Patron, Date);
	vector<string> OwingFees();

};

Library::Library(vector<Transaction> t, vector<Patron> p, vector<Book> b)
{
	trans = t;
	patrons = p;
	books = b;
};

void Library::CheckOut(Book b, Patron p, Date d)
{
	bool check_b {false};
	bool check_p {false};

	for (Book x : books) {if (b == x) check_b = true;}
	for (Patron x : patrons) {if (p == x) check_p = true;}

	if (check_b && check_p) {
		if (!Debt(p)) {
			AddTrans(Transaction(b, p, d));
		} else throw checkout_error {};
	} else throw checkout_error {};

};

vector<string> Library::OwingFees() 
{
	vector<string> users {};

	for (Patron x : patrons) {if (Debt(x)) users.push_back(x.Name());}

	return users;
};

//______________________________________________________________________________________________________
// Main() function, check code frequently for runtime errors
int main () 
{

	try {

		Date d {2000, Month::dec, 23};

		Book book {ISBN {"3-3-3-a"}, "author", "title", GENRE::bibliography, d, true}; 
		Book book2 {ISBN {"3-3-3-b"}, "author2", "title2", GENRE::fiction, Date {2000, Month::jan, 27}, false}; 

		//bool compare = book != book2;
		//cout << book << '\n' << "Compare = " << compare << "\n\n" << book2;

		Patron patron ("Andrea", 12345, 1);
		Patron patron2 ("Pietro", 125, 0);

		//if (Debt(patron)) cout << "TRUE" << '\n';
		//else cout << "FALSE" << '\n';

		Library lib;

		lib.AddBook(book);
		lib.AddBook(book2);
		lib.AddPatron(patron);
		lib.AddPatron(patron2);

		vector<string> owing = lib.OwingFees();

		//for (string x : owing) {cout << x << '\n';}
		//for (Book x : lib.Books()) {cout << x << '\n';}

		lib.CheckOut(book, patron2, d);
		vector<Transaction> t = lib.Transactions();
		cout <<  t[0].book.Title() << '\t' << t[0].patron.Name() << '\n';

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

	catch (Library::checkout_error) {
		cerr << "Checkout error\n";
		return 1;
	}

	catch (...) {
		cerr << "Unknown exception...";
		return 2;
	}
}
