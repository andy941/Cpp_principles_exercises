#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void print(string label, const vector<int>& x) 
{
    cout <<  "\n" << label << "\n";
    for (int i : x) {
        cout << i << "\n";
    }
}

vector<int> Fibonacci (int x, int y, vector<int> v, int n) 
{
	v.push_back(x);
	v.push_back(y);

	for (int i = 0; i < n; i++) {
		v.push_back(v[v.size()-1] + v[v.size()-2]); 
	}

	return v;
}

int main () 
{
	int x = 0;
	int y = 0;
	int n = 0;
	vector<int> result {};
	string label;

	cout << "Please insert the first number for Fibonacci: ";
	cin >> x;
	cout << "\nPlease insert the second number for Fibonacci: ";
	cin >> y;
	cout << "\nPlease insert how many Fibonacci numbers to generate: ";
	cin >> n;
	cout << "\nPlease insert a label for your data: ";
	cin >> label;

	result = Fibonacci(x,y,result,n);
	print(label, result);
}
