#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main () {

    class Too_many_numbers {};
    std::vector<int> vec {};
    int num {};
    int numbers {};
    int sum {0};

    std::cout << "Please insert how many numbers you want to sum\n";
    std::cin >> numbers;
    if (!std::cin)  {
        std::cerr << "input not an integer\n";
        return 1;
    }


    std::cout << "Insert the numbers to sum, terminate with '|'.\n";

    while (std::cin >> num) {
        vec.push_back(num);
        if (!std::cin) {
            std::cerr << "cannot read a double\n";
        }
    }

    if (vec.size() < numbers) {
        throw Too_many_numbers{};
        return 1;
    }

    for (int i = 0; i < numbers; i++) {
        sum += vec[i];
    }  

    std::cout << "The sum is: " << sum << " \n";

    return 0;
}

