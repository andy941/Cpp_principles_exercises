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

	Rectangle r {Point{100,100}, 1920/3*2, 1080/4*3}; 
	win.attach(r);

	Rectangle r2 {Point{95,95}, 1920/3*2+10, 1080/4*3+10}; 
	r2.set_style(Line_style(Line_style::solid,3));
	win.attach(r2);

	win.wait_for_button();   // display!
}


