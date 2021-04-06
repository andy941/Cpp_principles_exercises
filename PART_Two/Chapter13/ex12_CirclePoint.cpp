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
	constexpr Point start { 500 , 500 };
	constexpr int radius = 300; 

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Circle circle { start, radius };
	win.attach(circle);

	int x,y,X,Y;

	x = start.x + int(radius * cos(0 * halfC));
	y = start.y + int(radius * sin(0 * halfC));

	Point v {x,y};

	Circle vertex { v, 5 };
	vertex.set_color(Color::red);
	win.attach(vertex);

	win.wait_for_button();   // display!

	for (int i = 1; i < 361; i++) {

		X = x;
		Y = y;

		x = start.x + int(radius * cos(i * halfC));
		y = start.y + int(radius * sin(i * halfC));

		vertex.move(x - X, y - Y);

		win.wait_for_button();   // display!
	}

}

