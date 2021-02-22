#include "../std_lib_facilities.h"

int main()
{
	string file;

	cout << "Please insert the name of the file to transform to lowercase\n";
	cin >> file;

	ifstream ifs {file};
	if (!ifs) error("Sorry can't open the file", file);

	ofstream ofs {"Lowercase_" + file};

	for (char c; ifs.get(c);) {
		char ch = tolower(c);
		cout << ch;
		ofs << ch;
	}

	return 0;
}

