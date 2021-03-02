
#include "../std_lib_facilities.h"

string Reverse(const string& str) 
{
	string result;

	for (int i = 0; i < str.size(); i++) {
		result.push_back(str[str.size() - i - 1]);
	}
	 return result;
}
int main () 
{ 
	vector<string> lines;

	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open input file ",iname);

	for (string line; getline(ifs,line);) lines.push_back(line);

	for (int i = 0; i < lines.size(); i++) {
		cout << Reverse(lines[lines.size() - i - 1]) << '\n';
	}

	return 0;
}
