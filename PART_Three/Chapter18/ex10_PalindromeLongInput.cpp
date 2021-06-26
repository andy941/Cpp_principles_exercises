
#include "../std_lib_facilities.h"
#include "ex3_StringCompare.cpp"

/*
 * The aim of this exercise is to improve the read_word() function
 * so that arbitrarly long words can be read into the array.
 *
 * Because the problem resides only with words that don't fit the buffer
 * (length >= max), one naive solution would be to check the last possible character
 * of the allocated cstring array. If it's a character most likely the word isn't 
 * finished and we should allocate more space and continue reading from input.
 */

int len(const char* s)
{
	int length {0};
	while (s[length]) {length++;}
	return length;
}

//------------------------------------------------------------------------

char* read_word(istream& is, int max) 
{
	int size = max;
	char* str = new char[size+1]; 
	char* tmp = nullptr; 

	while (true) {

		for (int i = size-max; i < size; i++) {
			cin.get(str[i]);
			if (isspace(str[i])) { 
				str[i] = 0;
				return str;
			}
		}

		// Overflowing! allocate more space

		size += max;

		tmp=strdup(str);
		delete[] str;

		str = new char[size];

		for (int i = 0; i < size; i++) {
			str[i] = tmp[i];
		}

		delete[] tmp;
		tmp = nullptr;
	}
}

//------------------------------------------------------------------------

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
	constexpr int max = 4;
	int res {0};
	char* arr = nullptr;

	cout << "Insert a word: ";

	while (char* arr = read_word(cin, max)) {

		cout << "Inserted --> " << arr  << ' ' << len(arr) << '\n';

		res = is_palindrome(arr);
		cout << arr << " is ";
		if (res!=0) cout << "not ";
		cout << "a palindrome." << '\n';

		cout << "Insert a word: ";
	}

	return 0;
}

