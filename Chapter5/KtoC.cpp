#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

class bad_Temp {};

double ctok(double c)                   // converts Kelvin to Celsius
{
          int k = c - 273.15;
          if (k < -273.15*2) {
             throw bad_Temp{};
          }
          return k;
}

int main()
{
          double c = 0;                         // declare input variable
          std::cin >> c;                                // retrieve temperature to input variable
          try {
          double k = ctok(c);           // convert temperature
          std::cout << k << "K \n";
          }
          catch (bad_Temp) {
              std::cout << "Input temp too low!\n";
              return 1;
          }

}



