#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    double a {};
    double b {};
    double c {};
    double sum {};
    std::string unit;
    std::vector<double> measures;

    constexpr double convm = 100;
    constexpr double convin = 2.54;
    constexpr double convft = 12*2.54;

    std::cout << "Please enter a number followed by cm, m, in or ft:\n";
    std::cin >> a >> unit;

    if (unit == "m") {
        a = convm*a;
    } else if (unit == "in") {
        a = convin*a;
    } else if (unit == "ft") {
        a = convft*a;
    } else if (unit == "cm") {
    } else {
        std::cout << "Unit not valid\n";
    }

    b = a;
    c = a;

    sum += a;
    measures.push_back(a);

    while (true) { 

        std::cout << "Please enter a number followed by cm, m, in or ft:\n";
        std::cin >> a >> unit;

        if (std::cin.fail()) {
            break;
        }

        if (unit == "m") {
            a = convm*a;
        } else if (unit == "in") {
            a = convin*a;
        } else if (unit == "ft") {
            a = convft*a;
        } else if (unit == "cm") {
        } else {
            std::cout << "Unit not valid\n";
        }


        if (a < b) {
            b = a;
            std::cout << "The smaller measure is now: " << b << "cm" << "\n";
        }

        if (a > c) {
            c = a;
            std::cout << "The larger measure is now: " << c << "cm" << "\n";
        }

        sum += a;
        measures.push_back(a);
    }
    
    std::cout << "The larger measure is: " << b << "cm" << "\n";
    std::cout << "The smaller measure is: " << c << "cm" << "\n";
    std::cout << "The sum  is: " <<  sum << "cm" << "\n";
    
    std::sort(measures.begin(), measures.end());
    for (int i : measures) {
        std::cout << i << "\n";
    }

    return 0;
}

