#include "../std_lib_facilities.h"

/*
 * comparing the addresses, the stack grows upwards.
 * the address of b is 32 values higher than a.
 * a - b = -32
*/

int main() 
{
	char* a = new char('a');
	char* b = new char('b');
	cout << a -b << endl;
}





