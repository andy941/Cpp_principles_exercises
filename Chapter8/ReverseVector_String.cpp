#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void print(const vector<string>& x) 
{
    for (string i : x) {
        cout << i << " ";
    }
	cout << '\n';
}

vector<string> RevVec (vector<string> vec) 
{
	vector<string> result(vec.size());

	for (int i = 0; i < vec.size(); i++) {
		result[vec.size() - 1 - i] = vec[i];
	}
	return result;
}

void _RevVec (vector<string>& vec) 
{
	int iter = floor(vec.size()/2);
	string tmp = "";

	for (int i = 0; i < iter; i++) {
		tmp = vec[i];
		vec[i] = vec[vec.size() -1 -i];
		vec[vec.size() -1 -i] = tmp;
	}
}

int main () 
{
	vector<string> vec = {"the","brown","fox","jumped","over", "the","lazy","dog"};
	vector<string> vec2 = {"the","brown","fox","jumped","over", "the","lazy"};

	print(vec);
	print(vec2);

	print(RevVec(vec));
	print(RevVec(vec2));

	_RevVec(vec);
	_RevVec(vec2);

	print(vec);
	print(vec2);
}

