#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

int main()
{
    std::vector<double> x = {1,2,3,4,5,6};
    double j {};
    
   if (x.size()%2 == 1) { 
    std::cout << x[x.size()/2] << "\n";
   }

   if (x.size()%2 == 0) { 
    j = x[x.size()/2 -1] + ((x[x.size()/2] - x[x.size()/2 -1]) /2);
    std::cout << j << "\n";
   }
    return 0;
}

