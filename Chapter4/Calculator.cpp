#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main() {

    int a {};
    int b {};
    std::string c {};
    std::string d {};
    char op {};
    std::vector<std::string> numbers = {"zero","one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

    std::cout << "Please insert two numbers and one operator (+,-,*,/)" << "\n";

    while (std::cin >> c >> op >> d) {

        int idx {0};

        for (std::string i : numbers) {

            if (i == c) {
                a = idx;
            } 
            if (i == d) {
                b = idx;
            } 
            ++idx;
        }



        if (op == '+') {
            std::cout << "The sum of " << a << " and " << b << " is " << a+b << "\n";
        }
        else if (op == '-') {
            std::cout << "The subtraction of " << a << " and " << b << " is " << a-b << "\n";
        }
        else if (op == '*') {
            std::cout << "The product of " << a << " and " << b << " is " << a*b << "\n";
        }
        else if (op == '/') {
            std::cout << "The ratio of " << a << " and " << b << " is " << a/b << "\n";
        }


        else {
            break;
        }

        std::cout << "Please insert two numbers and one operator (+,-,*,/) separated by a single space" << "\n";
    }
    return 0;
}
