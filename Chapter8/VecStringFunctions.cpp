
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void print(const vector<string>& x, const vector<int>& y) 
{
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << '\t' << y[i] << "\n";
    }
}
 
struct Result 
{
	vector<int> vec;
	string longest;
	string shortest;
	string first;
	string last;
};

Result Count(vector<string> vec) 
{

	Result result;
	vector<int> count = {};

	for (string x : vec) {
		count.push_back(x.size());
	}

	result.vec = count;

	int longest = count[0];
	int shortest = count[0];
	result.longest = vec[0];
	result.shortest = vec[0];

	for (int i = 1; i < count.size(); i++) {
		if (count[i] > longest) {longest = count[i]; result.longest = vec[i];}
		if (count[i] < shortest) {shortest = count[i]; result.shortest = vec[i];}
	}

	sort(vec.begin(), vec.end());

	result.first = vec[0];
	result.last = vec[vec.size() -1];

	return result;
}


int main () 
{
	vector<string> vec = {"The", "brown", "quit", "fox", "jumped", "quit", "over"};
	vector<int> vec_count = {};
	Result result;

	result = Count(vec);


	print(vec, result.vec);

	cout << '\n' << "First =  " << result.first
		<< '\n' <<  "Last =  " << result.last
		<< '\n' << "Longest =  " << result.longest
		<< '\n' <<  "Shortest =  " <<result.shortest
		<< '\n';

	return 0;
}
