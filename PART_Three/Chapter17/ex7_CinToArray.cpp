#include "../std_lib_facilities.h"

/*
 * I am not sure how to properly do this, the array is gonna overflow eventually
 * if it's not costrained. I guess you could copy the 100 chars 
 * array in a 200 array and continue reading from cin. not sure if it's the 
 * best way to do it though.
 * for this exercise I'll just define a 100 chars array.
*/

int main() 
{
	char* str = new char[100];  // 100 chars should be enough for now

	for (int i = 0; !str[i]; i++) {
		cin >> str[i];
		if (str[i] == '!') { 
			cout << str << endl;
			delete[] str;
			return 0;
		}
	}

	cerr << "100 chars limit reached"<< endl;
	delete[] str;
	return 1;
}




