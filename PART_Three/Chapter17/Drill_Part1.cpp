#include "../std_lib_facilities.h"

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
	// With array
	int* arr_ints =  new int[10];

	for (int i = 0; i < 10; i++) {
		cout << arr_ints[i] << '\n';
	}

	print_array10(cout, arr_ints);

	for (int i = 0; i < 10; i++) {
		arr_ints[i] = 100+i;
	}

	print_array10(cout, arr_ints);

	delete[] arr_ints;

	// With vector
	vector<int> vec_ints(10); 

	for (int i = 0; i < 10; i++) {
		cout << vec_ints[i] << '\n';
	}

	print_vector(cout, vec_ints);

	for (int i = 0; i < 10; i++) {
		vec_ints[i] = 100+i;
	}

	print_vector(cout, vec_ints);
}


