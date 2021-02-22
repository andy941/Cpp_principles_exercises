#include "../std_lib_facilities.h"

int Countwords(string tocount)
{
	istringstream is {tocount};

	int count = 0;
	string s;
	while (is >> s) {
		count += 1;
	}

	return count;
}
int main()
{
	string file;

	cout << "Please insert the name of the file to transform to lowercase\n";
	cin >> file;

	ifstream ifs {file};
	if (!ifs) error("Sorry can't open the file", file);

	int line, words;

	for (string str; getline(ifs,str);) {
		line += 1;
		words = Countwords(str);

		cout << line << '\t' << words << '\n';
	}


	return 0;
}


