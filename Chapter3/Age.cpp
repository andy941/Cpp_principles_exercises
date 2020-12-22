#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::cout << "Please enter your age in years\n";

    float age;
    std::cin >> age;

    std::cout << "Your age in months is: " 
        << age*12 << "\n";
    
    return 0;

}
