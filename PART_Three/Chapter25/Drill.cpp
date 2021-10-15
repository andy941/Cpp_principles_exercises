#include "../std_lib_facilities.h"
#include <cstdint>
#include <ios>

template<class T>
void print(T & num)
{
	cout <<  dec << num << '\t' <<
		setfill('0') << setw(4) << hex << num << '\t' <<
		bitset<sizeof(num)*8>(num) << '\n';
}

using namespace std;
int main () 
{
	cout << "------ Signed int ---------------------------------" << endl;
	int v = 1; 
	for (int i = 0; i<sizeof(v)*8; ++i) { 
		cout << v << '\n'; 
		v <<=1; 
	}
	cout << "------ Signed int ---------------------------------" << endl;
	unsigned int v2 = 1; 
	for (int i = 0; i<sizeof(v)*8; ++i) { 
		cout << v2 << '\n'; 
		v2 <<=1; 
	}

	cout << "------ Binary from hex ----------------------------" << endl;
	short unsigned int a = 0xffff;
	cerr << "size of a = " << sizeof(a) << endl;
	cerr << endl;
	cerr << "All bits set to 1" << endl;
	print(a);
	cerr << endl;
	a = 0x0001;
	cerr << "Only least significant bit set" << endl;
	print(a);
	cerr << endl;
	a = 0x8000;
	cerr << "Only most significant bit set" << endl;
	print(a);
	cerr << endl;
	a = 0x00ff;
	cerr << "Only lowest byte set" << endl;
	print(a);
	cerr << endl;
	a = 0xff00;
	cerr << "Only highest byte set" << endl;
	print(a);
	cerr << endl;
	a = 0x5555;
	cerr << "Every second bit set (starting 1)" << endl;
	print(a);
	cerr << endl;
	a = 0xaaaa;
	cerr << "Every second bit set (starting 0)" << endl;
	print(a);
	cout << endl;

	cout << "------ Binary operations only ---------------------" << endl;
	a = 0;
	int bits = sizeof(a)*8;
	cerr << "size of a = " << sizeof(a) << endl;
	cerr << endl;
	a = ~a;
	cerr << "All bits set to 1" << endl;
	print(a);
	cerr << endl;
	a = 1;
	cerr << "Only least significant bit set" << endl;
	print(a);
	cerr << endl;
	a <<= bits-1;
	cerr << "Only most significant bit set" << endl;
	print(a);
	cerr << endl;
	a = 1;
	for (int i = 0; i < bits/2-1; i++) {
		a<<=1;  
		a ^= 1;
	}
	cerr << "Only lowest byte set" << endl;
	print(a);
	cerr << endl;
	a <<= bits/2;
	cerr << "Only highest byte set" << endl;
	print(a);
	cerr << endl;
	a = 0;
	for (int i = 0; i < bits-1; i++) {
		a<<=1;  
		if (i%2 == 0) a ^= 1;
	}

	cerr << "Every second bit set (starting 1)" << endl;
	print(a);
	cerr << endl;
	a = ~a;
	cerr << "Every second bit set (starting 0)" << endl;
	print(a);
	cout << endl;



}
