#include "../std_lib_facilities.h"

int ga[] {1,2,4,8,16,32,64,128,256,512};

void print_array(ostream& os, int* a, int n)
{
	for (int i = 0; i < n; ++i) {
		os << a[i] << ' ';
	}
}

void f(int* a, int n)
{
	int la[n];
	copy(ga, ga+n, la);
	print_array(cout, la, n);
	cout << endl;
	int* p = new int[n];
	copy(a, a+n, p);
	print_array(cout, p, n);
	cout << endl;
	delete[] p;
}


int main() 
{
	f(ga,10);

	int aa[] {1,2,6,24,120,720,5040,40320,362880,3628800};
	f(aa,10);

	return 0;
}
