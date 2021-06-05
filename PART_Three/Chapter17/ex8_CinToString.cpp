#include "../std_lib_facilities.h"

/*
*/

int main() 
{
	string str;  
	char c;

	for (int i = 0; cin.get(c); i++) {
		str.push_back(c);
		if (c == '!') { 
			cout << str << endl;
			return 0;
		}
	}
	return 1;
}





