
#include "../std_lib_facilities.h"

// Keyboard chars are from 33 to 126 of ASCII table.

int main () 
{
	for (short int i = 33; i <= 126; i++) {
		cout << char(i) << '\t'
			<< dec << i << '\t' 
			<< hex << setfill('0') << setw(4)<< i << endl;
	}
}
