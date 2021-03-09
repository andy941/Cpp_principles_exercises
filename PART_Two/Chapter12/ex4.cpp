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

	Rectangle r1 {Point{200,200}, 50, 50}; 
	Rectangle r2 {Point{200,300}, 50, 50}; 
	Rectangle r3 {Point{250,250}, 50, 50}; 
	Rectangle r4 {Point{300,200}, 50, 50}; 
	Rectangle r5 {Point{300,300}, 50, 50}; 
	r1.set_fill_color(Color::yellow);
	r2.set_fill_color(Color::yellow);
	r3.set_fill_color(Color::yellow);
	r4.set_fill_color(Color::yellow);
	r5.set_fill_color(Color::yellow);
	win.attach(r1);
	win.attach(r2);
	win.attach(r3);
	win.attach(r4);
	win.attach(r5);

	Rectangle r6 {Point{250,200}, 50, 50}; 
	Rectangle r7 {Point{200,250}, 50, 50}; 
	Rectangle r8 {Point{300,250}, 50, 50}; 
	Rectangle r9 {Point{250,300}, 50, 50}; 
	r6.set_fill_color(Color::blue);
	r7.set_fill_color(Color::blue);
	r8.set_fill_color(Color::blue);
	r9.set_fill_color(Color::blue);
	win.attach(r6);
	win.attach(r7);
	win.attach(r8);
	win.attach(r9);

	win.wait_for_button();   // display!
}


