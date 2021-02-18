#include "../std_lib_facilities.h"

class Roman
{
	string roman;
	int value;

	public:
	Roman () {};
	Roman(string);
	int as_int() const {return value;}
	string as_roman() const {return roman;}
};

// Helper functions to parse romans and calculate corresponding integer
int Level (char);

int Letter_to_int (char);

int Roman_to_int (string);

ostream& operator<<(ostream&, Roman&);

istream& operator>>(istream&, Roman&);
