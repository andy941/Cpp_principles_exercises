#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    int i {1};

    while (i == 1) { 

        double a = {};
        double b = {};

        std::cout << "Please enter two numbers:\n";
        std::cin >> a >> b;

        if (std::cin.fail()) {
            break;
        }

        else if ((a - b) <= 0.01) {
            std::cout << "The numbers are  almost equal" << "\n";
        }

        else if (a < b) {
            std::cout << "The smaller number is " << a << "\n";
            std::cout << "The larger number is " << b << "\n";
        }

        else if (a > b) {
            std::cout << "The smaller number is " << b << "\n";
            std::cout << "The larger number is " << a << "\n";
        }

        else if (a == b) {
            std::cout << "The numbers are equal" << "\n";
        }


    }

    return 0;
}
