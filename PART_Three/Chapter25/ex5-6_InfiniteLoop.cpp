
#include "../std_lib_facilities.h"

int main () 
{
	// unsigned char max = 0xff;
	// for ( char i = 0; i < max; i++) {
	// 	cout << int(i) << endl;
	// }

	char a = 'a';

	while (!(a == 'b' & a == 'c')) 
	{	// evaluates always to true it's bitwise AND instead of logical AND
		cout << a << endl;
		a = rand()%128; //pick a different ascii char
	}
	
}
