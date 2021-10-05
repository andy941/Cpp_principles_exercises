
#include "../std_lib_facilities.h"

template<class T>
void print(T & num)
{
	cout <<  dec << num << '\t' <<
		setfill('0') << setw(4) << hex << num << '\t' <<
		bitset<sizeof(num)*8>(num) << '\n';
}

struct PPN {                                       // R6000 Physical Page Number
          unsigned int PFN : 22 ;         // Page Frame Number
          int : 3 ;                                     // unused
          unsigned int CCA : 3 ;         // Cache Coherency Algorithm
          bool nonreachable : 1 ;
          bool dirty : 1 ;
          bool valid : 1 ;
          bool global : 1 ;
};

ostream& operator<<(ostream& os, PPN p)
{
	os << hex <<
		"PFN:\t" << p.PFN << '\n' <<
		"CCA:\t" << p.CCA << '\n' <<
		"non_reachable:\t" << p.nonreachable << '\n' <<
		"dirty:\t" << p.dirty << '\n' <<
		"valid:\t" << p.valid << '\n' <<
		"global:\t" << p.global << '\n';
	return os;
}

using namespace std;
int main () 
{
	cout << "------ Bitfield ---------------------------------" << endl;
	PPN p;
	p.PFN = 0xf0;
	p.CCA = 0x5;
	p.nonreachable = 0x1;
	p.global = 0x1;
	cout << p << endl;

	cout << "------ unsigned 32-bit int ----------------------" << endl;
	unsigned int pp = 0;
	print(pp);
	pp |= 0xf0 << 10;
	pp |= 0x5 << 7;
	pp |= 1 << 3;
	pp |= 1;
	print(pp);
	PPN pp_struct;
	pp_struct.PFN = pp >> 10;
	pp_struct.CCA = pp >> 7;
	pp_struct.nonreachable = pp >> 3;
	pp_struct.global = pp;
	cout << pp_struct;
	cout << endl;

	cout << "------ bitset -----------------------------------" << endl;
	bitset<sizeof(pp)*8> ppp = 0;
	cout << ppp << endl;
	ppp |= 0xf0 << 10;
	ppp |= 0x5 << 7;
	ppp.set(3,1);
	ppp.set(0,1);
	cout << ppp << endl;
	pp = ppp.to_ulong();
	pp_struct.PFN = pp >> 10;
	pp_struct.CCA = pp >> 7;
	pp_struct.nonreachable = pp >> 3;
	pp_struct.global = pp;
	cout << pp_struct;
	cout << endl;


}
