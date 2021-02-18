#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include "../std_lib_facilities.h"
using namespace std;

void Concatenate(string f1, string f2, string f3)
{
	ifstream file1 {f1};
	if (!file1) cerr << "Can't open " << f1 << '\n';
	ifstream file2 {f2};
	if (!file2) cerr << "Can't open " << f2 << '\n';
	ofstream file3 {f3};
	if (!file3) cerr << "Can't open " << f3 << '\n';

	char buffer;
	while (true)
	{
		buffer = file1.get();
		if (file1.eof()) break;
		file3 << buffer;
	}
	while (true)
	{
		buffer = file2.get();
		if (file2.eof()) break;
		file3 << buffer;
	}
}

int main() 
{
	string file1, file2,file3;
	cout << "Insert the names of the 2 files you want to concatenate\n";
	cin >> file1 >> file2;
	cout << "Insert the name of the output file\n";
	cin >> file3;

	Concatenate(file1,file2,file3);

	return 0;
}
