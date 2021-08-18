#include "../std_lib_facilities.h"

template<typename Iter, typename T>
  typename iterator_traits<Iter>::difference_type
Count(Iter b, Iter e, T t)
{
	typename iterator_traits<Iter>::difference_type c = 0;	// Like std, trait has to be defined in the iterator
	while (b!=e) {
		if (*b == t) ++c;
		++b;
	}
	return c;
}

int main() 
{
	vector<int> v(40);
	generate(v.begin(), v.end(), [](){ return rand()%10; });
	for (auto& x : v) cout << x << ' ';
	cout << endl;
	int c = Count(v.begin(), v.end(), 3);
	cout << "Count occurence of 3: " << c << endl;
}



