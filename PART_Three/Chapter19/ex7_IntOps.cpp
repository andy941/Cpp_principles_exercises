
#include "../std_lib_facilities.h"
#include <type_traits>
#include <concepts>
#include "ex2_ProdVec.cpp"

template<typename T> 
struct Number
{
	static_assert(std::is_arithmetic<T>::value, "The template has to be a Number");			// I looked for so long for this, is very confusing. It makes the compiler throw an error at compile time
																							// which is more readable and can't occur at runtime. can still be a char.
	T num {0};

	Number() = default;
	Number(T n) :num{n} {  };

};

// There could be an elegant way to find a common type to use as output, but this works simply
// by using the type of the left argument.
template<typename T, typename U> 
Number<T> operator+(const Number<T>& n, const Number<U>& m) { return Number<T>{n.num+m.num}; }

template<typename T, typename U> 
Number<T> operator*(const Number<T>& n, const Number<U>& m) { return Number<T>{n.num*m.num}; }

template<typename T, typename U> 
Number<T> operator/(const Number<T>& n, const Number<U>& m) { return Number<T>{n.num/m.num}; }

template<typename T> 
ostream& operator<<(ostream& os, Number<T> n) 
{ 
	os << n.num;
	return os; 
}

int main () 
{
	Number<int> a { 4 };
	Number<int> b {   };
	Number<char> c { 'c' };			// can still compile
	// Number<string> d {};			// Compile time error, very clear explanation
	Number<double> d { 5.8 };
	
	b = a+a;
	// d = d%a;						// invalid operands to binary expression, type checking seems to work;
	cout << b << endl;
	cout << c << endl;

	// Try the Vector operation implementation
	vector<Number<int>> v_int { 3, 5, 7};
	vector<Number<double>> v_double { 2.5, 6.7, 7.8};
	vector<Number<char>> v_char { 'g', 't', 'a' };
	cout << f(v_int, v_int) << endl;
	cout << f(v_double, v_int) << endl;
	cout << f(v_int, v_double) << endl;					// WARNINGS for narrowing
	cout << f(v_char, v_double) << endl;				// WARNINGS for narrowing

}

