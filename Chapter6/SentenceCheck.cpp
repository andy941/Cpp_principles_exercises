#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>


std::vector<std::string> Noun = {"birds", "fish", "C++"};
std::vector<std::string> Conj = {"and", "or", "but"};
std::vector<std::string> Verb = {"rules", "fly", "swim"};

// handy function to print a vector
void printvec(std::vector<std::string> x) {
    for (std::string i : x) {
        std::cout << i << "\n";
    }
}

// function to check if a variable is in a vector
bool is_in(std::string word, std::vector<std::string> x) {
	bool found = false;
	for (std::string i : x) {
		if (i == word) found = true;
	}
	return found;
}


int main() {

	std::string word;
	std::string nextword;

	std::cout << "Please insert a phrase:\n";

	while (std::cin >> word) {
		if (word == ".") {
			std::cout << "OK\n";
			continue;
		}

		std::cin >> nextword;

		if (word == "\n") {
			std::cout << "Not OK\n";
		}
	}
	return 0;
}
