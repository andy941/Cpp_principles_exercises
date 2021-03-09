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

#include "Simple_window.h"           // if we want that “Next” button
#include "Graph.h"

using namespace Graph_lib;

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,600,400,"Canvas"};
	win.label("My window");


	Text a {Point{150,150}, "A"};
	a.set_font_size(150);
	a.set_style(Line_style(Line_style::solid,4));
	a.set_color(Color::dark_green);
	Text f {Point{350,150}, "F"};
	f.set_font_size(150);
	f.set_style(Line_style(Line_style::solid,4));
	f.set_color(Color::dark_yellow);

	win.attach(a);
	win.attach(f);

	win.wait_for_button();   // display!
}


