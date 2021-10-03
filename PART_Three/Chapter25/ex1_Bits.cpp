
#include "../std_lib_facilities.h"

template<class T>
void print(T & num)
{
	cout <<  dec << num << '\t' <<
		setfill('0') << setw(8) << hex << num << '\n' <<
		bitset<sizeof(num)*8>(num) << '\n';
}

template<class T>
void explore_bits( T a )
{
	a = 0xffffffff;
	cerr << "size in bytes = " << sizeof(a) << endl;
	cerr << endl;
	cerr << "All bits set to 1" << endl;
	print(a);
	cerr << endl;
	a = 0x00000001;
	cerr << "Only least significant bit set" << endl;
	print(a);
	cerr << endl;
	a = 0x80000000;
	cerr << "Only most significant bit set" << endl;
	print(a);
	cerr << endl;
	a = 0x000000ff;
	cerr << "Only lowest byte set" << endl;
	print(a);
	cerr << endl;
	a = 0xff000000;
	cerr << "Only highest byte set" << endl;
	print(a);
	cerr << endl;
	a = 0x55555555;
	cerr << "Every second bit set (starting 1)" << endl;
	print(a);
	cerr << endl;
	a = 0xaaaaaaaa;
	cerr << "Every second bit set (starting 0)" << endl;
	print(a);
	cout << endl;
	a = 0x00ff00ff;
	cerr << "Every second byte set (starting 1)" << endl;
	print(a);
	cout << endl;
	a = 0xff00ff00;
	cerr << "Every second byte set (starting 0)" << endl;
	print(a);
	cout << endl;
	cerr << "Every 2 bits set (starting 1)" << endl;
	a = 0x00ff00ff;
	a ^= a<<4;
	a ^= a<<2;
	print(a);
	cout << endl;
	a = ~a;
	cerr << "Every second byte set (starting 0)" << endl;
	print(a);
	cout << endl;
}


using namespace std;
int main () 
{
	unsigned int ui = 0; 
	signed int si = 0; 

	cerr << "Unsigned int ......" << endl;
	explore_bits(ui);
	cout <<endl;
	cerr << "Signed int ......" << endl;
	explore_bits(si);
	cout <<endl;
}
