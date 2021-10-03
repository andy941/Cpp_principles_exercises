#include "../std_lib_facilities.h"



int main () 
{
	for (short int i = 0; i <= 400; i++) {
		cout << dec << i << '\t' << hex << setfill('0') << setw(4)<< i << endl;
	}
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << endl;
	for (short int i = -200; i <= 200; i++) {
		cout << dec << i << '\t' << hex << setfill('0') << setw(4)<< i << endl;
	}
}
