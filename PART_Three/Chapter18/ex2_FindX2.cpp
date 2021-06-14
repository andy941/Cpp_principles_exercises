#include "../std_lib_facilities.h"
#include "ex1_StringDuplicator2.cpp"

/* 
*/

char* findx(const char* str,  const char* sub)
{
	if (!sub) return nullptr;			// Check if null substring

	const char* s = str;
	const char* x = sub;

// If first letter coincides start looping to see if the substring is found completely
	while (*s) {
		cout << *s << endl;
		if (*s == *x) {
			cout << "Match: " << *s << ' ' << *x << endl;
			for (const char* temp = s; temp; temp++) {							
				cout << "Check: " << *temp << ' ' << *x << endl;
				if (!*x) {
					return strdup(sub);
				}
				if (!*temp) {
					return nullptr;
				}
				if (*temp != *x) break;
				++x;
			}
		}
		x = sub;
		++s;
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





