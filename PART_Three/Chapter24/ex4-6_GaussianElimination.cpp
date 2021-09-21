#include "../std_lib_facilities.h"
#include "Matrix/Matrix.h"
#include "Matrix/MatrixIO.h"
//#include <stdio.h>
#include <random>
#include <functional>

using namespace Numeric_lib;
using namespace std;

typedef Numeric_lib::Matrix<double, 2> _Matrix;
typedef Numeric_lib::Matrix<double, 1> _Vector;

class Elim_failure : runtime_error
{
	public:
		Elim_failure(Index n)
			:runtime_error("Elimination failure at index " + to_string(n)) { }
};

class Back_subst_failure : runtime_error
{ 
	public:
		Back_subst_failure(Index n)
			:runtime_error("Back sub failure at index " + to_string(n)) { }
};

_Vector operator*(const _Matrix& m, const _Vector& u)
{
	const Index n = m.dim1();
	_Vector v(n);
	//for (Index i = 0; i<n; ++i) v(i) = dot_product(m[i],u);
	for (Index i = 0; i<n; ++i) {
		double sum = 0;
		for (Index j = 0; j<n; ++j) {
			sum += m[i][j]*u[j];
		}
		v(i) = sum;
	}
	return v;
}

void classical_elimination(_Matrix& A, _Vector& b)
{
	const Index n = A.dim1();

	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (Index j = 0; j<n-1; ++j) {
		const double pivot = A(j,j);
		if (pivot == 0) throw Elim_failure(j);

		// fill zeros into each element under the diagonal of the ith row:
		for (Index i = j+1; i<n; ++i) {
			const double mult = A(i,j) / pivot;

			//A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			for (Index z = j; z<A[i].size(); ++z) {
				A[i][z] = A[j][z] * -mult + A[i][z];
			}

			b(i) -= mult*b(j);       // make the corresponding change to b
		}
	}
}

_Vector back_substitution(const _Matrix& A, const _Vector& b)
{
	const Index n = A.dim1();
	_Vector x(n);

	for (Index i = n-1; i>= 0; --i) {

		Row<double> subA = A[i].slice(i+1);
		Row<double> subB = x.slice(i+1);
		double sum = 0;
		for (Index i = 0; i<subA.size(); ++i) {
			sum += subA[i]*subB[i];
		}
		//double s = b(i)-dot_product(A[i].slice(i+1),x.slice(i+1));
		double s = b(i)-sum;

		if (double m = A(i,i))
			x(i) = s/m;
		else
			throw Back_subst_failure(i);
	}

	return x;
}
_Vector classical_gaussian_elimination(_Matrix A, _Vector b)
{
	classical_elimination(A, b);
	return back_substitution(A, b);
}


void elim_with_partial_pivot(_Matrix& A, _Vector& b)
{
	const Index n = A.dim1();

	for (Index j = 0; j<n; ++j) {
		Index pivot_row = j;

		// look for a suitable pivot:
		for (Index k = j+1; k<n; ++k)
			if (abs(A(k,j)) > abs(A(pivot_row,j))) pivot_row = k;

		// swap the rows if we found a better pivot:
		if (pivot_row!=j) {
			A.swap_rows(j,pivot_row);
			std::swap(b(j), b(pivot_row));
		}

		// elimination:
		for (Index i = j+1; i<n; ++i) {
			const double pivot = A(j,j);
			if (pivot==0) error("can't solve: pivot==0");
			const double mult = A(i,j)/pivot;
			//A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			for (Index z = j; z<A[i].size(); ++z) {
				A[i][z] = A[j][z] * -mult + A[i][z];
			}
			b(i) -= mult*b(j);
		}
	}
}

_Vector partial_pivot_elimination(_Matrix A, _Vector b)
{
	elim_with_partial_pivot(A, b);
	return back_substitution(A, b);
}

_Vector random_vector(Index n)
{
	_Vector v(n);
	std::default_random_engine ran{};                        // generates integers
	uniform_real_distribution<> ureal {0,10};   // maps ints into doubles
	// in [0:max)

	for (Index i = 0; i < n; ++i)
		v(i) = ureal(ran);

	return v;
}

_Matrix random_matrix(Index n)
{
	_Matrix v(n, n);
	std::default_random_engine ran{};                        // generates integers
	uniform_real_distribution<> ureal {0,10};   // maps ints into doubles

	for (Index i = 0; i < v.dim1(); i++) {
		for (Index j = 0; j < v.dim2(); j++) {
			v[i][j] = ureal(ran);
		}
	}

	return v;
}

void solve_random_system(Index n)
{
	_Matrix A = random_matrix(n);         // see §24.7
	_Vector b = random_vector(n);

	cout << "A = " << A << '\n';
	cout << "b = " << b << '\n';

	try {
		_Vector x = classical_gaussian_elimination(A, b);
		cout << "classical elim solution is x = " << x << '\n';
		_Vector v = A*x;
		cout << " A*x = " << v << '\n';
	}
	catch(const exception& e) {
		cerr << e.what() << '\n';
	}
}

int main () 
{
	solve_random_system(5);

	_Matrix A(2,2);
	_Vector b(2);
	A(0,0) = 0; 
	A(0,1) = 1; 
	A(1,0) = 1; 
	A(1,1) = 0; 
	b(0) = 5; 
	b(1) = 6; 
	cout << "A = " << A << '\n';
	cout << "b = " << b << '\n';

	//_Vector x = classical_gaussian_elimination(A, b); // Elim_failure
	try {
		_Vector x = partial_pivot_elimination(A, b);
		cout << "partial pivot elim solution is x = " << x << '\n';
		_Vector v = A*x;
		cout << " A*x = " << v << '\n';
	}
	catch(const exception& e) {
		cerr << e.what() << '\n';
	}

}
