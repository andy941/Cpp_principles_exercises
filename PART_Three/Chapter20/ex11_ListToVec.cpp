#include "../std_lib_facilities.h"

template<typename T, typename U>
void universal_copy( const T& l, U& v)
{
	auto it_v = v.begin();
	for (auto it = l.begin(); it != l.end(); it++) {
		*it_v = *it;
		++it_v;
	}
}

template<typename T>
void print( const T& data)
{
	for (auto x : data) cout << x << '\t';
}

int main() 
{
	list<int> lst { 20, 5, 4, 3, 1, 5, 10, 2, 15, 7 };
	vector<double> vec(lst.size());

	print(lst);
	cout << endl;
	print(vec);
	cout << endl;
	cout << "---------------------------------------------------------------------------------------------" << endl;
	universal_copy(lst, vec);
	print(lst);
	cout << endl;
	print(vec);
	cout << endl;
	cout << "---------------------------------------------------------------------------------------------" << endl;
	sort(vec.begin(), vec.end());
	print(lst);
	cout << endl;
	print(vec);
	cout << endl;
}



