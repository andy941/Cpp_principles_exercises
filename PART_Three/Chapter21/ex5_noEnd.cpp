#include "../std_lib_facilities.h"

template<typename Iter, typename T>
  typename iterator_traits<Iter>::difference_type
Count(Iter b, Iter e, T t)
{
	typename iterator_traits<Iter>::difference_type c = 0;	// Like std, trait has to be defined in the iterator
	while (b!=e+1) {
		if (*b == t) ++c;
		++b;
	}
	return c;
}

template<class InputIterator, class T>		// find from STD reworked
InputIterator Find (InputIterator first, InputIterator last, const T& val, bool& found)
{
	while (first!=last+1) {
		if (*first==val) { return first; found=true; }
		++first;
	}
	if (*last == val) { return last; found=true; }

	found=false;		// My way of saying. NOT FOUND instead of end();
	return last;
}

int main() 
{
	// Count version without end() one after the last
	vector<int> v(10);
	vector<int>::iterator vit { &v[v.size()-1] };
	generate(v.begin(), vit, [](){ return rand()%10; });
	for (auto& x : v) cout << x << ' ';
	cout << endl;
	int c = Count(v.begin(), v.end()-1, 3);
	v.push_back(3);
	int c2 = Count(v.begin(), v.end()-1, 3);
	for (auto& x : v) cout << x << ' ';
	cout << "Count occurence of 3: " << c << ' ' << c2 << endl;
	// Find version without end() one after the last
	bool f1, f2;
	auto three = Find(v.begin(), v.end(), 3, f1);
	auto twelve = Find(v.begin(), v.end(), 12, f2);
	if (f1) cout << "Found " << *three << endl;
	if (f2) cout << "Found " << *twelve << endl;

}



