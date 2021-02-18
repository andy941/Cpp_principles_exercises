#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include "../std_lib_facilities.h"
using namespace std;

int main()
{
	string file {"text_with_integers.txt"};
	int num, sum;
	double non_int;

	ifstream ifs {file};
	if (!ifs) error("can't open file for reading\n");

	while (true)
	{
		ifs >> num;
		sum += num;

		if (ifs.fail()) {
			ifs.clear();
			for (char ch; ifs >> ch;) {
				if (isdigit(ch)) {ifs.unget(); break;}
			}

		}

		if (ifs.eof()) break;
	}

	cout << "Sum of all integers:  " << sum << endl;
	return 0;
}
