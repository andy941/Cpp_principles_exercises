#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

// handy function to print a vector
void printvec(std::vector<int> x) {
    for (int i : x) {
        std::cout << i << "  ";
    }
    std::cout <<  "\n" << "Size = " << x.size() << "\n";
}

int main () {

    std::vector<int> vec = {1,1};
    int fib {};
    int num {};

    std::cout << "Insert a number:\n";
    std::cin >> num;

    while (true) {
        fib = vec[vec.size() -1] + vec[vec.size() -2];

        if (fib > num) {
            break;
        }

        vec.push_back(fib);
    }

    std::cout << "Fibonacci series:\n";
    printvec(vec);
    std::cout << "\nThe largest Fibonacci number contained in " <<
        num << " is: " << vec[vec.size()-1] << "\n";

    return 0;
}

    


