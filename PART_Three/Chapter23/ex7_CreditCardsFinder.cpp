
//#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include<regex>
using namespace std;

/*
 * https://www.creditcardinsider.com/learn/anatomy-of-a-credit-card/
 */

int main() 
{
	ifstream in {"CreditCards.txt"};                                         // input file
	if (!in) cerr << "no file\n";

	regex pat {R"([3-6]\d{13,16})"};

	int lineno = 0;
	for (string line; getline(in,line); ) {     // read input line into input buffer
		++lineno;
		smatch matches;                         // matched strings go here
		if (regex_search(line, matches, pat))
			cout << lineno << ": " << line << '\n';
	}
}

