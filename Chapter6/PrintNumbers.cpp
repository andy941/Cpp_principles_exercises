#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main() {

	std::vector<std::string> words = {"Thousands", "Hundreds", "Tens", "Ones"};
	std::vector<char> number = {};
	char num;

	std::cout << "Please insert a number with magnitude 10^3 max:\n"
		"Terminate the input with an '=' sign\n";
	
	while (std::cin >> num) {
		if (num == '=') break;
		number.push_back(num);
	}

	for (char x : number) {
		std::cout << x;
	}

	std::cout << " is ";

	for (int i = 0; i < number.size(); i++) {
		int digit = number[i] - '0';
		std::string word= words[words.size() - number.size() + i];

		std::cout << digit << " " << word << " ";

		
	}

	std::cout << "\n";

	return 0;
}
