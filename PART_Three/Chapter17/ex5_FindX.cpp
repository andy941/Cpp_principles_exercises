#include "../std_lib_facilities.h"
#include "ex4_StringDuplicator.cpp"

/* 
 * Not very clear what should be returned here, I decided for nullptr if
 * the substring is not found and the substring itself if it is found.
*/
char* findx(const char* s,  const char* x)
{
	if (!x) return nullptr;							// Check if null substring

	for (int i = 0; s[i]; i++) {
		if (s[i] == x[0]) {
			cerr << "T\n";
			for (int j = 0; s[i+j]; j++) {			// If first letter coincides start looping to see
				cerr << j << ' ' << i << endl;		// if the substring is found completely
				if (!x[j]) {
					return strdup(x);
				}
				if (s[i+j] != x[j]) break;
			}
		}
	}

	return nullptr;
}

int main() 
{
	char str[] {"Hello World!"};
	char x1[] {"orl"};
	char x2[] {"ello w"};
	char x3[] {"Hello W"};

	char* res1 = findx(str, x1);
	char* res2 = findx(str, x2);
	char* res3 = findx(str, x3);

	if (!res1) cout << "1 NotFound\n";
	if (res1) cout << "1 Result: " << res1 << '\n';
	if (!res2) cout << "2 NotFound\n";
	if (res2) cout << "2 Result: " << res2 << '\n';
	if (!res3) cout << "3 NotFound\n";
	if (res3) cout << "3 Result: " << res3 << '\n';

	delete[] res1;
	delete[] res2;
	delete[] res3;
}




