#include "../std_lib_facilities.h"
//#include "Matrix/Matrix.h"
//#include "Matrix/MatrixIO.h"
//#include <stdio.h>
#include <random>
#include <functional>

//using namespace Numeric_lib;
using namespace std;

typedef vector<vector<double>> _Matrix;
typedef vector<double> _Vector;

class Elim_failure : runtime_error
{
	public:
		Elim_failure(int n)
			:runtime_error("Elimination failure at index " + to_string(n)) { }
};

class Back_subst_failure : runtime_error
{ 
	public:
		Back_subst_failure(int n)
			:runtime_error("Back sub failure at index " + to_string(n)) { }
};

_Vector operator*(const _Matrix& m, const _Vector& u)
{
	const int n = m.size();
	_Vector v(n);
	//for (int i = 0; i<n; ++i) v(i) = dot_product(m[i],u);
	for (int i = 0; i<n; ++i) {
		double sum = 0;
		for (int j = 0; j<n; ++j) {
			sum += m[i][j]*u[j];
		}
		v[i] = sum;
	}
	return v;
}

void classical_elimination(_Matrix& A, _Vector& b)
{
	const int n = A.size();

	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (int j = 0; j<n-1; ++j) {
		const double pivot = A[j][j];
		if (pivot == 0) throw Elim_failure(j);

		// fill zeros into each element under the diagonal of the ith row:
		for (int i = j+1; i<n; ++i) {
			const double mult = A[i][j] / pivot;

			//A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			for (unsigned long int z = j; z<A[i].size(); ++z) {
				A[i][z] = A[j][z] * -mult + A[i][z];
			}

			b[i] -= mult*b[j];       // make the corresponding change to b
		}
	}
}

_Vector back_substitution(const _Matrix& A, const _Vector& b)
{
	const int n = A.size();
	_Vector x(n);

	for (int i = n-1; i>= 0; --i) {

		vector<double> subA = vector<double>(A[i].begin()+i+1, A[i].end());
		vector<double> subB = vector<double>(x.begin()+i+1, x.end());
		double sum = 0;
		for (unsigned long int i = 0; i<subA.size(); ++i) {
			sum += subA[i]*subB[i];
		}
		//double s = b(i)-dot_product(A[i].slice(i+1),x.slice(i+1));
		double s = b[i]-sum;

		if (double m = A[i][i])
			x[i] = s/m;
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
	const int n = A.size();

	for (int j = 0; j<n; ++j) {
		int pivot_row = j;

		// look for a suitable pivot:
		for (int k = j+1; k<n; ++k)
			if (abs(A[k][j]) > abs(A[pivot_row][j])) pivot_row = k;

		// swap the rows if we found a better pivot:
		if (pivot_row!=j) {
			//A.swap_rows(j,pivot_row);
			auto tmpA = A[j];
			A[j] = A[pivot_row];
			A[pivot_row] = tmpA;
			//std::swap(b(j), b(pivot_row));
			auto tmpb = b[j];
			b[j] = b[pivot_row];
			b[pivot_row] = tmpb;
		}

		// elimination:
		for (int i = j+1; i<n; ++i) {
			const double pivot = A[j][j];
			if (pivot==0) error("can't solve: pivot==0");
			const double mult = A[i][j]/pivot;
			//A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			for (unsigned long int z = j; z<A[i].size(); ++z) {
				A[i][z] = A[j][z] * -mult + A[i][z];
			}
			b[i] -= mult*b[j];
		}
	}
}

_Vector partial_pivot_elimination(_Matrix A, _Vector b)
{
	elim_with_partial_pivot(A, b);
	return back_substitution(A, b);
}

_Vector random_vector(int n)
{
	_Vector v(n);
	std::default_random_engine ran{};                        // generates integers
	uniform_real_distribution<> ureal {0,10};   // maps ints into doubles
	// in [0:max)

	for (int i = 0; i < n; ++i)
		v[i] = ureal(ran);

	return v;
}

_Matrix random_matrix(int n)
{
	_Matrix v(n,vector<double>(n));

	std::default_random_engine ran{};                        // generates integers
	uniform_real_distribution<> ureal {0,10};   // maps ints into doubles

	for (unsigned long int i = 0; i < v.size(); i++) {
		for (unsigned long int j = 0; j < v[0].size(); j++) {
			v[i][j] = ureal(ran);
		}
	}

	return v;
}

ostream& operator<<(ostream& os, _Matrix& m) 
{
	cout << '{' << endl;
	for (auto x : m) {
		cout << '{' << '\t';
		for (auto y : x) {
			cout << y << '\t'; 
		}
		cout << '}' << endl;
	}
	cout << '}' << endl;
	return os;
}

ostream& operator<<(ostream& os, _Vector& m) 
{
	cout << "{\t";
	for (auto x : m) {
		cout << x << '\t'; 
	}
	cout << '}' << endl;
	return os;
}

void solve_random_system(int n)
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

	_Matrix A(2, vector<double>(2));
	_Vector b(2);
	A[0][0] = 0; 
	A[0][1] = 1; 
	A[1][0] = 1; 
	A[1][1] = 0; 
	b[0] = 5; 
	b[1] = 6; 
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

