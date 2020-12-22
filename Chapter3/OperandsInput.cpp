#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::string op {};
    double v1 {};
    double v2 {};

    std::cout << "Please enter an operator and two numbers \n";
    std::cin >> op >> v1 >> v2;

    if (op == "+") {
        std::cout << v1+v2 << "\n";
    }
    if (op == "-") {
        std::cout << v1-v2 << "\n";
    }
    if (op == "*") {
        std::cout << v1*v2 << "\n";
    }
    if (op == "/") {
        std::cout << v1/v2 << "\n";
    }
    
    return 0;
}

