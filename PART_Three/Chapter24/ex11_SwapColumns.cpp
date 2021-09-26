
#include "../std_lib_facilities.h"
#include "Matrix/Matrix.h"
#include "Matrix/MatrixIO.h"

using namespace Numeric_lib;
using namespace std;

template<class T>
void Matrix<T,2>::SwapColumns(Index i, Index j) 
{
	if (i == j) return;
	for (Index ii = 0; ii < (*this).dim1(); ii++) {
		swap((*this)(ii,i),(*this)(ii,j));
	}
}

int main () 
{
	Matrix<int, 2> m(10,10);
	for (int i = 0; i < m.dim1(); i++) {
		for (int j = 0; j < m.dim2(); j++) {
			m(i,j) = j;
		}
	}

	cout << m << endl;
	m.SwapColumns(3,4);
	m.SwapColumns(0,9);
	cout << m << endl;
}
