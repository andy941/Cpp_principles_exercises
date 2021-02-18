#include "../std_lib_facilities.h"
#include "RomanInt.h"

// Helper functions to parse romans and calculate corresponding integer
int Level (char r)
{
	static vector<char> levels {'I','V','X','L','C','D','M'};

	for (int i = 0; i < levels.size(); i++) {
		if (levels[i] == r) return i;
	}

	error("Error Not a Roman number!\n");
}

int Letter_to_int (char r)
{
	class NonRoman{};

	switch (r) {
		case 'I': 
			return 1;
		case 'V': 
			return 5;
		case 'X': 
			return 10;
		case 'L': 
			return 50;
		case 'C': 
			return 100;
		case 'D': 
			return 500;
		case 'M': 
			return 1000;
		default: 
			throw NonRoman{};
	}
}

int Roman_to_int (string roman)
{
	int result = 0;
	int buffer = 0;

	for (int i = 0; i < roman.size(); i++) {

		// When at the end evaluate the last letter and check if 
		// the buffer is empty or not
		if (i == roman.size() -1) {
			if (buffer == 0) return result += Letter_to_int(roman[i]);
			return result += Letter_to_int(roman[i]) - buffer;
		}

		if (Level(roman[i]) < Level(roman[i+1])) {
			buffer += Letter_to_int(roman[i]);
			continue;
		}

		result += Letter_to_int(roman[i]) - buffer;
		buffer = 0;
	}
}

Roman::Roman(string r)
	:roman(r), value(Roman_to_int(r))
{
};

ostream& operator<<(ostream& os, Roman& r)
{
	os << r.as_roman();
	return os;
};

istream& operator>>(istream& is, Roman& r)
{
	string roman_number;
	is >> roman_number;

	r = Roman{roman_number};
	
	return is;
};

// FOR DEBUG PURPOSES
//int main ()
//{
//	Roman rome;
//	cout << "TRIAL " << Roman_to_int("MCMXII") << '\n';
//	cout << "insert a roman : ";
//	cin >> rome;
//
//	cout << '\n' << rome << "   " << rome.as_int() << '\n';
//
//
//	return 0;
//}

