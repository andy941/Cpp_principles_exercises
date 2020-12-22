#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::cout << "Please enter a number:\n";

    int n;
    std::cin >> n;

    std::cout << "sum itself: " << n+n;
    std::cout << "squared: " << n*n;
    std::cout << "div/2: " << n/2 << "modulo: " << n%2;

    double nd = n;
    std::cout << "square root: " << sqrt(nd) ;
    
    return 0;

}

