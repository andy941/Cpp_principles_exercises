#include "../std_lib_facilities.h"

/* 
 * Binary search in the standard library returns bool, I will do the same here
 * Without random access iterators in list is not possible, or it doesn't make sense to 
 * try and implement a binary search, you still have to visit all the members of the list
 * one by one. you can't do better than O(n) for a regular list. 
 * It's a good exercise however to make the same function work for both with template dipatching
 * (I just learnt it exists and it seems the thing that makes most sense here).
 * This is adapted from: https://en.cppreference.com/w/cpp/iterator/iterator_tags
 */

namespace implementation_details {
	template<class BDIter, class T>
		bool alg(BDIter b, BDIter e, T t, std::forward_iterator_tag)
		{
			cerr << "Forward iterator Bsearch called." << endl;
			if (b==e) return false;

			if (t < *b) return false;

			while (b != e) {
				if (*b==t) return true;
				++b;
			}
			return false;
		}
	 
	template<class RAIter, class T>
		bool alg(RAIter b, RAIter e, T t, std::random_access_iterator_tag)
		{
			cerr << "Random iterator Bsearch called." << endl;
			if (b==e) return false;

			if (t > *(e-1)) return false;
			if (t < *b) return false;

			RAIter m = b + (e-b)/2;
			while (b <= e) {
				cout << *b << ' ' << *m << ' ' << *e << endl;
				if (t == *m) return true;
				if (t <= *m) e = m-1;
				if (t >= *m) b = m+1;
				m = b + (e-b)/2;
			}
			return false;
		}
} // namespace implementation_details

template<typename Iter, typename T>
bool Bsearch(Iter b, Iter e, T t)
{
	return implementation_details::alg(b,e,t, 
			typename iterator_traits<Iter>::iterator_category());
}

int main() 
{
	constexpr long long int sz { 1000000 };
	list<int> l(sz);
	vector<int> v(sz);
	constexpr long long int n { sz/2 + 100 };

	iota(v.begin(), v.end(), 0);
	iota(l.begin(), l.end(), 0);
	//for (auto& x : v) cout << x << ' ';
	//cout << endl;
	sort(v.begin(), v.end());
	//for (auto& x : v) cout << x << ' ';
	//cout << endl;
	if (Bsearch(v.begin(), v.end(), n)) cout << "Found number: " << n << endl;
	else  cout << "NOT Found number: " << n << endl;

	cout << endl;
	cout << endl;
	//for (auto& x : l) cout << x << ' ';
	//cout << endl;
	l.sort();
	//for (auto& x : l) cout << x << ' ';
	//cout << endl;
	if (Bsearch(l.begin(), l.end(), n)) cout << "Found number: " << n << endl;

	cout << endl;
	cout << endl;
}




