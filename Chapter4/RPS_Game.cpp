#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    char choice {};
    std::vector<char> choices = {'r', 'p', 's'};
    char mychoice {};

    std::cout << "Rock 'r', Paper 'p', Scissors 's' \n";

    while (std::cin >> choice) {

        mychoice = choices[rand() % 3];

        if (choice == mychoice) {
            std::cout << "I Won!\n";
        }
        else if (choice != mychoice) {
            std::cout << "You Won ....\n";
        }

    std::cout << "Mychoice: " << mychoice << "\n" << "Your choice: " << choice << "\n";

    }

    std::cout << "we can play later...\n";

    return 0;

}

