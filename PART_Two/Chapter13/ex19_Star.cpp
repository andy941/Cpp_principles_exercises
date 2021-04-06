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

struct Star : Closed_polyline
{
	// Need radians to use trigonometry
	constexpr static double halfC = M_PI / 180;

    Star() {};
    Star(Point, int, int, int);
};

Star::Star (Point center, int sides, int radius1, int radius2)
{
	// sides number strictly > 2
	if (sides < 3) error("sides have to be > 2 ... \n");

	// With the internal angle steps  we can go from one vertex
	// to the next one with trigonometry formulas. Hypotenuse is the
	// radius and the angle increments at every step of the cycle
	double step = 360.0 / sides;
	int x,y;

	for (double i = 0; i < 360; i+= step) {

		// external vertex of the star
		x = int(center.x + radius1 * cos(i * halfC));
		y = int(center.y + radius1 * sin(i * halfC));

		add(Point{x,y});

		// internal vertex of the star
		x = int(center.x + radius2 * cos((i + step/2) * halfC));
		y = int(center.y + radius2 * sin((i + step/2) * halfC));

		add(Point{x,y});
	}
};

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Vector_ref<Star> ref {};

	for (int i = 0; i < 1000; i++) {
		ref.push_back( new Star { Point { 450, 500 }, 30, i*5 + 30, i*5 });
	}

	for (int i = 0; i < ref.size(); i++) win.attach(ref[i]);

	win.wait_for_button();   // display!
}


