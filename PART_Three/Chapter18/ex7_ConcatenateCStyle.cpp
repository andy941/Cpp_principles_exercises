
#include "../std_lib_facilities.h"

int len(const char* s)
{
	int length {0};
	while (s[++length]) {}
	return length;
}

char* cat_dot(const char* s1, const char* s2, const char* sep) 
{
	int length {0};
	length = len(s1) + len(s2) + len(sep);
	const char* str1 = s1;
	const char* s = sep;
	const char* str2 = s2;

	char* result = new char[length];
	for (int i = 0; i<len(s1); i++) {
		result[i] = *str1++; 
	}
	for (int i = len(s1); i<len(s1)+len(sep); i++) {
		result[i] = *s++; 
	}
	for (int i = len(s1)+len(sep); i<length; i++) {
		result[i] = *str2++; 
	}

	return result;
}

int main() 
{
	char s1[] {"My name is"};
	char s2[] {" Andrea"};
	char sep[] {":"};

	char* arr = cat_dot(s1, s2, sep);
	cout << '\n' << arr << '\n';

	delete[] arr;

	return 0;
}

