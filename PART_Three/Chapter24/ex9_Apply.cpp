#include "../std_lib_facilities.h"
#include "ex1-2_Triple.cpp"
#include <boost/bind/bind.hpp>

/*
 * I am not happy with this. It kind of barely work but there seems to be a better way.
 * If only I could deduce the return type from the function without calling it it would better.
 * In this case the return type is always the same (int), no matter the arguments.
 */

using namespace Numeric_lib;
using namespace std;


int TripleD(const double& n) 
{
	return n*3;
}

template<typename F, typename M>
auto Apply(F f, M x)
{ 
	Matrix<decltype(f(x[0]))> res(x.size());   
	for (int i = 0; i < x.size(); i++) {
		res.data()[i] = f(x[i]);
	}

	return xfer(res); 
}

int main () 
{
	Matrix<double> m(5);
	for (double i = 0.030; i < m.size(); i+=1.000) {
		m[i] = i;
	}

	cout << m << endl;
	auto n = Apply(TripleD, m);
	cout << n << endl;
}
