#include "../std_lib_facilities.h"
using namespace std;

	template<class RAIter, class T> bool alg(RAIter b, RAIter e, T t)
{
	if (b==e) return true;	// Left this error on purpose to trigger test

	if (t > *(e-1)) return false;
	if (t < *b) return false;

	RAIter m = b + (e-b)/2;
	while (b <= e) {
		if (t == *m) return true;
		if (t <= *m) e = m-1;
		if (t >= *m) b = m+1;
		m = b + (e-b)/2;
	}
	return false;
}

struct Test {
	string label {""};
	int val {0};
	vector<int> seq {};
	bool res {false};
	Test() = default;
};

istream& operator>>(istream& is, Test& t)
{   
	char r1;
	char r2;
	char l1;
	char l2;
	is >> l1 >> t.label >> t.val >> l2;
	if (l1 != '{' || l2 != '{') {
		is.clear(std::ios::failbit);
		return is;
	}

	for ( int i; is >> i;) {
		t.seq.push_back(i);
	}
	is.clear();

	is >> r1 >> t.res >> r2;
	if (r1 != '}' || r2 != '}') {
		is.clear(std::ios::failbit);
		return is;
	}

	return is;
}

int test_all(istream& is)
{
	int error_count = 0;
	for (Test t; is>>t; t = {}) {
		bool r = alg(t.seq.begin(), t.seq.end(), t.val);
		if (r !=t.res) {
			cout << "failure: test " << t.label
				<< " binary_search: "
				<< t.seq.size() << " elements, val==" << t.val
				<< " –> " << t.res << '\n';
		  ++error_count;
		}

	}

	return error_count;
}

int main () 
{
    ifstream ifs {"tests.txt"};
	if (!ifs) return 1;
	int errors = test_all(ifs);
	cout << "number of errors: " << errors << "\n";
}
