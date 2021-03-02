
#include "../std_lib_facilities.h"

string Reverse(const string& str) 
{
	vector<string> words;
	string result;

	ostringstream oss {result};
	istringstream iss {str};

	for (string s; iss >> s;) words.push_back(s);

	for (int i = 0; i < words.size(); i++) {
		oss << words[words.size() - i - 1] << ' ';
	}
	 return oss.str();
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

