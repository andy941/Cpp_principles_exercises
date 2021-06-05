#include "../std_lib_facilities.h"

/*
 * if the array risks to overflow, I will copy the existing string on chars
 * in a bigger array and continue on reading.
*/


int main() 
{
	int size = 10;
	char* str = new char[size+1]; 
	char* tmp = nullptr; 

	while (true) {

		for (int i = size-10; i < size; i++) {
			cin >> str[i];
			if (str[i] == '!') { 
				cout << str << endl;
				return 0;
			}
		}

		// Overflowing! allocate more space

		size += 10;

		tmp = new char[size];

		for (int i = 0; i < size; i++) {
			tmp[i] = str[i];
		}

		delete[] str;

		str = new char[size];

		for (int i = 0; i < size; i++) {
			str[i] = tmp[i];
		}

		cout << "STR: " << str << '\n' << "TMP: " << tmp << '\n' << size << '\n';

		delete[] tmp;

	}
	return 1;
}





