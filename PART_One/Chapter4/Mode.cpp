#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main () {

    std::vector<std::string> vec = {};
    std::vector<int> count = {};
    std::vector<std::string> unique = {};
    std::string word {};
    std::string mode {};
    int value {};
    std::string max {};
    std::string min {};

    std::cout << "Please enter a series of numbers separated by spaces (terminate with any character)" << "\n";

    while (std::cin >> word) {
        vec.push_back(word);
    }

    unique.push_back(vec[0]);
    count.push_back(1);

    for (int i = 1; i < vec.size(); i++) {

        for (int j = 0; j < unique.size(); j++) {

            if (vec[i] == unique[j]) {
                count[j] += 1;
                break;
            } 

            else if  (j == unique.size() - 1) {
                unique.push_back(vec[i]);
                count.push_back(1);
                break;
            }
        }
    }

    value = count[0];
    mode = unique[0];

    for (int i = 0; i < count.size(); i++) {
        if (count[i] >= value) {
            mode = unique[i];
            value = count[i];
        }
    }

    std::cout << "\n" << "Mode: " << mode << "\n" << "\n";

    for (int i = 0; i < unique.size(); i++) {
        std::cout << unique[i] << "\t" << count[i] << "\n";
    }

    if (vec.size() == 1) {
        std::cout << "Max: " << vec[0] << "\n";
        std::cout << "Min: " << vec[0] << "\n";
        return 0;
    }

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] <= vec[i-1]) {
            min = vec[i];
        }

        if (vec[i] >= vec[i-1]) {
            max = vec[i];
        }
    }

    std::cout << "Max: " << max << "\n";
    std::cout << "Min: " << min << "\n";
    
    return 0;
}


