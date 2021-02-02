#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    int v1 {};
    int v2 {};
    int prod {};
    int sum {};
    int diff {};
    double ratio {};

    std::cout << "Please enter first number:\n";
    std::cin >> v1;
    std::cout << "Please enter second number:\n";
    std::cin >> v2;

    if (v1 > v2)
        std::cout << "the first number is larger\n";
    if (v1 < v2)
        std::cout << "the second number is larger\n";
    if (v1 == v2)
        std::cout << "the numbers are equal\n";

    prod = v1 * v2;
    sum = v1 + v2;
    diff = v1 - v2;
    ratio = v1 / v2;

    std::cout << "Product: " << prod << "\n"
        << "Sum: " << sum << "\n"
        << "Diff: " << diff << "\n"
        << "Ratio: " << ratio << "\n";

    return 0;
}
