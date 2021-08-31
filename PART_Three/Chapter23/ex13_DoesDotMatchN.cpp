//#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include<regex>
using namespace std;

int main() 
{
	string s = "ggg\nddd";
	regex pat {R"(ggg.ddd)"};           // postal code pattern
	smatch matches;

	cout << s << endl;
	if (!regex_search(s, matches, pat)) cout << "Pattern . not found" << endl;
	else for (auto& x : matches) {
		cout << "Pattern found" << endl;
		cout << x << endl;
	}
}
