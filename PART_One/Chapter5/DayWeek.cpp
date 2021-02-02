#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

// handy function to print a vector
void printvec(std::vector<std::string> x) {
    for (std::string i : x) {
        std::cout << i << "\n";
    }
}

int main() {

    std::string day = {};
    int value = {};
    std::vector<std::string> Rejected = {};
    std::vector<std::string> Week = {"Mon","Tue","Wed","Thu", "Fri","Sat","Sun"};
    std::vector<int> values(7);   

    std::cout << "Please enter a Day of the week and a value\n" <<
        "Accepted Days:\n";
    printvec(Week);
    std::cout << "Terminate with 'end' as a day name\n";

    while (std::cin >> day >> value) {

        if (day == "end" && value == 0) break;

        int count = 0;
        for (std::string x : Week) {
            if (x==day) count += 1;
        }

        if (count == 0) Rejected.push_back(day);

        for (int i =0; i < Week.size(); i++) {
            if (Week[i] == day) 
                values[i] += value;
        }

    }

    for (int i =0; i < Week.size(); i++) {
        std::cout << Week[i] << '\t' << values[i] << "\n";
    }

    std::cout << "Rejected " << Rejected.size() << " days: " << "\n";
    printvec(Rejected);

    return 0;
}


