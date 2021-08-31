#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

int main()
{
	cout << "Enter a file name:\n";
	string file;
	cin >> file;
	ifstream ifs { file };
	if (!ifs) error("File not Found!");
	string file_s;
	for (char c; ifs.get(c); )  file_s.push_back(c);
	cout << file_s << endl;

	while (true) {
		regex pattern;

		string pat;
		cout << "enter pattern: ";
		cin >> pat;

		try {
			pattern = pat;      // this checks pat
			cout << "pattern: " << pat << '\n';
		}
		catch (regex_error re) {
			cout << pat << " is not a valid regular expression\n";
			continue;
		}

		cout << "--------------------------------------------------------------------" << endl;
		smatch matches;
		if (regex_search(file_s, matches, pattern)) {
			cout << '\t' << "Pattern found:" << endl;
			for (unsigned int i = 0; i < matches.size(); ++i)
				cout << '\t' << "matches[" << i << "]: "
					<<  matches[i] << '\n';
		} else cout << '\t' << "Pattern not found" << endl;
		cout << "--------------------------------------------------------------------" << endl;
	}
}
