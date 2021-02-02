#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::cout << "Please enter a number:\n";

    double n {0};
    std::string currency {""};
    std::cout << "Enter amount and currency to be converted:\n ";
    std::cin >> n >> currency;

    if (currency == "yen") {
    std::cout << "The total amount is $" << n*0.0096 << "\n";
    }
    else if (currency == "euro") {
    std::cout << "The total amount is $" << n*1.1000 << "\n";
    }
    else {
    std::cout << "Please insert a valid currency \n";
    }

    return 0;

}

