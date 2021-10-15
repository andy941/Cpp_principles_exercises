
#include "../std_lib_facilities.h"
using namespace std;

template<class RAIter, class T>
bool alg(RAIter b, RAIter e, T t)
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

int main () 
{
	constexpr long long int sz { 1000000 };
	vector<int> v(sz);
	constexpr long long int n { sz/2 + 100 };

	iota(v.begin(), v.end(), 0);
	sort(v.begin(), v.end());
	if (alg(v.begin(), v.end(), n)) cout << "Found number: " << n << endl;
	else  cout << "NOT Found number: " << n << endl;
	 
}
