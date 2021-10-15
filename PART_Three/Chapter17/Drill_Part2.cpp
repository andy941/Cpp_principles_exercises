#include "../std_lib_facilities.h"
#include <algorithm>

void print_array10(ostream& os, int* a)
{
	for (int i = 0; i < 10; i++) {
		os << a[i] << '\n';
	}
}

void print_vector(ostream& os, vector<int>& a)
{
	for (int i = 0; i < 10; i++) {
		os << a[i] << '\n';
	}
}

int main() 
{
	int v1 {7};
	int* p1 = &v1;

	int* p2 = new int[7] {1,2,4,8,16,32,64};
	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	cout << p1 << " points to " << *p1 << endl;
	cout << p2 << " points to " << *p2 << endl;

	delete[] p2;

	// Array
	p1 = new int[10] {1,2,4,8,16,32,64,128,256,512};
	p2 = new int[10];

	for (int i = 0; i < 10; i++) {
		p2[i] = p1[i];
	}

	print_array10(cerr, p1);
	print_array10(cerr, p2);
	
	// Vector
	vector<int> vec1 {1,2,4,8,16,32,64,128,256,512};
	vector<int> vec2 (10);

	vec2 = vec1;

	print_vector(cerr, vec1);
	print_vector(cerr, vec2);
}

