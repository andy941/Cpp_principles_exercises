#include "../std_lib_facilities.h"

int main()
{

	char ch;

	cout << "Insert a phrase or a single word to see the type of each character\n"
		<< "End with '\' \n";

	while (true) {

		cin.get(ch);

		if (isspace(ch)) { cout << "\n"; continue;}

		cout << ch;
		if (isdigit(ch)) cout << "\tDigit";
		if (isalpha(ch)) cout << "\tLetter";
		if (isalnum(ch)) cout << "\tAlphanumeric";
		if (ispunct(ch)) cout << "\tPunctuation";
		if (isupper(ch)) cout << "\tUpperCase";
		if (islower(ch)) cout << "\tLowerCase";

		if (ch == '\\') {cout << "\tEND CHARACTER\n"; break;}



		cout << endl;
	}
	return 0;
}




