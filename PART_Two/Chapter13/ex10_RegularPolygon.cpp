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

struct Regular_Polygon : Closed_polyline
{
	// Need radians to use trigonometry
	constexpr static double halfC = M_PI / 180;

	Regular_Polygon () {};
	Regular_Polygon (Point, int, int);

	private: 
	Point center;
	int radius;
	int sides;
	double angle_ext;
};

Regular_Polygon::Regular_Polygon (Point c, int s, int d)
	:center{c}, radius{d}, sides{s}
{
	// sides number strictly > 2 of course ..
	if (sides < 3) error("sides have to be > 2 ... \n");

	// With the internal angle steps  we can go from one vertex
	// to the next one with trigonometry formulas. Hypotenuse is the
	// radius and the angle increments at every step of the cycle
	double step = 360.0 / sides;
	int x,y;

	for (double i = 0; i < 360; i+= step) {

		x = int(c.x + d * cos(i*halfC));
		y = int(c.y + d * sin(i*halfC));

		add(Point{x,y});
	}
};

//int main()
//{
//	const double height = sqrt(3) / 2;
//
//	Point tl {100,100};              // top left corner of our window
//
//	Simple_window win {tl,800,1200,"Canvas"};
//	win.label("My window");
//
//	const Point start {600,500};
//	constexpr int radius = 100;
//	constexpr int sides = 1000;
//	constexpr int increment = 5;
//
//	Vector_ref<Regular_Polygon> ref {};
//    
//	for (int i = 3; i < sides; i++) {
//		ref.push_back( new Regular_Polygon { Point { start.x, start.y }, i, radius + i*increment });
//	}
//
//	for (int i = 0; i < ref.size(); i++) win.attach(ref[i]);
//	
//	win.wait_for_button();   // display!
//}






