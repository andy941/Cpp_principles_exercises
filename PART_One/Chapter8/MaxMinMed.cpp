#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

// To answer Bjarne, the Struct is better becuse more self explanatory (ex11)
struct Result 
{
	double max;
	double min;
	int med;
};

Result maxv (vector<double> vec) 
{
	Result a;
	a.max = vec[0];
	a.min = vec[0];
	a.med = 0;

	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] > a.max) a.max = vec[i];
		if (vec[i] < a.min) a.min = vec[i];
	}

   if (vec.size()%2 == 1) { 
    a.med = vec.size()/2;
   }

   if (vec.size()%2 == 0) { 
    a.med = vec[vec.size()/2 -1] + ((vec[vec.size()/2] - vec[vec.size()/2 -1]) /2);
   }

   return a;
}



