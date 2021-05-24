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

struct Lines_window : Graph_lib::Window {

	Lines_window(Point xy, int w, int h, const string& title);

	private:

	Open_polyline lines;

	Button next_button;          // add (next_x,next_y) to lines
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	Menu color_menu;
	Button menu_button;

	Menu styles_menu;
	Button styles_menu_button;

	void next();
	void quit() { hide(); };

	// Color Menu
	void change(Color c) { lines.set_color(c);  Fl::redraw();}
	void red_pressed() { change(Color::red); hide_menu(); }
	void blue_pressed() { change(Color::blue); hide_menu(); }
	void black_pressed() { change(Color::black); hide_menu(); }

	void hide_menu() { color_menu.hide(); menu_button.show(); }
	void menu_pressed() { menu_button.hide(); color_menu.show(); }

	// Styles Menu
	void style_change(Line_style s) { lines.set_style(s);  Fl::redraw();}
	void solid_pressed() { style_change(Line_style::solid); hide_styles_menu(); }
	void dash_pressed() { style_change(Line_style::dash); hide_styles_menu(); }
	void dot_pressed() { style_change(Line_style::dot); hide_styles_menu(); }
	
	void hide_styles_menu() { styles_menu.hide(); styles_menu_button.show(); }
	void styles_menu_pressed() { styles_menu_button.hide(); styles_menu.show(); }

};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	next_button{Point{x_max()-150,0}, 70, 20, "Next point",
		[](Address, Address pw) {reference_to<Lines_window>(pw).next();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Lines_window>(pw).quit();}},
	next_x{Point{x_max()-310,0}, 50, 20, "next x:"},
	next_y{Point{x_max()-210,0}, 50, 20, "next y:"},
	xy_out{Point{100,0}, 100, 20, "current (x,y):"},
	
	color_menu{Point{x_max()-70,40},70,20,Menu::vertical,"color"},
	menu_button{Point{x_max()-80,30}, 80, 20, "color menu",
		[](Address, Address pw) {reference_to<Lines_window>(pw).menu_pressed();}},

	styles_menu{Point{x_max()-70,200},70,20,Menu::vertical,"styles"},
	styles_menu_button{Point{x_max()-80,210}, 80, 20, "styles menu",
		[](Address, Address pw) {reference_to<Lines_window>(pw).styles_menu_pressed();}}

{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);

	// Color Menu
	color_menu.attach(new Button{Point{0,0},0,0,"red",
		[](Address, Address pw) {reference_to<Lines_window>(pw).red_pressed();}});
	color_menu.attach(new Button{Point{0,0},0,0,"blue",
		[](Address, Address pw) {reference_to<Lines_window>(pw).blue_pressed();}});
	color_menu.attach(new Button{Point{0,0},0,0,"black",
		[](Address, Address pw) {reference_to<Lines_window>(pw).black_pressed();}});
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);

	// Styles menu
	styles_menu.attach(new Button{Point{0,0},0,0,"solid",
		[](Address, Address pw) {reference_to<Lines_window>(pw).solid_pressed();}});
	styles_menu.attach(new Button{Point{0,0},0,0,"dash",
		[](Address, Address pw) {reference_to<Lines_window>(pw).dash_pressed();}});
	styles_menu.attach(new Button{Point{0,0},0,0,"dot",
		[](Address, Address pw) {reference_to<Lines_window>(pw).dot_pressed();}});
	attach(styles_menu);
	styles_menu.hide();
	attach(styles_menu_button);

	attach(lines);
}
		
void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{x,y});

	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

											
int main()
{
	try {
		Lines_window win {Point{100,100},600,400,"lines"};
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




