#include "../std_lib_facilities.h"

int main()
{
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open input file ",iname);

	// open an ostream for binary output to a file:
	cout << "Please enter output file name\n";
	string oname;
	cin >> oname;
	ofstream ofs {oname,ios_base::binary};        // note: stream mode
	// binary tells the stream not to try anything clever with the bytes
	if (!ofs) error("can't open output file ",oname);

	char x;
	while (ifs.get(x)) { 
	// write to binary file:
		ofs.write(as_bytes(x),sizeof(char));         // note: writing bytes
	}
	return 0;
}
