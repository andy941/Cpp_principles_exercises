//#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include<regex>
using namespace std;

// I have to account for each case separately, I will do 2 of the easiest
// If the literal Month binfing is needed would be sufficient to do an enumerator class
// and bind i.e. (A|a)pr(il)? -> enum class { apr : 4 }

bool case1 (string line, string& newline)
{
	regex pat {R"((\d{4})(\s|\\|-|\.)(\d{2})(\s|\\|-|\.)(\d{2}))"};
	smatch matches;
	if (regex_search(line, matches, pat)) {
		ostringstream oss;
		oss << matches[1] << '-' <<
			matches[3] << '-' <<
			matches[5];
		regex_replace(back_inserter(newline), line.begin(), line.end(), pat, oss.str());
		return true;
	}
	return false;
}

bool case2 (string line, string& newline)
{
	regex pat {R"((\d{2})(\s|\\|-|\.)(\d{2})(\s|\\|-|\.)(\d{4}))"};
	smatch matches;
	if (regex_search(line, matches, pat)) {
		ostringstream oss;
		oss << matches[5] << '-' <<
			matches[3] << '-' <<
			matches[1];
		cout << oss.str() << endl;
		regex_replace(back_inserter(newline), line.begin(), line.end(), pat, oss.str());
		return true;
	}
	return false;
}

int main() 
{
	ifstream in {"Dates.txt"};                                         // input file
	if (!in) cerr << "no file\n";

	int lineno = 0;
	for (string line; getline(in,line); ) {     // read input line into input buffer
		++lineno;
		smatch matches;                         // matched strings go here
		string newline = "";

		if (case1(line, newline))		cout << "NEW: " << newline << endl;
		else if (case2(line, newline))	cout << "NEW: " << newline << endl;
		else							cout << line << endl;
	}
}

