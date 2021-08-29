//#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

int main()
{
	regex pattern;

	string pat;
	cout << "enter pattern: ";
	getline(cin,pat);            // read pattern

	try {
		pattern = pat;      // this checks pat
		cout << "pattern: " << pat << '\n';
	}
	catch (regex_error re) {
		cout << pat << " is not a valid regular expression\n";
		exit(1);
	}

	cout << "now enter a file name:\n";
	string file;
	cin >> file;
	ifstream ifs { file };

	int lineno = 0;
	for (string line; getline(ifs,line); ) {
		++lineno;
		smatch matches;
		if (regex_search(line, matches, pattern)) {
			cout << "line " << lineno << ": " << line << '\n';
			for (int i = 0; i<matches.size(); ++i)
				cout << "\tmatches[" << i << "]: "
					<<  matches[i] << '\n';
		}
	}
}
