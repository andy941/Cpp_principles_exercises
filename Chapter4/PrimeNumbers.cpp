#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

bool FindPrime(int x) {
    
    int count {0};

    for (int i = 2; i < round(sqrt(x)) +1; ++i) {
        if (x % i == 0) {
            ++count;
        }
    }

    if (count > 0) {
        return false;
    }

    else {
        return true;
    }

}

// handy function to print a vector
void printvec(std::vector<int> x) {
    for (int i : x) {
        std::cout << i << "  ";
    }
    std::cout <<  "\n" << "Size = " << x.size() << "\n";
}

int main()
{ 
    int n {};
    int primes {};

    std::cout << "Insert a max number for the range " << "\n";
    std::cin >> n;

    std::cout << "Insert a max number for the primes to retrieve " << "\n";
    std::cin >> primes;

    std::vector<int> nums {};

    // the vector contains integers from 1 to 100
    for (int i = 2; i < n; i++) {
        if (FindPrime(i)) {
            nums.push_back(i);
        }
        if (nums.size() == primes) {
            break;
        }
    }
    
    printvec(nums);
    return 0;
}



