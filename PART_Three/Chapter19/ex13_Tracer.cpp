#include "../std_lib_facilities.h"

struct Tracer 
{
	int num = 0;
	Tracer() { cerr << "Constructed Tracer num NOT SET"<< endl;  };
	Tracer(int n) : num { n } { cerr << "Constructed Tracer num " << num << endl; }
	
	Tracer& operator=(const Tracer& t) 
	{ 
		num = t.num;
		return *this;
		cerr << "Copy assignment called for Tracer num " << num << endl; 
	}

	Tracer(const Tracer& t) 
		:num{t.num}
	{ 
		cerr << "Copy Constructor called for Tracer num " << num << endl; 
	}

	~Tracer() {  cerr << "Destroyed Tracer num " << num << endl;  };
};

//int main() 
//{
//}
