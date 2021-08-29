
//#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include<regex>
using namespace std;

int main() 
{

	ifstream in {"Dates.txt"};                                         // input file
	if (!in) cerr << "no file\n";

	regex pat {R"(\d{2}(\d{2})?(\s|\\|-|\.)(\d{2}|\w{3}|\w{5})(\s|\\|-|\.)\d{2}(\d{2})?)"};

	int lineno = 0;
	for (string line; getline(in,line); ) {     // read input line into input buffer
		++lineno;
		smatch matches;                         // matched strings go here
		if (regex_search(line, matches, pat))
			cout << lineno << ": " << line << '\n';
	}
}

