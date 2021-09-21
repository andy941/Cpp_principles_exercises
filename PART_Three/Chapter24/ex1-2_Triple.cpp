//#include "../std_lib_facilities.h"
#include "Matrix/Matrix.h"
//#include "Matrix/Matrix11.h"
#include "Matrix/MatrixIO.h"
//#include "Matrix/MatrixIO11.h"

using namespace Numeric_lib;
using namespace std;

void triple(int& n) 
{
	n*=3;
}

int Triple(const int& n) 
{
	return n*3;
}

class tripleO
{
	public:
	void operator()(int n) {n*=3;};
};

class TripleO
{
	public:
	int operator()(int n) {return n*3;};
};

//int main () 
//{
//	Matrix<int> m(5);
//	for (int i = 0; i < m.size(); i++) {
//		m[i] = i;
//	}
//
//	cout << m << endl;
//	Matrix<int> n = Numeric_lib::apply(Triple, m);
//	cout << n << endl;
//	m.apply(triple);
//	cout << m << endl;
//
//	n = Numeric_lib::apply(TripleO(), m);
//	cout << n << endl;
//	m.apply(tripleO());
//	cout << m << endl;
//}
