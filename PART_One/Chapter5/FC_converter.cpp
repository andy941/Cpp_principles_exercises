#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

class bad_Temp {};
class bad_Char {};

double ctok(double c, char fc)                   // converts Kelvin to Celsius
{
    if (fc == 'F') {
          double k = (c - 32)*5/9;
          if (k < -459.67) {
             throw bad_Temp{};
          }
          return k;
    }

    if (fc == 'C') {
          double k = c*9/5 + 32;
          if (k < -273.15) {
             throw bad_Temp{};
          }
          return k;
    } 
    
    else { 
        throw bad_Char{};
    }
}

int main()
{
          double c = 0;                         // declare input variable
          char fc = 'N';
          std::cout << "Please enter a temperature followed by an identification"
             " character 'C' or 'F'\n";
          std::cin >> c >> fc;                                // retrieve temperature to input variable
          try {
          double k = ctok(c,fc);           // convert temperature
          std::cout << k << "\n";
          }
          catch (bad_Temp) {
              std::cout << "Input temp too low!\n";
              return 1;
          }
          catch (bad_Char) {
              std::cout << "Bad Identifier please use 'F' or 'C'\n";
              return 1;
          }

}


