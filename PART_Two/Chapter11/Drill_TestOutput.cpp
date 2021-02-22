#include "../std_lib_facilities.h"

int main()
{
	int age = 26;

	cout << showbase;
	cout << "Decimal" << '\t' << age << '\n' <<
		"Hex" << hex << '\t' << age << '\n' << 
		"Octal" << oct << '\t' << age << '\n';

	cout << age << setw(12) << string("\tAndrea\t") << int(1284202) << endl;
	cout << age << setw(10) << string("\tLuca\t") << int(12842399698) << endl;
	return 0;
}

