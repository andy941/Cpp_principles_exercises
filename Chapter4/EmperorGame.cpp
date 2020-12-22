#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main() {

    int rice {1};
    int square {1};
    int tot {1};
    int enough {1};
    int last {};

    std::cout << "When it's enough rice?" << "\n";
    std::cin >> enough; 

    while (true) {
        last = tot;
        tot = tot*2;
        if (tot >= enough) {
            break; 
        }
        ++square;
    }

    std::cout << "Square number " << square << "\n" <<
        "Total amount of rice " << last << "\n";

    return 0;
}
