
#include "../std_lib_facilities.h"
#include "Matrix/Matrix.h"
#include "Matrix/MatrixIO.h"
#include <complex>

using namespace Numeric_lib;

int main () 
{
	// cerr << "char size:\t" << sizeof(char) << endl <<
	// 	"short size:\t" << sizeof(short) << endl <<
	// 	"int size:\t" << sizeof(int) << endl <<
	// 	"long size:\t" << sizeof(long) << endl <<
	// 	"float size:\t" << sizeof(float) << endl <<
	// 	"double size:\t" << sizeof(double) << endl <<
	// 	"int* size:\t" << sizeof(int*) << endl <<
	// 	"double* size:\t" << sizeof(double*) << endl << 
	// 	"Matrix int 10 size:\t" << sizeof(Matrix<int>(10)) << endl <<
	// 	"Matrix int 100 size:\t" << sizeof(Matrix<int>(100)) << endl <<
	// 	"Matrix double 10 size:\t" << sizeof(Matrix<double>(10)) << endl <<
	// 	"Matrix int,2 10,10 size:\t" << sizeof(Matrix<int,2>(10,10)) << endl <<
	// 	"Matrix int,3 10,10,10 size:\t" << sizeof(Matrix<int,3>(10,10,10)) << endl <<
	// 	endl;
	// Matrix<int> a(10);
	// Matrix<int> b(100);
	// Matrix<double> c(10);
	// Matrix<int,2> d(10,10);
	// Matrix<int,3> e(10,10,10);
	// cerr << a.size() << endl;
	// cerr << b.size() << endl;
	// cerr << c.size() << endl;
	// cerr << d.size() << endl;
	// cerr << e.size() << endl;
	
	// while (true) {
	// 	cout << "Insert an int: " << endl;
	// 	long long int x = 0;
	// 	cin >> x;
	// 	if (cin.fail()) {
	// 		cin.clear();
	// 		cin.ignore(1000, '\n');
	// 		cerr << "Bad input, try an integer" << endl;
	// 		continue;
	// 	}
	// 	double d = sqrt(x);
	// 	if (errno != EDOM) cout << d << endl;
	// 	else cerr << "No square root possible for this value" << endl;
	// }
	
	// Matrix<double> m(10);
	// cerr << "Please insert 10 doubles: " << endl;
	// for (int i = 0; i < 10; i++) {
	// 	double n = 0;
	// 	cin >> n;
	// 	m[i] = n;
	// }
	// cout << m << endl;
	
	// cerr << "Please insert two integer values for the rows and columns" << endl;
	// int m,n;
	// cin >> m >> n;
	// Matrix<int,2> mult(m,n);
	// for (int i = 0; i < m; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		mult[i][j] = i*j;
	// 	}
	// }
	// cout << mult << endl;
	
	// Matrix<complex<double>> m(10);
	// cerr << "Please insert 10 complex doubles: " << endl;
	// for (int i = 0; i < 10; i++) {
	// 	complex<double> n = 0;
	// 	cin >> n;
	// 	m[i] = n;
	// }
	// cout << m << endl;
	// complex<double> sum = 0;
	// for (int i = 0; i < m.size(); i++) {
	// 	sum += m[i];
	// }
	// cout << "SUM = " << sum << endl;
}
