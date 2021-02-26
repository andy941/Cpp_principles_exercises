/*
 * 6. Write a program that replaces punctuation with whitespace. 
 *	  Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters.
 *	  Don’t modify characters within a pair of double quotes ("). 
 *	  For example, “- don't use the as-if rule.” becomes “ don t use the as if rule ”.
 *
 * 7. Modify the program from the previous exercise so that it 
 *    replaces don't with do not, can't with cannot, etc.; leaves 
 *    hyphens within words intact (so that we get “ do not use the as-if rule ”);
 *    and converts all characters to lower case.
 *
*/

#include "../std_lib_facilities.h"

string PunctToWhite(const string& str, bool& ignore)
{
	bool word;
	string result;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '"') {
			ignore = !ignore; 
			result.push_back(str[i]);
			continue;
		}
		if (ignore) {
			result.push_back(str[i]);
			continue;
		}

		if (str[i] == '-' && i != 0 && i != str.size()-1) {result.push_back(str[i]); continue;} 

		if (ispunct(str[i]) || str[i] == '-') {result.push_back(' '); continue;}

		result.push_back(str[i]);
	}
	
	return result;
}

int main()
{

	char ch;
	string line, word;
	bool quote {false};

	cout << "Insert a phrase to get rid of the punctuation\n"
		<< "use double quotes to keep punctutation \n"
		<< "End with '\' \n";

	while (true) {
		getline(cin,line);
		istringstream is {line};

		while (is.get(ch)) {
			if (isspace(ch)) {
				cout << ch;
				continue; 
			}

			is.unget();
			is >> word;
			cout << PunctToWhite(word, quote);
		}

		cout << '\n';

	}

	return 0;
}

