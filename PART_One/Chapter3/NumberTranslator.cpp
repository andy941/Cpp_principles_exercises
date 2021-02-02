#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    int nu {0};

    std::cout << "Enter a number from 1 to 4: \n";

    std::cin >> nu;

    if (nu == 1) {
        std::cout << "The number is spelled: ONE\n";
    }
    else if (nu == 2) {
        std::cout << "The number is spelled: TWO\n";
    }
    else if (nu == 3) {
        std::cout << "The number is spelled: THREE\n";
    }
    else if (nu == 4) {
        std::cout << "The number is spelled: FOUR\n";
    }
    else {
        std::cout << "Not a number from 1 to 4\n";
    }

    return 0;
}
