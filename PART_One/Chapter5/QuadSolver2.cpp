#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main () {

    class Neg_root {};
    double a {};
    double b {};
    double c {};
    double result1 {};
    double result2 {};

    std::cout << "Please enter values for 'a', 'b' and 'c':\n";
    std::cin >> a >> b >> c;

    if ((b*b -4*a*c) < 0) {
        throw Neg_root{};
    }

    result1 = (-b + sqrt(b*b -4*a*c))/2*a;
    result2 = (-b - sqrt(b*b -4*a*c))/2*a;


    std::cout << "The results are: " << result1 << " and " <<
        result2 << ".\n";

    return 0;
}

