#include "../std_lib_facilities.h"

/* 
 * I we try using a CString without a termination char '\0' the 
 * loops will not stop and we'll start pointing some random place in 
 * memory. Here below are all the rewritten functions that work
 * with non terminated set of characters.
 *
 * N.B.: cout << is not gonna print properly char arrays because there is no
 * end, it will print one more char. is not important in this case but things
 * will print weird.
*/

char* strdup(char* s, int n)
{

	char* ps = s;

	char* dup = new char[n];
	char* pdup = dup;

	while (--n) {
		*pdup = *ps;
		++ps;
		++pdup;
	}

	return dup;
}

char* findx(const char* str,  const char* sub, int n1, int n2)
{
	if (!sub) return nullptr;			// Check if null substring

	const char* s = str;
	const char* x = sub;
	int m = n2;

	while (--n1) {
		cout << *s << endl;

		if (*s == *x) {
			cout << "Match: " << *s << ' ' << *x << endl;

			for (const char* temp = s; m--; ++temp) {							
				cout << "Check: " << *temp << ' ' << *x << endl;

				if (!*temp) return nullptr;
				if (*temp != *x) break;
				if (m==0) return strdup(sub);

				++x;
			}
		}
		s++;
		x = sub;
		m = n2;
		
	}
	return nullptr;
}

int strcmp(const char* str1, const char* str2, int n1, int n2)
{
	const char* s1 = str1;
	const char* s2 = str2;
	int result = 0;

	while (1) {
		result += *s1-*s2;
		if (result != 0) return result/abs(result);
		--n1;
		--n2;
		if (!n1 || !n2) break;
		++s1;
		++s2;
	}

	if (n1 == 0 && n2 == 0) return 0;
	if (n1 == 0) return +1;
	if (n2 == 0) return -1;

	error("something went wrong");
	return 1;
}

int main() 
{
	// Strdup test
	cout << "\n___STRDUP TEST___" << endl;
	char str[] {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};

	char* cstring2 = strdup(str, 12);

	cout << str << '\n' << cstring2 << '\n';
	delete cstring2;

	// Findx test
	cout << "\n___FINDX TEST___" << endl;

	char str2[] {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
	char x1[] {'o', 'r', 'l'};
	char x2[] {'e', 'l', 'l', 'o', ' ', 'w'};
	char x3[] {'H', 'e', 'l', 'l', 'o', ' ', 'W'};

	char* res1 = findx(str2, x1, 12, 3);
	char* res2 = findx(str2, x2, 12, 6);
	char* res3 = findx(str2, x3, 12, 7);

	if (!res1) cout << "1 NotFound\n";
	if (res1) cout << "1 Result: " << res1 << '\n';
	if (!res2) cout << "2 NotFound\n";
	if (res2) cout << "2 Result: " << res2 << '\n';
	if (!res3) cout << "3 NotFound\n";
	if (res3) cout << "3 Result: " << res3 << '\n';

	delete[] res1;
	delete[] res2;
	delete[] res3;

	// Strcmp test
	cout << "\n___STRCMP TEST___" << endl;
	char carr1[] {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
	char carr2[] {'H', 'e', 'l', 'l', 'a', 'W', 'o', 'r', 'l', 'd', '!'};
	char carr3[] {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
	char carr4[] {'H', 'e', 'l', 'l', 'z', ' ', 'W', 'o', 'r', 'l', 'd', 'z', '!'};
	char carr5[] {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '!'};

	cout <<  carr2 << ' ' << strcmp(carr1, carr2, 12, 11) << endl;
	cout <<  carr3 << ' ' << strcmp(carr1, carr3, 12, 12) << endl;
	cout <<  carr4 << ' ' << strcmp(carr1, carr4, 12, 13) << endl;
	cout <<  carr5 << ' ' << strcmp(carr1, carr5, 12, 13) << endl;

	return 0;
}






