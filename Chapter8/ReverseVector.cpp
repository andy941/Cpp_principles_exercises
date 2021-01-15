#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void print(const vector<int>& x) 
{
    for (int i : x) {
        cout << i << " ";
    }
	cout << '\n';
}

vector<int> RevVec (vector<int> vec) 
{
	vector<int> result(vec.size());

	for (int i = 0; i < vec.size(); i++) {
		result[vec.size() - 1 - i] = vec[i];
	}
	return result;
}

void _RevVec (vector<int>& vec) 
{
	int iter = floor(vec.size()/2);
	int tmp = 0;

	for (int i = 0; i < iter; i++) {
		tmp = vec[i];
		vec[i] = vec[vec.size() -1 -i];
		vec[vec.size() -1 -i] = tmp;
	}
}

int main () 
{
	vector<int> vec = {1,2,3,4,5,6,7,8};
	vector<int> vec2 = {1,2,3,4,5,6,7};

	print(vec);
	print(vec2);

	print(RevVec(vec));
	print(RevVec(vec2));

	_RevVec(vec);
	_RevVec(vec2);

	print(vec);
	print(vec2);
}

