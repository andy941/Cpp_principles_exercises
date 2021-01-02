#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

// handy function to print a vector
void printvec(std::vector<char> x) {
    for (char i : x) {
        std::cout << i << "  ";
    }
    std::cout <<  "\n" << "Size = " << x.size() << "\n";
}

bool is_in(char word, std::vector<char> x) {
	bool found = false;
	for (char i : x) {
		if (i == word) found = true;
	}
	return found;
}

std::vector<int> BullsCows(std::vector<char> nums, std::vector<char> hnums){

    int bulls = 0;
    int cows = 0;
    std::vector<int> results = {};

    for (int i=0; i < nums.size(); i++) {

        for (int j=0 ; j < hnums.size(); j++) {

            if (nums[i] == hnums[j] & i==j) {
                bulls += 1;
            } else if (nums[i] == hnums[j]) {
                cows += 1;
            }
        }
    }

    results.push_back(bulls);
    results.push_back(cows);

    return results;
}

int main() {

	std::vector<char> letters = {'a', 'b', 'c', 'd', 'e'};
	std::vector<char> vec = {};
	std::vector<char> hid = {};
	std::vector<int> bullscows = {};
	char n;
	int seed;
	char letter;

	std::cout << "Please insert a seed\n";
	std::cin >> seed;
	srand(seed);

	while (true) {

		letter = letters[rand() % 4];

		if (!is_in(letter, hid)) {
			hid.push_back(letter);
		}

		if (hid.size()  == 4) {
			break;
		}
	}


	std::cout << "Please insert 4 unique letters from 'a' to 'e' separated by  space\n";

	while (true) {

		vec = {};


		while (std::cin >> n) {

			vec.push_back(n);
			if (vec.size()  == 4) {
				break;
			}
		}

		bullscows = BullsCows(vec,hid);

		std::cout << "You have " << bullscows[0] << " Bulls " <<
			"and " << bullscows[1] << " Cows. \n";

		printvec(vec);
		printvec(hid);

		if (bullscows[0] == hid.size()) {
			break;
		}
	}

	std::cout << "Congratulations your guess is right!\n";

	return 0;
}

