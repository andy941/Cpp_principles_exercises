#include "../std_lib_facilities.h"

vector<int> gv {1,2,4,8,16,32,64,128,256,512};

void print_vector(ostream& os, vector<int> a)
{
	for (int x : a) {
		os << x << ' ';
	}
}

void f(vector<int> a)
{
	vector<int> lv(a.size());
	copy(gv.begin(), gv.end(), lv.begin());
	print_vector(cout, lv);
	cout << endl;
	vector<int> lv2 {a};
	print_vector(cout, lv2);
	cout << endl;
}

int main() 
{
	f(gv);
	vector<int> vv {1,2,6,24,120,720,5040,40320,362880,3628800};
	f(vv);

	return 0;
}

