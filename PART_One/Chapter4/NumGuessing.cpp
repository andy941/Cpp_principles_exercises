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

int main()
{
    char answer = 'y';
    int count {1};
    std::vector<int> nums {};
    std::vector<int> subset {};
    double mean {};

    // the vector contains integers from 1 to 100
    for (int i = 1; i < 101; i++) {
        nums.push_back(i);
    }

    std::cout << "Think of a number from 1 to 100" << "\n" << "\n";

    while (nums.size() != 1) {

        mean = (nums[0] + nums[nums.size() - 1]) / 2;
        std::cout << count << "- Is your number > " << mean <<  " (y) (n)" << "\n";
        std::cin >> answer;

        if (answer == 'y') {
            for (int i : nums) {
                if (i > mean) {
                    subset.push_back(i); 
                }
            }
        }

        if (answer == 'n') {
            for (int i : nums) {
                if (i <= mean) {
                    subset.push_back(i); 
                }
            }
        }

        ++count;

        nums = subset;
        subset = {};
        printvec(nums);

    }

    std::cout << "Your number is " << nums[0] << "\n";
    return 0;
}


