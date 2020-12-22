#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::string v1 {};
    std::string v2 {};
    std::string v3 {};
    std::string o1 {};
    std::string o2 {};
    std::string o3 {};

    std::cout << "Please enter three words:\n";
    std::cin >> v1 >> v2 >> v3;

    o1 = v1;
    o2 = v2;
    o3 = v3;

    if (o1 > o2) {
        o1 = v2;
        o2 = v1;
    }
    std::cout << o1 << "," << o2 << "," << o3 << "\n";

    if (o2 > o3) {
        o3 = o2;
        o2 = v3;
    }
    std::cout << o1 << "," << o2 << "," << o3 << "\n";

    if (o1 > o2) {
        o2 = o1;
        o1 = v3;
    }
    std::cout << o1 << "," << o2 << "," << o3 << "\n";
    return 0;
}
