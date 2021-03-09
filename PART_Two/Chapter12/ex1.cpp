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

	Polygon poly;
	poly.add(Point{100,200});
	poly.add(Point{400,200});
	poly.add(Point{400,500});
	poly.add(Point{100,500});
	poly.set_color(Color::blue);
	win.attach(poly);

	Rectangle r {Point{300,300}, 100, 50}; 
	poly.set_color(Color::red);
	win.attach(r);

	win.wait_for_button();   // display!
}


