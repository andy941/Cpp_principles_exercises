#include "../std_lib_facilities.h"
#include <exception>
#include <type_traits>

/*
 * The function sums the two vectors member-wise for the whole length of the first
 * vector. if the firs vector is longer than the second it just adds 0 for the missing
 * values.
*/

template <typename T, typename U>
T f(const vector<T>& vt, const vector<U>& vu)
{
	//typename std::common_type<T,U>::type sum {0};
	T sum = 0;

	for (int i = 0; i < vt.size(); i++) {
		try { sum = sum + (vt[i] * vu[i]); }
		catch ( const std::out_of_range& e) {  };		// Do nothing, could be resolved with no try catch and explicit range checking.
	}

	return sum;
}

//int main() 
//{
//	vector<int> v1 { 1,1 };
//	vector<int>	v2 { 1,1,1 };
//	vector<double>	v3 { 2.0,2.0,2.0,2.0 };
//
//	cout << f(v2,v2) << endl;
//	cout << f(v2,v1) << endl;
//	cout << f(v2,v3) << endl;
//}
