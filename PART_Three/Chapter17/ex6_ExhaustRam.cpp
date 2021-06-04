#include "../std_lib_facilities.h"

int main() 
{
	bool* p= nullptr;
	unsigned long long int i = 0;

	while(true) {
		try {
			p = new bool[1024*1000*i];					// 1 megabytes
			delete[] p;
			std::cout << "Size of free RAM temporary: " << i/1024.0 << "Gb"<< endl;
			i++;
		}
		catch (std::bad_alloc& e) {			// This exception should be thrown by any operating system in these conditions
			std::cout << "Size of free RAM: " << i/1024.0 << "Gb"<< endl;
			return 0;
		}
		catch (...) {
			std::cout << "Size of free RAM: " << i << "Gb? (Maybe..)"<< endl;
			return 0;
		}
	}
}





