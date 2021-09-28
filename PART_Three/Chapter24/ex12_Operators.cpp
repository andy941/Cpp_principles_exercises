
#include "../std_lib_facilities.h"
#include "Matrix/Matrix.h"
#include "Matrix/MatrixIO.h"

using namespace Numeric_lib;
using namespace std;

Matrix<double> operator*(Matrix<double,2>& m,Matrix<double>& v)
{	// Assuming right dimensions
	Matrix<double> result(m.dim1());
	for (Index i = 0; i <m.dim1(); i++) {
		result(i) = dot_product(m[i], v);
	}
	return result;
}

template<int N> 
Matrix<double,N> operator+(Matrix<double,N>& m,Matrix<double,N>& n)
{	// Assuming right dimensions
	Matrix<double,N> result { m };	// I can't see how to avoid this copy
	for (unsigned int i = 0; i <result.size(); i++) {
		result.data()[i] += n.data()[i];
	}
	return result;
}

int main () 
{
	Matrix<double, 2>m(3,4);
	for (unsigned int i = 0; i <m.size(); i++) {
		m.data()[i] = rand()%4;
	}

	Matrix<double> v(4);
	for (double i = 0; i < v.size(); i++) {
		v[i] = rand()%4;
	}

	Matrix<double, 3>c(3,2,2);
	for (unsigned int i = 0; i <c.size(); i++) {
		c.data()[i] = rand()%10;
	}

	cout << m << endl;
	cout << v << endl;
	cout << "-------------------------------------" << endl;
	cout << "m*v:" << endl;
	cout << m*v << endl;
	cout << "-------------------------------------" << endl;
	cout << "m+m:" << endl;
	cout << m+m << endl;
	cout << "c3+c3:" << endl;
	cout << "{ ";
	for (int i = 0; i < c.size(); i++) cout << ' ' << c.data()[i];
	cout << "}" << endl;
	c = c + c;
	cout << "{ ";
	for (int i = 0; i < c.size(); i++) cout << ' ' << c.data()[i];
	cout << "}" << endl;
}
