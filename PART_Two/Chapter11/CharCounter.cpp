#include "../std_lib_facilities.h"

struct table 
{
	vector<int> values {0,0,0,0,0,0};
	vector<string> types {"Digit", "Letter","AlphaNumeric", "Punctuation", "Uppercase", "Lowercase"};
	table() {}; 

	void add(char);
};

void table::add(char ch)
{
		if (isdigit(ch)) values[0] += 1;
		if (isalpha(ch)) values[1] += 1;
		if (isalnum(ch)) values[2] += 1;
		if (ispunct(ch)) values[3] += 1;
		if (isupper(ch)) values[4] += 1;
		if (islower(ch)) values[5] += 1;

		return;
}

ostream& operator<<(ostream& os, const table& tb)
{
	for (int i = 0; i < tb.values.size(); i++) {
		os << tb.types[i] << '\t' << tb.values[i] << '\n';
	}

	return os;
}

int main()
{
	table tab;

	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open input file ",iname);
	
	for (char ch; ifs.get(ch);) {

		ifs.get(ch);

		if (isspace(ch)) continue;

		tab.add(ch);
	}

	cout << '\n' << "Results: " << '\n' << '\n' << tab;
	return 0;
}



