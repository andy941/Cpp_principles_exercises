#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

void print_until_s (vector<string>& v, string quit)
{
	int count = 0;
	for (string s : v) {
		if (s==quit) count +=1;
		if (count == 2) return;
		cout << s << '\n';
	}
}

int main () 
{
	vector<string> vec = {"The", "brown", "quit", "fox", "jumped", "quit", "over", "the"};

	print_until_s(vec, "quit");

	return 0;
}
