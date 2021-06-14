#include "../std_lib_facilities.h"

/* 
*/

char* strdup(char* s)
{

	int length = 0;

	char* ps = s;

	while (*ps) {
		length++;
		ps++;
	}

	ps-=length;			// Bring pointer back to start

	char* dup = new char[length];
	char* pdup = dup;

	while (*ps) {
		*pdup = *ps;
		++ps;
		++pdup;
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
