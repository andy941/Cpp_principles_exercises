#include "../std_lib_facilities.h"

template<typename T>
inline ostream& operator<<(ostream& os, const vector<T>& v) 
{
	cout << "{ ";
	for (T& x : v) cout << x << ',';
	cout << " }";
	return os;
}

template<typename T>
inline istream& operator>>(istream& is, vector<T>& v) 
{
	T t;
	char buffer;
	while(cin >> t) 
	{
		v.push_back(t);
		cin.get(buffer);
		if (buffer == '\n') return is;
		cin.putback(buffer);
	}
	return is;
}

int main() 
{
	vector<int> ints;
	vector<char> chars;
	cout << "Please insert a spaced vector of integers:\n";
	cin >> ints;
	cout << "Please insert a spaced vector of chars:\n";
	cin >> chars;

	for (auto& x : ints) cout << x << ',';
	cout << endl;
	for (auto& x : chars) cout << x << ',';
}



