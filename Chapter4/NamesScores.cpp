#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main () {

    std::vector<std::string> names {};
    std::vector<double> scores {};
    std::string name {};
    double score {};
    std::string request {};

    std::cout << "Please enter a name and a score, terminate with 'NoName 0'" << "\n";
    std::cin >> name >> score;
    
    if (name == "NoName" & score == 0) {
        std::cout << "Input terminated by user.\n";
    }

    names.push_back(name);
    scores.push_back(score);

    while (std::cin >> name >> score) {

        if (name == "NoName" & score == 0) {
            std::cout << "Input terminated by user.\n";
            break;
        }

        for (int i = 0; i < names.size(); i++) {

            if (name == names[i]) {
                std::cout << "Name already in the database!\n";
                break;
            }

            if (i == names.size() -1) {
                names.push_back(name);
                scores.push_back(score);
                break;
            }
        }

    }

    for (int i = 0; i < names.size(); i++) {
        std::cout << "\n" << names[i] << "\t" << scores[i] << "\n";
    }

    std::cout << "Please insert a Name to know the score\n";

    while (std::cin >> request) {

        for (int i = 0; i < names.size(); i++) {

            if (request == names[i]) {
                std::cout << "The score of " << request << " is " <<
                    scores[i] << "\n";
                break;
            }

            if (i == names.size() -1) {
                std::cout << "Name not in database. \n";
                break;
            }
        }
    }



    return 0;
}
