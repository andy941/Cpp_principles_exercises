#include "../std_lib_facilities.h"
#include "ex3_StringCompare.cpp"

int len(const char* s)
{
	int length {0};
	while (s[length]) {length++;}
	return length;
}

istream& read_word(istream& is, char* buffer, int max)  // read at most max–1 characters from is into buffer
{
	is.width(max);
	is >> buffer;
	return is;
}

int is_palindrome(char* str) 
{
	int length = len(str);
	char* str2 = new char[length];

	for(int i = 0; i<length; i++) {
		str2[i] = str[length - 1 - i]; 
	}
	str2[length] = 0; //end cstring style with '\0'

	int result = strcmp(str,str2);

	delete[] str2;
	return result;

}

int main() 
{
	constexpr int max = 128;
	int res {0};

	cout << "Insert a word: ";

for (char arr[max]; read_word(cin, arr, max);) {
		res = is_palindrome(arr);
		cout << arr << " is ";
		if (res!=0) cout << "not ";
		cout << "a palindrome." << '\n';
		cout << "Insert a word: ";
	}

	return 0;
}

