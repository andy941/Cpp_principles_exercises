#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    int nu {0};

    std::cout << "Enter a number: \n";

    std::cin >> nu;

    if (nu%2 == 0) {
        std::cout << "The number " << nu << " is even.\n";
    }
    if (nu%2 != 0) {
        std::cout << "The number " << nu << " is odd.\n";

    }

    return 0;
}
