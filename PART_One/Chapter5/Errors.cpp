#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main() {

    try {
        std::cout << "Success!\n";
        return 0;
    }

    catch (std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }

    catch (...) {
        std::cerr << "Oops: unknown exception!\n";
        return 2;
    }
}              
