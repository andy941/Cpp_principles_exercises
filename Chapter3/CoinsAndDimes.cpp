#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    int v1 {};
    int v2 {};

    std::cout << "How many nickels do you have?\n";
    std::cin >> v1;
    std::cout << "How many dimes do you have?\n";
    std::cin >> v2;

    if (v1 == 1) {
        std::cout << "You have " << v1 << " nickel\n";
    }
    else if (v1 != 1){
        std::cout << "You have " << v1 << " nickels\n";
    }

    if (v2 == 1) {
        std::cout << "You have " << v1 << " dime\n";
    }
    else if (v2 != 1){
        std::cout << "You have " << v1 << " dimes\n";
    }

    std::cout << "Your total is $" << 0.05*v1 + 0.1*v2 << "\n";

    return 0;
}


