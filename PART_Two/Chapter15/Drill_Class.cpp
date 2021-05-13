
#include "../std_lib_facilities.h"


bool find( string& s, string& c )
{
	for ( char x : s ) {
		for ( char y : c ) {
			if (x == y) return true;
		}
	}
	return false;
}

struct Person 
{
	string invalids {"'[]*&^%$#@"};

	Person() { };
	Person(string n, int a) : name{n}, age{a} 
	{ 
		if ( a < 0 || a > 150 ) error("Age is bonkers\n");
		if ( find(invalids, name) ) error("Name is bonkers\n");
	};

	string show_name() const { return name; }
	int show_age() const { return age; }
	void set_name(string n) { name = n; }
	void set_age(int a) { age = a; }

	private:
	string name;
	int age;
};


ostream& operator<<(ostream& os, Person& p)
{
	os << p.show_name() << " " << p.show_age();
	return os;
}

istream& operator>>(istream& is, Person& p)
{
	string n;
	int a;

	is >> n >> a;
	p.set_name(n);
	p.set_age(a);

	return is;
}

int main()
{
	Person p { "Goofy", 62 };

	cout << "insert name and age please" << '\n';
	cin >> p;
	cout << p << '\n';
}
	Person p { "&Goofy", 62 };


