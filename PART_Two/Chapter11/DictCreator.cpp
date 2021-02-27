/*
 * 8. Use the program from the previous exercise to make a dictionary 
 *    (as an alternative to the approach in §11.7). 
 *    Run the result on a multi-page text file, look at the result, and see 
 *    if you can improve the program to make a better dictionary.
 *    
*/

#include "../std_lib_facilities.h"

void CheckSpelling(string& str)
{
	if (str == "don't") {str = "do not";}
	if (str == "can't") {str = "can not";}
	if (str == "isn't") {str = "is not";}
	if (str == "wasn't") {str = "was not";}
	if (str == "weren't") {str = "were not";}
	if (str == "hasn't") {str = "has not";}
	if (str == "have't") {str = "have not";}
}

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
	string line, word, file;
	bool quote {false};
	vector<string> text;

	cout << "Insert the name of a file\n";

	cin >> file;
	ifstream ifs {file};
	if (!ifs) error("can't open file\n");

	while (getline(ifs,line)) {

		for (char& x : line) x = tolower(x);

		istringstream is {line};

		while (is.get(ch)) {
			if (isspace(ch)) {
				cout << ch;
				continue; 
			}

			is.unget();
			is >> word;

			// This is awful, you will always have two words as one string
			// maybe I should have done a input strem class like in the chapter ...
			CheckSpelling(word);

			text.push_back(PunctToWhite(word, quote));
		}

	}

	sort(text.begin(),text.end());

	for (string x : text) cout << x << '\n';

	return 0;
}

