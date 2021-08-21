#include "../std_lib_facilities.h"

/*
 * I supposed the vector<Purchase> means that the entry per buyer
 * should be unique and the purchase vector just hold all of the Purchases 
 * of one buyer. I suppose... but it's really not clear.
 * It definetely makes it more complicated but it makes more sense.
 */

struct Purchase 
{
	string name {""};
	int units {0};
	double unit_price {0};

	explicit Purchase() = default;
	//Purchase (string name, int units, double unit_price) :name{name}, units{units}, unit_price{unit_price} {  };
	double value() { return unit_price*units; }
};

istream& operator>>(istream& is, Purchase& p)
{
	char comma = ',';
	char c;
	string name;
	double price;
	int units;


	while (is.get(c)) {	
		if (c == ',') break;
		if (isalpha(c) || c == ' ') name.push_back(c);
	}
	p.name = name;

	is >> price >> comma >> units;
	p.unit_price = price;
	p.units = units;

	if (comma != ',') error("bad format, not CSV");
	return is;
}

ostream& operator<<(ostream& os, Purchase& p)
{
	os << p.name << ',' << p.unit_price << ',' << p.units;
	return os;
}

struct Order
{
	string name = "";
	string address = "";
	vector<Purchase> purchases {  };
	
	explicit Order() = default;
	Order(string n, string a, Purchase p) :name{n}, address{a}, purchases{p} {  };

	double total_value()
	{
		double result = accumulate(purchases.begin(), purchases.end(), 0.0, 
				[&](double r, Purchase p) { return r += p.value(); });
		return result;
	}
};

istream& operator>>(istream& is, Order& o)
{
	char c;
	string n;
	string a;
	Purchase p;

	while (is.get(c)) {	
		if (c == ',') break;
		if (isalpha(c) || c == ' ') n.push_back(c);
	}
	o.name = n;

	while (is.get(c)) {	
		if (c == ',') break;
		if (isalpha(c) || c == ' ') a.push_back(c);
	}

	o.address = a;

	is >> p;
	o.purchases = { p };

	return is;
}

ostream& operator<<(ostream& os, Order& o)
{
	for (auto& x : o.purchases) {
		os << o.name << ',' << o.address << ',' << x << '\n';
	}
	return os;
}

template<template<typename> class C> 
void read_orders(C<Order>& v, string file)
{
	ifstream ifs { file };
	if (!ifs) error("file not found");

	string s;
	typename C<Order>::iterator it;

	for (Order o; ifs >> o;) {
		s = o.name;
		it = find_if(v.begin(), v.end(), 
				[&](Order oo) { return oo.name == s; });
		if (it == v.end()) v.push_back(o);
		else {
			it->purchases.push_back(o.purchases[0]);
		}
	}
}
//void read_orders(vector<Order>& v, string file)
//{
//	ifstream ifs { file };
//	if (!ifs) error("file not found");
//	string s;
//	vector<Order>::iterator it;
//
//	for (Order o; ifs >> o;) {
//		s = o.name;
//		it = find_if(v.begin(), v.end(), 
//				[&](Order oo) { return oo.name == s; });
//		if (it == v.end()) v.push_back(o);
//		else {
//			it->purchases.push_back(o.purchases[0]);
//		}
//	}
//}

template<template<typename> class C> 
void write_orders(C<Order>& v, string file)
{
	ofstream ofs { file };
	if (!ofs) error("Can't write to file...");
	for (Order& x : v) {
		ofs << x;
	}
}

int main() 
{
	// Vector version
	vector<Order> v {};
	list<Order> l {};
	ofstream ofs { "merge_orders.csv" };
	ostream_iterator<Order> oo { ofs, ""};

	// Vector
	read_orders(v, "orders_1.csv");
	for (Order& x : v) cout << x;
	cout << endl;
	sort(v.begin(), v.end(), 
			[&](Order& o1, Order& o2) { return o1.name < o2.name; });
	for (Order& x : v) cout << x;
	cout << endl;
	write_orders(v, "sorted_orders_1.csv");

	// List
	read_orders(l, "orders_2.csv");
	for (Order& x : l) cout << x;
	cout << endl;
	l.sort([&](Order& o1, Order& o2) { return o1.address < o2.address; });
	for (Order& x : l) cout << x;
	cout << endl;
	write_orders(l, "sorted_orders_2.csv");

	// Merge
	vector<Order> m(v.size() + l.size());
	l.sort([&](Order& o1, Order& o2) { return o1.name < o2.name; });	// need same rules for sorting for std::merge()
	merge(v.begin(), v.end(), l.begin(), l.end(), m.begin(),
		[&](const Order& o1, const Order& o2) { return o1.name < o2.name; }	);
	write_orders(m, "merge_orders.csv");

	// Sum ex10
	double result = accumulate(m.begin(), m.end(), 0.0, 
			[&] (double r, Order& o) { return r += o.total_value(); });
	cout << "The total amount of purchases is $" << result << endl;
	
}



