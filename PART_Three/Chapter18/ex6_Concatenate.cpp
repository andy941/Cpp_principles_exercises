#include "../std_lib_facilities.h"


string cat_dot(const string& s1, const string& s2, const string& sep) {
	return s1 + sep + s2;
}

int main() 
{
	cout << cat_dot("My Name is", " Andrea", ":") << endl;

	return 0;
}

