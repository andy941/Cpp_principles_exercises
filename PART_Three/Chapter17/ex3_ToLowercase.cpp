#include "../std_lib_facilities.h"

/*https://stackoverflow.com/questions/25821178/convert-lowercase-to-uppercase-using-ascii
 * This is very elegant solution, I was trying to find something similar to avoid
 * using the tolower() function in the stdlib and I stumble upon this elegant solution.
 * I was thinking about the ASCII table and how to convert the chars in ints from the table and
 * do some operations on them but is actually much easier: you can just flip the third left-most
 * bit (or more precisely bit number 5, from the least-significant) 
 * to convert the char between uppercase [1] or lowercase [0].
 *
 * str[i] ^=0x20
 *
 *				Letter	ASCII Code	Binary	Letter	ASCII Code	Binary
 * 				a	097	01100001			A	065	01000001
 * 				b	098	01100010			B	066	01000010
 * 				c	099	01100011			C	067	01000011
 * 				d	100	01100100			D	068	01000100
 * 				e	101	01100101			E	069	01000101
 * 				f	102	01100110			F	070	01000110
 * 				g	103	01100111			G	071	01000111
 * 				h	104	01101000			H	072	01001000
 * 				i	105	01101001			I	073	01001001
 * 				j	106	01101010			J	074	01001010
 * 				k	107	01101011			K	075	01001011
 * 				l	108	01101100			L	076	01001100
 * 				m	109	01101101			M	077	01001101
 * 				n	110	01101110			N	078	01001110
 * 				o	111	01101111			O	079	01001111
 * 				p	112	01110000			P	080	01010000
 * 				q	113	01110001			Q	081	01010001
 * 				r	114	01110010			R	082	01010010
 * 				s	115	01110011			S	083	01010011
 * 				t	116	01110100			T	084	01010100
 * 				u	117	01110101			U	085	01010101
 * 				v	118	01110110			V	086	01010110
 * 				w	119	01110111			W	087	01010111
 * 				x	120	01111000			X	088	01011000
 * 				y	121	01111001			Y	089	01011001
 * 				z	122	01111010			Z	090	01011010
 *					      ^							  ^
 *
 * to be sure to apply this method only to the uppercase letters it has to be checked that the 
 * int value is in the range [65,90].
 * 
 *
*/

void to_lower(char* s)
{
	while (*s) {
		if (*s > 64 && *s < 91) *s ^= 0x20;
		s++;
	}
}

int main() 
{
	char cstring[] {"Hello World!"};

	cout << cstring << '\n';
	to_lower(cstring);
	cout << cstring << '\n';
}


