#include "../std_lib_facilities.h"
#include "ex1-2_Triple.cpp"
#include <boost/bind/bind.hpp>

using namespace Numeric_lib;
using namespace std;

// This is VERY hard for me, I know it says is for experts only but
// it would have been nice to have some more hints to at least try.
// It seems something that could be very useful.

template<typename F, typename T>
Matrix<T> Apply(F f, Matrix<T> a) 
{
	auto f1 = boost::bind(apply, f, a);
	return f1(f,a);
}

int main () 
{
	Matrix<int> m(5);
	for (int i = 0; i < m.size(); i++) {
		m[i] = i;
	}

	cout << m << endl;
	Matrix<int> n = Apply(Triple, m);
	cout << n << endl;

	//m.apply(triple);
	//cout << m << endl;

	//n = Numeric_lib::apply(TripleO(), m);
	//cout << n << endl;
	//m.apply(tripleO());
	//cout << m << endl;
}
