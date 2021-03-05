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

	Axis xa {Axis::x, Point{20,300}, 280, 10, "x axis"}; 	
	win.attach(xa);  
	Axis ya {Axis::y, Point{20,300}, 280, 10, "y axis"};
	ya.label.set_color(Color::dark_red);
	win.attach(ya);

	Function sine {sin,0,100,Point{20,150},1000,50,50};
	win.attach(sine);

	Polygon poly;
	poly.add(Point{301,202});
	poly.add(Point{404,197});
	poly.add(Point{505,501});
	poly.add(Point{605,806});
	poly.add(Point{201,101});
	poly.set_style(Line_style::dash);
	win.attach(poly);

	Rectangle r {Point{200,200}, 100, 50}; 
	r.set_fill_color(Color::yellow);
	poly.set_style(Line_style(Line_style::dash,4));
	win.attach(r);

	Text t {Point{150,150}, "Hello, graphical world!"};
	win.attach(t);

	win.wait_for_button();   // display!
}

