#include "../std_lib_facilities.h"
#include "ex1_StringDuplicator2.cpp"

/* 
 * Return +1 if s1>s2, return -1 if s1<s2 and 0 if they are the same.
 * in case one string is the substring of the other the shorter gets 
 * the higher lexycographical rank.
*/

int strcmp(const char* str1, const char* str2)
{
	const char* s1 = str1;
	const char* s2 = str2;
	int result = 0;

	while (*s1 && *s2) {
		result += *s1-*s2;
		if (result != 0) return result/abs(result);
		++s1;
		++s2;
	}
	if (!*s1 && !*s2) return 0;
	if (!*s1) return +1;
	if (!*s2) return -1;
}

//int main() 
//{
//	char str1[] {"Hello World!"};
//	char str2[] {"HellaWorld!"};
//	char str3[] {"Hello World!"};
//	char str4[] {"Hellz Worldz!"};
//	char str5[] {"Hello World!!"};
//
//	cout << str1 << ' ' << str2 << ' ' << strcmp(str1, str2) << endl;
//	cout << str1 << ' ' << str3 << ' ' << strcmp(str1, str3) << endl;
//	cout << str1 << ' ' << str4 << ' ' << strcmp(str1, str4) << endl;
//	cout << str1 << ' ' << str5 << ' ' << strcmp(str1, str5) << endl;
//}






