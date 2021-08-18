
#include "../std_lib_facilities.h"
#include <set>

struct Fruit
{
	string name;
	double price;
};

struct comparison 
{
	bool operator() (const Fruit* a, const Fruit* b) const { return a->price < b->price; }
};

int main() 
{
	set<Fruit*, comparison> s {  };
	s.insert(new Fruit{ "Banana", 3.59 });
	s.insert(new Fruit{ "Ananas", 4.79 });
	s.insert(new Fruit{ "Tomato", 0.19 });
	for (auto& x : s) cout << x->name << '\t' << x->price << endl;
}



