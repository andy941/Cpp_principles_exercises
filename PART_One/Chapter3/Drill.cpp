#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::cout << "Please enter the name of the person you want to write to:\n";
    std::string first_name {};
    std::cin >> first_name;

    std::cout << "Please enter friend name:\n";
    std::string friend_name {};
    std::cin >> friend_name;

    std::cout << "Please enter your friend's sex (f or m):\n";
    char friend_sex {0};
    std::string pronoun {};
    std::cin >> friend_sex;
    if (friend_sex == 'm') 
       pronoun = "him"; 
    if (friend_sex == 'f') 
       pronoun = "her"; 

    std::cout << "Please enter the age of the person you want to write to:\n";
    int age {0};
    std::string response {};
    std::cin >> age;
    if (age >110 || age < 0)
        std::cout << "You are kidding.\n";
    if (age < 12)
       response = "Next year you will be " + std::to_string(age+1) + "\n"; 
    if (age == 17)
       response = "Next year you will be able to vote\n";
    if (age >70)
       response = "I hope you are enjoying retirement\n";

    std::cout << "Dear " << first_name << ",\n"
        "How are you?\nLong time no see!\n"
        "Have you seen " << friend_name << " lately?\n"
        "If you see " << pronoun << " tell " << pronoun << " to call me.\n"
        << response
        << "\n\nYours Sincerely,\nAndrea Finocchio\n";
    
    return 0;

}
