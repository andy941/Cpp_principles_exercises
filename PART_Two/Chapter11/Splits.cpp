
// This is basically the solution to exercise 10 and 11

#include "../std_lib_facilities.h"

bool isin (const string& spaces, char ch)
{
	for (char x : spaces) {
		if (x==ch) return true; 
	}
	return false;
}

vector<string> split(string& str, const string& spaces) 
{
	vector<string> result;
	string sub_string;

	for (char& x : str) {
		if (isin(spaces,x)) x = ' ';
	}

	istringstream iss {str};

	for (char x; iss.get(x);) {

		if (isspace(x) || isin(spaces,x)) continue;

		iss.unget();
		iss >> sub_string;


		result.push_back(sub_string);
	}
	
	return result;
}

int main ()
{
	vector<string> substrings;
	string str, spaces;

	cout << "Insert a phrase:\n";
	getline(cin,str);
	cout << "Insert a spaces:\n";
	getline(cin,spaces);

	substrings = split(str, spaces);
	for (string x : substrings) cout << x << '\n';

	return 0;
}
