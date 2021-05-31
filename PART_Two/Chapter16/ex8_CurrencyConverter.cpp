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

using namespace Graph_lib;

//-------------------------------------------------------------------------
// From Chapter15 ex6:
vector<long int> split_val ( const string& line, const string& delim = ",")
{
	char x;
	long int val;
	vector<long int> v;
	istringstream iss { line };

	while (iss >> val) {
		v.push_back(val);
		iss >> x;
		if (x != ',') error("This doesn't seem a csv file... \n");
	}

	return v;
}

vector<string> split ( const string& line, const string& delim = ",")
{
	char x;
	vector<string> v;
	string token;
	istringstream iss { line };

	while ( iss >> x ) {

		if ( x == ',' ) {
			v.push_back(token);
			token = {};
			continue;
		}

		token.push_back(x);
	}

	v.push_back(token);

	return v;
}

//-------------------------------------------------------------------------
// Adapt the code in Chapter9/Money.cpp
class Money 
{
	long int amount {0};

	string currency {"USD"};
	vector<string> labels {"USD", "EUR", "GBP"};
	vector<vector<long int>> conv_table = {
		{100,83,73},
		{121,100,88},
		{137,113,100},
	};

	int decimal {2};

	public:
	Money() {};
	Money(long int) {};
	Money(long int, string file = "");
	void set_value(long int a, string c) { amount=a; currency=c; decimal=2;};
	long int Amount();
	string Curr() {return currency;};
	int Decimal() {return decimal;};
	void Conv(string);
};

Money::Money(long int aa, string file)
{
	string line;
	ifstream ifs {file};
	if (!ifs) error("can't open file\n");

	getline(ifs, line);
	vector<string> names = split(line); 

	vector<vector<long int>> new_table;
	while( getline(ifs, line)) {
		vector<long int> values = split_val(line, ",");
		if (values.size() != 3) {cerr << "Sorry the coordinates file seem to have "
			"more than 3 columns\n";}

		new_table.push_back(values);
	}

	conv_table = new_table;
	labels = names;
	currency = names[0];

	amount = aa;
}

long int Money::Amount()
{
	return amount;
}

void Money::Conv(string b)
{
	string a {currency};

	bool check {false};
	for (string x : labels) {if (x == b) check = true;};
	if (!check) {cerr << "Error, Currency not in database\n"; return;};

	int x;
	int y;

	for (int i; i < labels.size(); i++) {
		if (labels[i] == a) x = i;
		if (labels[i] == b) y = i;
	}

	amount = amount * conv_table[x][y];
	currency = b;
	decimal +=2;

}

//operator overloading
istream& operator>>(istream& is, Money& mon)
{
	long int aa;
	string cc;

	is >> cc >> aa;
	mon = Money(aa*100,cc);

	return is;
};

ostream& operator<<(ostream& os, Money& mon)
{
	int dec = pow(10, mon.Decimal());
	double am;

	if (mon.Amount() %(dec/10) >= 5*dec/100) am = ceil(double(mon.Amount()) / dec * 100) / 100;
	if (mon.Amount() %(dec/10) <= 5*dec/100) am = floor(double(mon.Amount()) / dec * 100) / 100;


	os << mon.Curr() << " " << am;
	return os;
};

//----------------------------------------------------------------------------------------------
struct Currency_window : Graph_lib::Window {

	Currency_window(Point xy, int w, int h, const string& title);

	private:

	Money money {0,"conversion_table.csv"};

	Button calculate_button;          // add (next_x,next_y) to lines
	Button quit_button;
	In_box amount_in;
	Out_box amount_out;

	long int from_amount,to_amount;
	string from_currency, to_currency;

	Menu from_menu;
	Button from_menu_button;

	Menu to_menu;
	Button to_menu_button;

	void next();
	void quit() { hide(); };

	// from Menu
	void from_usd_pressed() { from_currency="USD"; from_hide_menu(); }
	void from_eur_pressed() { from_currency="EUR"; from_hide_menu(); }
	void from_gbp_pressed() { from_currency="GBP"; from_hide_menu(); }

	void from_hide_menu() { from_menu.hide(); from_menu_button.show(); }
	void from_menu_pressed() { from_menu_button.hide(); from_menu.show(); }

	// to Menu
	void to_usd_pressed() { to_currency="USD"; to_hide_menu(); }
	void to_eur_pressed() { to_currency="EUR"; to_hide_menu(); }
	void to_gbp_pressed() { to_currency="GBP"; to_hide_menu(); }

	void to_hide_menu() { to_menu.hide(); to_menu_button.show(); }
	void to_menu_pressed() { to_menu_button.hide(); to_menu.show(); }

	void convert();
};

Currency_window::Currency_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	calculate_button{Point{x_max()-150,0}, 70, 20, "Convert",
		[](Address, Address pw) {reference_to<Currency_window>(pw).convert();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Currency_window>(pw).quit();}},
	amount_in{Point{x_max()-310,0}, 50, 20, "Amount in:"},
	amount_out{Point{100,0}, 100, 20, "Amount out:"},
	
	from_menu{Point{x_max()-70,40},70,20,Menu::vertical,"From Currency"},
	from_menu_button{Point{x_max()-80,30}, 80, 20, "From Currency",
		[](Address, Address pw) {reference_to<Currency_window>(pw).from_menu_pressed();}},

	to_menu{Point{x_max()-70,200},70,20,Menu::vertical,"To Currency"},
	to_menu_button{Point{x_max()-80,210}, 80, 20, "To Currency",
		[](Address, Address pw) {reference_to<Currency_window>(pw).to_menu_pressed();}}

{
	attach(calculate_button);
	attach(quit_button);
	attach(amount_in);
	attach(amount_out);

	// In Menu
	from_menu.attach(new Button{Point{0,0},0,0,"USD",
		[](Address, Address pw) {reference_to<Currency_window>(pw).from_usd_pressed();}});
	from_menu.attach(new Button{Point{0,0},0,0,"EUR",
		[](Address, Address pw) {reference_to<Currency_window>(pw).from_eur_pressed();}});
	from_menu.attach(new Button{Point{0,0},0,0,"GBP",
		[](Address, Address pw) {reference_to<Currency_window>(pw).from_gbp_pressed();}});
	attach(from_menu);
	from_menu.hide();
	attach(from_menu_button);

	// Out Menu
	to_menu.attach(new Button{Point{0,0},0,0,"USD",
		[](Address, Address pw) {reference_to<Currency_window>(pw).to_usd_pressed();}});
	to_menu.attach(new Button{Point{0,0},0,0,"EUR",
		[](Address, Address pw) {reference_to<Currency_window>(pw).to_eur_pressed();}});
	to_menu.attach(new Button{Point{0,0},0,0,"GBP",
		[](Address, Address pw) {reference_to<Currency_window>(pw).to_gbp_pressed();}});
	attach(to_menu);
	to_menu.hide();
	attach(to_menu_button);
}
		
void Currency_window::convert()
{
	money.set_value(amount_in.get_int()*100, from_currency);
	money.Conv(to_currency);
	ostringstream oss;
	oss << money;
	amount_out.put(oss.str());

	redraw();
}

											
int main()
{
	try {
		Currency_window win {Point{100,100},600,400,"lines"};
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





