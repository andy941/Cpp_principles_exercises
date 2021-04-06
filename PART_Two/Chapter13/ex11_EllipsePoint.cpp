/*
 * The only way to make this work is to clone this repository:
 *		https://github.com/cortical-iv/hello_fltk.git
 *	And follow the instructions, essentially the most reliable
 *	course of action is to have all the files in the work directory
 *	and then compile each time with this:
 *
 *	g++ -w -Wall -std=c++11 <file.cpp> Graph.cpp Window.cpp GUI.cpp Simple_window.cpp `fltk-config --ldflags --use-images` -o <file.o>
 *
 *	(Or you can make compile and then just do the linking, which is faster ...)
 *
*/

#include "Simple_window.h"           // if we want that “Next” button
#include "Graph.h"

using namespace Graph_lib;

int main()
{
	// Need radians to use trigonometry
	constexpr static double halfC = M_PI / 180;

	Point tl {100,100};              // top left corner of our window
	constexpr  Point start { 600 , 600 };

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Ellipse ellipse { start, 100, 150 };
	win.attach(ellipse);

	Line h_axis { Point { start.x - 100, start.y }, Point { start.x + 100, start.y } };
	Line v_axis { Point { start.x, start.y - 150 }, Point { start.x, start.y + 150 } };
	h_axis.set_color(Color::red);
	v_axis.set_color(Color::red);
	win.attach(h_axis);
	win.attach(v_axis);

	Marks m {"*", {ellipse.focus1(), ellipse.focus2()}};
	win.attach(m);

	// use parametric equations for ellipse to find a 
	// point on it and connect it with lines
	Point vertex { start.x + int(100 * cos(30 * halfC)), start.y + int(150 * sin(30 * halfC)) };
	Line l1 { ellipse.focus1(), vertex };
	Line l2 { ellipse.focus2(), vertex };
	l1.set_color(Color::cyan);
	l2.set_color(Color::cyan);
	win.attach(l1);
	win.attach(l2);

	win.wait_for_button();   // display!
}



