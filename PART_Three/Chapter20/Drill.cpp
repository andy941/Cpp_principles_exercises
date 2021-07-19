
#include "../std_lib_facilities.h"

template<typename Iter1, typename Iter2>
Iter2 Copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	if(f1==e1) return f2;			// Check for empty

	while(f1!=e1) {
		*f2 = *f1;
		++f1;
		++f2;
	}
	return f2;
}

int main() 
{
	array<int, 10> arr { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> vec { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	list<int> lst { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	array<int,10> arr_cp;
	vector<int> vec_cp { vec };
	list<int> lst_cp { lst };

	for (int i = 0; i < 10; i++) arr[i] += 2;
	for (int i = 0; i < 10; i++) vec[i] += 3;
	for (auto it = lst.begin(); it != lst.end(); it++) *it += 5;


	cerr << "\nArray:\n ";
	for (int i = 0; i < 10; i++) 
	{
		cerr << arr[i] << '\t';
	}

	cerr << "\nVector:\n ";
	for (int i = 0; i < 10; i++) 
	{
		cerr << vec[i] << '\t';
	}

	cerr << "\nList:\n ";
	for (auto it = lst.begin(); it != lst.end(); it++) 
	{
		cerr << *it << '\t';
	}

	copy(arr.begin(), arr.end(), vec.begin());
	copy(vec.begin(), vec.end(), lst.begin());

	cerr << "\nList after copy test:\n ";
	for (auto it = lst.begin(); it != lst.end(); it++) 
	{
		cerr << *it << '\t';
	}

	auto it = find(vec.begin(), vec.end(), 47);
	if (it!=vec.end()) cout << "Found " << 47 << " at Position " << vec.end() - it << endl;
	auto it2 = find(lst.begin(), lst.end(), 5);
	if (it2!=lst.end()) cout << "Found " << 5 << " at Position " << distance(lst.begin(), it2) << endl;
}



