#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    int number_of_words = 0;
    std::string previous = " ";       // previous word; initialized to “not a word”
    std::string current;                             // current word
    while (std::cin>>current) {                // read a stream of words
        ++number_of_words;
        if (previous == current)    // check if the word is the same as last
            std::cout << "word number" << number_of_words << "repeated: " << current << "\n";
        previous = current;
    }
}


