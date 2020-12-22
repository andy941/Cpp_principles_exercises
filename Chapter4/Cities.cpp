#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::vector<double> x = {};
    double dist {};
    double max {};
    double min {};
    double tot {};

    while (std::cin >> dist){
        x.push_back(dist);
    }
    
    tot = x.back();

    if (x.size() == 1) {
        std::cout << "Max: " << x[0] << "\n";
        std::cout << "Min: " << x[0] << "\n";
        std::cout << "Mean: " << x[0]  << "\n";
        return 0;
    }

    for (int i = 1; i < x.size(); i++) {
        if (x[i] <= x[i-1]) {
            min = x[i];
        }

        if (x[i] >= x[i-1]) {
            max = x[i];
        }

        tot += x[i];
    }

    std::cout << "Max: " << max << "\n";
    std::cout << "Min: " << min << "\n";
    std::cout << "Mean: " << tot / x.size() << "\n";
    return 0;
}

