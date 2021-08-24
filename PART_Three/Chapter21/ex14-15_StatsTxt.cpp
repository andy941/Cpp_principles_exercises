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
#include <iterator>
#include<numeric> 
#include<algorithm> 
//#include "../std_lib_facilities.h"
#include "ex13_CleanUp.cpp"

using namespace Graph_lib;

// GUI implementation -----------------------------------------------------

struct Orders_window : public Graph_lib::Window {

	map<string,int> data;

	Orders_window(Point xy, int w, int h, const string& title);

	Button quit_button;
	Button load_button;
	In_box input_file;
	In_box output_file;
	In_box search_string;
	Out_box result;

	Menu actions_menu;
	Button actions_button;

	void quit() { hide(); };
	void load();

	// Actions Menu
	void find_pressed();
	void freq_pressed();
	void find_start_pressed();
	void find_length_pressed();

	void actions_menu_hide() { actions_menu.hide(); actions_button.show(); }
	void menu_pressed() { actions_button.hide(); actions_menu.show(); }
};

Orders_window::Orders_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Orders_window>(pw).quit();}},
	load_button{Point{x_max()-70,20}, 70, 20, "Load",
		[](Address, Address pw) {reference_to<Orders_window>(pw).load();}},
	input_file{Point{50,0}, 70, 20, "Input file:"},
	output_file{Point{200,0}, 70, 20, "Output file:"},
	search_string{Point{400,0}, 70, 20, "Search:"},
	result{Point{50,40}, x_max()-230, y_max()-100, "Output:"},
	
	actions_menu{Point{x_max()-180,40}, 180, 20 ,Menu::vertical,"Actions:"},
	actions_button{Point{x_max()-180,40}, 180, 20, "Actions menu",
		[](Address, Address pw) {reference_to<Orders_window>(pw).menu_pressed();}}

{
	attach(quit_button);
	attach(load_button);
	attach(input_file);
	attach(output_file);
	attach(search_string);
	attach(result);

	// Color Menu
	actions_menu.attach(new Button{Point{0,0},0,0,"[Search] for word",
		[](Address, Address pw) {reference_to<Orders_window>(pw).find_pressed();}});
	actions_menu.attach(new Button{Point{0,0},0,0,"highest occurrence",
		[](Address, Address pw) {reference_to<Orders_window>(pw).freq_pressed();}});
	actions_menu.attach(new Button{Point{0,0},0,0,"word begins with [Search]",
		[](Address, Address pw) {reference_to<Orders_window>(pw).find_start_pressed();}});
	actions_menu.attach(new Button{Point{0,0},0,0,"word length is [Search]",
		[](Address, Address pw) {reference_to<Orders_window>(pw).find_length_pressed();}});

	attach(actions_menu);
	actions_menu.hide();
	attach(actions_button);
}

void Orders_window::load() 
{
	const string input = input_file.get_string();
	ostringstream oss;

	ifstream ifs { input };
	if (!ifs) {
		result.put("Cannot open file!");
		redraw();
		return;
	};

	data = cleanup(ifs);
	oss << "File " << input << " loaded." << '\n';
	for (auto& x : data) oss << x.first << "\t" << x.second << "\n";
	result.put(oss.str());
}

void Orders_window::find_pressed()
{
	const string input = input_file.get_string();
	const string output = output_file.get_string();
	const string search = search_string.get_string();
	ostringstream oss;
	
	auto x = data.find(search);
	if (x != data.end()) oss << x->first << '\t' << x->second << endl;
	else oss << search << " not found." << endl;

	result.put(oss.str());

	//if(output != "") copy(data, output);

	actions_menu_hide();
}
		
void Orders_window::freq_pressed()
{
	const string input = input_file.get_string();
	const string output = output_file.get_string();
	const string search = search_string.get_string();
	ostringstream oss;
	
	auto x = max_element(data.begin(), data.end(), 
			[&](const auto& a, const auto& b) { return a.second < b.second; });
	if (x != data.end()) oss << x->first << '\t' << x->second << endl;
	else oss << "No data loaded." << endl;

	result.put(oss.str());

	//if(output != "") copy(data, output);

	actions_menu_hide();
}

void Orders_window::find_start_pressed()
{
	const string input = input_file.get_string();
	const string output = output_file.get_string();
	const string search = search_string.get_string();
	ostringstream oss;
	map<string, int> tmp;
	
	copy_if(data.begin(), data.end(), inserter(tmp, tmp.begin()), 
			[&](const auto a) { 
			return a.first.compare(0, search.size(),search) == 0; 
			});
	if (tmp.empty()) {
		result.put("No string beginning with " + search  + " exist.");
		return;
	}
	
	for (auto& x : tmp) oss << x.first << "\t" << x.second << "\n";
	result.put(oss.str());

	//if(output != "") copy(data, output);

	actions_menu_hide();
}

void Orders_window::find_length_pressed()
{
	const string input = input_file.get_string();
	const string output = output_file.get_string();
	const int search = search_string.get_int();
	ostringstream oss;
	map<string, int> tmp;
	
	copy_if(data.begin(), data.end(), inserter(tmp, tmp.begin()), 
			[&](const auto& a) { return a.first.size() == search; });
	if (tmp.empty()) {
		result.put("No string of length " + to_string(search)  + " exist.");
		return;
	}

	for (auto& x : tmp) oss << x.first << "\t" << x.second << "\n";
	result.put(oss.str());

	//if(output != "") copy(data, output);

	actions_menu_hide();
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





