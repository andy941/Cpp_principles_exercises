#include "../std_lib_facilities.h"

/* 
 * I think the right way is to get the length of the current array,
 * create a new one of the correct length and then copy every char.
*/

char* strdup(char* s)
{

	int length = 0;

	for (int i = 0; s[i]; i++) {
		length++;
	}

	char* dup = new char[length];

	for (int i = 0; i < length; i++) {
		dup[i] = s[i];
	}

	return dup;
}

//int main() 
//{
//	char cstring[] {"Hello World!"};
//
//	char* cstring2 = strdup(cstring);
//
//	cout << cstring << '\n' << cstring2 << '\n';
//	delete cstring2;
//}



