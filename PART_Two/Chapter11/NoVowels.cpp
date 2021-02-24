#include "../std_lib_facilities.h"

int main()
{
	string file;

	cout << "Please insert the name of the file to transform to lowercase\n";
	cin >> file;

	ifstream ifs {file};
	if (!ifs) error("Sorry can't open the file", file);

	for (char ch; ifs.get(ch);) {
		switch (ch) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U':
			continue;
		default: cout << ch;
		}
	}

	return 0;
}


