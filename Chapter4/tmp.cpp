#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::vector<char> alphabet(26);
    alphabet[5] = 'r';
    std::cout << alphabet.size() << "\n";
    
    for (char x : alphabet) {
        std::cout << x << "\n";
    }

    return 0;
}
