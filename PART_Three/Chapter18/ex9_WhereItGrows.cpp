
#include "../std_lib_facilities.h"

/*
 * Compile with g++ -fpermissive to have pointer arithmetic for
 * pointers to fucntions.
*/

void fun1() {};
void fun2() {};

int main() 
{
	cout << "If the number is positive the  growth is decremental,"
		 " positive number indicates an incremental growth" << endl;

	constexpr static char s1 {'a'};
	constexpr static char s2 {'b'};
	cout << "Static Store: " << &s1 - &s2 << endl;

	cout << "Stack: " << fun1 - fun2 << endl;

	char* f1 = new char('a');
	char* f2 = new char('b');
	cout << "Free Store (2 chars): " << f1 - f2 << endl;

	char* a1 = new char[10];
	cout << "Free Store Array (first and fifth chars): " << &a1[0] - &a1[5] << endl;
}





