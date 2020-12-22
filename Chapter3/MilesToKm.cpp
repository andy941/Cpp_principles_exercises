#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::cout << "Please enter a distance in kilometers:\n";
    
    double km {0};
    std::cin >>  km;
    
    std::cout << km*1.609 << "\n";
}
