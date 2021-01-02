// Things missing from Bjorn's solution:
// - initialize the vectors in an init() function that
//   will be called in  main(). is more clean and possibly
//   more robust? possible problems can arise with my crappy
//   way of coding that? only time will tell

#include<iostream>
#include <istream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>


std::vector<std::string> Noun = {"birds", "fish", "C++"};
std::vector<std::string> Conj = {"and", "or", "but"};
std::vector<std::string> Verb = {"rules", "fly", "swim"};
std::vector<std::string> Art = {"the"};

// handy function to print a vector
void printvec(std::vector<std::string> x) {
    for (std::string i : x) {
        std::cout << i << "\n";
    }
}

// check if a word is in a vector
bool is_in(std::string word, std::vector<std::string> x) {
	bool found = false;
	for (std::string i : x) {
		if (i == word) found = true;
	}
	return found;
}

//--------------------------------------------------------------------------------------------
// Define the functions:
//----------------------

// sentence() starts to call noun()

bool conjunction();
bool verb();
bool noun();

bool sentence() {

	bool check;
	std::string word;

	check = noun();

	if (check) {
		return true;
	}
	else {
		return false;
	}
}

// Noun function has to be followed by a verb
bool noun() {

	std::string word;

	std::cin >> word;

	if (is_in(word, Art)) {
		std::cin >> word;
	}

	if (is_in(word,Noun)) {
		return verb();
	}

	else return false;
}

bool verb() {

	std::string word;

	std::cin >> word;


	if (is_in(word,Verb)) {
		return conjunction();
	}

	else return false;

}


bool conjunction() {

	std::string word;

	std::cin >> word;

	if (word == ".") {
		return true;
	}

	if (is_in(word, Conj)) {
		return sentence();
	}

	else return false;

}

// Verb function has to be followed by a conjuction or a full stop

// Conjuction has to be followed by another sentence


// The artile 'The' can only preceed a noun

int main() {

	bool answer;
	std::string word;

	std::cout << "Please insert a phrase:\n";

	while (true) {
		
		answer = sentence();

		if (answer) {
			std::cout << "OK\n";
		}	
		else if (!answer) {
			std::cout << "Not OK\n";
		} 
	}
	return 0;
}
