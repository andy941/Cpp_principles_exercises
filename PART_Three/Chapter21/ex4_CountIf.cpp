
#include "../std_lib_facilities.h"

template<typename Iter, typename Predicate>
  typename iterator_traits<Iter>::difference_type
Count_if(Iter b, Iter e, Predicate p)
{
	typename iterator_traits<Iter>::difference_type c = 0;	// Like std, trait has to be defined in the iterator
	while (b!=e) {
		if (p(*b)) ++c;
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
	int c = Count_if(v.begin(), v.end(), [&](int x){ return x<3;});
	cout << "Count members < 3: " << c << endl;
}



