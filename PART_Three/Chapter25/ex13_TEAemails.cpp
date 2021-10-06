
#include "../std_lib_facilities.h"
using namespace std;

void encipher(
          const unsigned int *const v,
          unsigned int *const w,
          const unsigned int * const k)
{
          static_assert(sizeof(int)==4,"size of int wrong for TEA");

          unsigned int y = v[0];
          unsigned int z = v[1];
          unsigned int sum = 0;
          const unsigned int delta = 0x9E3779B9;

          for (unsigned int n = 32; n-->0; ) {
                    y += (z<<4 ^ z>>5) + z^sum + k[sum&3];
                    sum += delta;
                    z += (y<<4 ^ y>>5) + y^sum + k[sum>>11 & 3];
          }
          w[0]=y;
          w[1]=z;
}
void decipher(
          const unsigned int *const v,
          unsigned int *const w,
          const unsigned int * const k)
{
          static_assert(sizeof(int)==4,"size of int wrong for TEA");

          unsigned int y = v[0];
          unsigned int z = v[1];
          unsigned int sum = 0xC6EF3720;
          const unsigned int delta = 0x9E3779B9;

          // sum = delta<<5, in general sum = delta * n
          for (unsigned int n = 32; n-- > 0; ) {
                    z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
                    sum -= delta;
                    y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
          }
          w[0]=y;
          w[1]=z;
}

void email_encrypt(string infile, string outfile, string key)
{
    const int nchar = 2*sizeof(int);        // 64 bits
    const int kchar = 2*nchar;                   // 128 bits

    string op;
    while (key.size()<kchar) key += '0';    // pad key
    ifstream inf(infile);
    ofstream outf(outfile);
    if (!inf) error("bad file name");

	const unsigned int* k =
	    reinterpret_cast<const unsigned int*>(key.data());

    unsigned int outptr[2];
    char inbuf[nchar];
    unsigned int* inptr = reinterpret_cast<unsigned int*>(inbuf);
    int count = 0;

    while (inf.get(inbuf[count])) {
              outf << hex;                               // use hexadecimal output
              if (++count == nchar) {
                        encipher(inptr,outptr,k);
                        // pad with leading zeros:
                        outf << setw(8) << setfill('0') << outptr[0] << ' '
                                  << setw(8) << setfill('0') << outptr[1] << ' ';
                        count = 0;
              }
    }

    if (count) {  // pad
              while(count != nchar) inbuf[count++] = '0';
              encipher(inptr,outptr,k);
              outf << outptr[0] << ' ' << outptr[1] << ' ';
    }
		  
}

void email_decrypt(string infile, string outfile, string key)
{

	const int nchar = 2*sizeof(int);        // 64 bits
	const int kchar = 2*nchar;                   // 128 bits

	string op;
	while (key.size()<kchar) key += '0';    // pad key
	ifstream inf(infile);
	ofstream outf(outfile);
	if (!inf) error("bad file name");

	const unsigned int* k =
		reinterpret_cast<const unsigned int*>(key.data());

	unsigned int inptr[2];
	char outbuf[nchar+1];
	outbuf[nchar]=0;   // terminator
	unsigned int* outptr = reinterpret_cast<unsigned int*>(outbuf);
	inf.setf(ios_base::hex ,ios_base::basefield);      // use hexadecimal input

	while (inf>>inptr[0]>>inptr[1]) {
		decipher(inptr,outptr,k);
		outf<<outbuf;
		cout<<outbuf;
	}
}

int main()           // sender
{
	while (true) {

		string answer;
		char c;
		cout << "Type [E] for encryption and [D] for decryption. [q] to quit: ";
		cin >> (c);
		if (c == 'q') break; 
		else cin.putback(c);
		cin >> answer;
		cout << endl;

		if (answer == "E") {
			string infile, outfile, key;
			cout << "File to encrypt: ";
			cin >> infile;
			cout << endl;
			cout << "Out file: ";
			cin >> outfile;
			cout << endl;
			cout << "Key for encryption: ";
			cin >> key;
			cout << endl;
			email_encrypt(infile, outfile, key);
		}

		if (answer == "D") {
			string infile, outfile, key;
			cout << "File to decrypt: ";
			cin >> infile;
			cout << endl;
			cout << "Out file: ";
			cin >> outfile;
			cout << endl;
			cout << "Key for decryption: ";
			cin >> key;
			cout << endl;
			email_decrypt(infile, outfile, key);
		}
	}
}
