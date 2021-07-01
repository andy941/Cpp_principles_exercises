
#include "../std_lib_facilities.h"

class Link {
	public:
		string value;

		Link(int& n, Link* f = nullptr, Link* s = nullptr, Link* t = nullptr)
			: nd{n}, pfirst{f}, psecond{s}, pthird{t} { }

		Link* first() const { return pfirst; }
		Link* second() const { return psecond; }
		Link* third() const { return pthird; }
		int node() const { return nd; }

		void set_first(Link* p) { pfirst = p; };
		void set_second(Link* p) { psecond = p; };
		void set_third(Link* p) { pthird = p; };

	private:
		int nd;
		Link* pfirst;
		Link* psecond;
		Link* pthird;
};



