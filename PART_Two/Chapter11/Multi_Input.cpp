#include "../std_lib_facilities.h"

int main()
{

	int num;
	char ch, ch2;

	cout << "Please insert white spaced integers in octal, hexadecimal or decimal format\nEnd with ';'\n";
	cout << showbase;

	while (true) {
		cin >>  ch;

		if (ch == ';') break;

		if (ch == '0') {
			ch2 = cin.peek();
			cin.putback(ch);

			if (ch2 == 'x') {
				cin >> hex >> num;
				cout << hex << num << '\t' << setw(12) << "hexadecimal\t" << "converts to\t" << dec << num << "\tdecimal\n";
			}
			if (isspace(ch2) || isdigit(ch2)) {
				cin >> oct >> num;
				cout << oct << num << '\t' << setw(12) << "octal\t" << "converts to\t" << dec << num << "\tdecimal\n";
			}
		} 

		else {
			cin.putback(ch);

			cin >> dec >>num;
			cout << dec << num << '\t' << setw(12) << "decimal\t" << "converts to\t" << num << "\tdecimal\n";
		}
	}
	return 0;
}



