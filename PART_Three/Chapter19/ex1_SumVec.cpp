
#include "../std_lib_facilities.h"
#include <exception>

/*
 * The function sums the two vectors member-wise for the whole length of the first
 * vector. if the firs vector is longer than the second it just adds 0 for the missing
 * values.
*/

template <typename T>
void f(vector<T>& v1, const vector<T>& v2)
{
	for (int i = 0; i < v1.size(); i++) {
		try { v1[i] += v2[i]; }
		catch ( const std::out_of_range& e) {  };		// Do nothing, could be resolved with no try catch and explicit range checking.
	}
}

int main() 
{
	vector<int> v1 { 1,1 };
	vector<int>	v2 { 1,1,1 };
	vector<int>	v3 { 1,1,1,1 };

	f(v2,v2);
	for (auto& x : v2) cout << x << '\t';
	cout << endl;
	f(v2,v1);
	for (auto& x : v2) cout << x << '\t';
	cout << endl;
	f(v2,v3);
	for (auto& x : v2) cout << x << '\t';
	cout << endl;

	vector<string> v4 { "abc","abc" };
	vector<string>	v5 { "abc","abc","abc" };
	vector<string>	v6 { "abc","abc","abc","abc" };

	f(v5,v5);
	for (auto& x : v5) cout << x << '\t';
	cout << endl;
	f(v5,v4);
	for (auto& x : v5) cout << x << '\t';
	cout << endl;
	f(v5,v6);
	for (auto& x : v5) cout << x << '\t';
	cout << endl;
}
