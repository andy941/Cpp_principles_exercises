#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include "../std_lib_facilities.h"
using namespace std;

int main() 
{
	int sum = 0;
	int n;

	ifstream ifs {"mydata.txt"};

	while (ifs >> n) {
		sum += n;
	}

	cout << "Result : " << sum << endl;

	return 0;
}
