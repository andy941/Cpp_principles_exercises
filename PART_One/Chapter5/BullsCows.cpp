#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

// handy function to print a vector
void printvec(std::vector<int> x) {
    for (int i : x) {
        std::cout << i << "  ";
    }
    std::cout <<  "\n" << "Size = " << x.size() << "\n";
}

std::vector<int> BullsCows(std::vector<int> nums, std::vector<int> hnums){

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

    std::vector<int> vec = {};
    std::vector<int> hid = {};
    std::vector<int> bullscows = {};
    int n;
    int seed;

    std::cout << "Please insert a seed\n";
    std::cin >> seed;
    srand(seed);

    for (int i=0; i < 4; i++) {
        hid.push_back(rand() % 4);
    }

    while (true) {

        vec = {};

        std::cout << "Please insert 4 integers from 0 to 9 separated by  space\n";

        while (true) {

            if (vec.size() == 4) {
                break;
            }

            std::cin >> n;
            vec.push_back(n);
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
