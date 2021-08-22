
/*
 * The only way to make this work is to clone this repository:
 *		https://github.com/cortical-iv/hello_fltk.git
 *	And follow the instructions, essentially the most reliable
 *	course of action is to have all the files in the work directory
 *	and then compile each time with this:
 *
 *	g++ -w -Wall -std=c++11 <file.cpp> Graph.cpp Window.cpp GUI.cpp Simple_window.cpp `fltk-config --ldflags --use-images` -o <file.o>
 *
*/

#include "../hello_fltk/Window.h"  
#include "../hello_fltk/GUI.h"  
#include "../hello_fltk/Graph.h"
#include<numeric> 
#include<algorithm> 

using namespace Graph_lib;

// Order classes implementation -----------------------------------------------------
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

//template<template<typename> class C> 
void read_orders(vector<Order>& v, string file)
{
	ifstream ifs { file };
	if (!ifs) error("file not found");

	string s;
	typename vector<Order>::iterator it;

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

void write_orders(vector<Order>& v, string file)
{
	ofstream ofs { file };
	if (!ofs) error("vectoran't write to file...");
	for (Order& x : v) {
		ofs << x;
	}
}

// GUI implementation -----------------------------------------------------


struct Orders_window : public Graph_lib::Window {

	Orders_window(Point xy, int w, int h, const string& title);

	Button quit_button;
	In_box input_file;
	In_box output_file;
	In_box search_string;
	Out_box result;

	Menu actions_menu;
	Button actions_button;

	void quit() { hide(); };

	// Actions Menu
	void list_all_pressed();
	void find_pressed();
	void sum_pressed();

	void actions_menu_hide() { actions_menu.hide(); actions_button.show(); }
	void menu_pressed() { actions_button.hide(); actions_menu.show(); }
};

Orders_window::Orders_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Orders_window>(pw).quit();}},
	input_file{Point{50,0}, 70, 20, "Input file:"},
	output_file{Point{200,0}, 70, 20, "Output file:"},
	search_string{Point{400,0}, 70, 20, "Search:"},
	result{Point{50,40}, x_max()-230, y_max()-100, "Output:"},
	
	actions_menu{Point{x_max()-180,40}, 180, 20 ,Menu::vertical,"Actions:"},
	actions_button{Point{x_max()-180,40}, 180, 20, "Actions menu",
		[](Address, Address pw) {reference_to<Orders_window>(pw).menu_pressed();}}

{
	attach(quit_button);
	attach(input_file);
	attach(output_file);
	attach(search_string);
	attach(result);

	// Color Menu
	actions_menu.attach(new Button{Point{0,0},0,0,"List all entries",
		[](Address, Address pw) {reference_to<Orders_window>(pw).list_all_pressed();}});
	actions_menu.attach(new Button{Point{0,0},0,0,"Find customer orders",
		[](Address, Address pw) {reference_to<Orders_window>(pw).find_pressed();}});
	actions_menu.attach(new Button{Point{0,0},0,0,"Get total price\n(use search to subset for customer)",
		[](Address, Address pw) {reference_to<Orders_window>(pw).sum_pressed();}});

	attach(actions_menu);
	actions_menu.hide();
	attach(actions_button);
}

void Orders_window::list_all_pressed()
{
	const string input = input_file.get_string();
	const string output = output_file.get_string();
	const string search = search_string.get_string();

	vector<Order> v;
	ostringstream oss;

	read_orders(v, input);
	
	for (auto& x : v) oss << x;
	result.put(oss.str());
	if(output != "") write_orders(v, output);

	actions_menu_hide();

	redraw();
}
		
void Orders_window::find_pressed()
{
	const string input = input_file.get_string();
	const string output = output_file.get_string();
	const string search = search_string.get_string();

	vector<Order> v;
	vector<Order> v_sub;
	ostringstream oss;

	read_orders(v, input);
	copy_if(v.begin(), v.end(), back_inserter(v_sub),
			[&](Order o){ return o.name == search; });

	
	for (auto& x : v_sub) oss << x;
	result.put(oss.str());
	if(output != "") write_orders(v_sub, output);

	actions_menu_hide();

	redraw();
}

void Orders_window::sum_pressed()
{
	const string input = input_file.get_string();
	const string output = output_file.get_string();
	string search = search_string.get_string();

	vector<Order> v;
	double res = 0;
	ostringstream oss;

	read_orders(v, input);
	if (search!="") {
		auto it = std::find_if(v.begin(), v.end(), [&] (const Order o) { return o.name == search; });
		res = it->total_value();
	}
	else { 
		res = std::accumulate(v.begin(), v.end(), 0.0, [&](double r, Order o) { return r += o.total_value(); });
	}
	
	oss << "The total value for all orders issued by " << search << " is: " << res << '\n';
	string s = oss.str();
	result.put(s);

	actions_menu_hide();

	redraw();
}

int main()
{
	try {
		Orders_window win {Point{100,100},600,400,"lines"};
		return gui_main();
	}
	catch(exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
}





