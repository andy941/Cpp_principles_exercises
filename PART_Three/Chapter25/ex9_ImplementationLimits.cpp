#include "../std_lib_facilities.h"

// Keyboard chars are from 33 to 126 of ASCII table.

int main () 
{
	cout << "Number of bits in an int = " << sizeof(int)*8 << endl;
	char c = -1;
	cout << int(c) << '\t' << bitset<sizeof(c)*8>(c) << endl;
	unsigned char uc = -1;
	cout << int(uc) << '\t' << bitset<sizeof(uc)*8>(c) << endl;

	
}
