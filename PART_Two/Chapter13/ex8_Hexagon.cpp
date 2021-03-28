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

struct Regular_Hexagon : Polygon
{
	constexpr static double halfC = M_PI / 180;

	Regular_Hexagon () {};
	Regular_Hexagon (Point, int);

	private: 
	Point center;
	int distance;
};

Regular_Hexagon::Regular_Hexagon (Point c, int d)
	:center{c}, distance{d}
{
	add(Point{ c.x - d , c.y });
	add(Point{ c.x - d/2 , int(c.y + d * sqrt(3) / 2) });
	add(Point{ c.x + d/2 , int(c.y + d * sqrt(3) / 2) });
	add(Point{ c.x + d , c.y });
	add(Point{ c.x + d/2 , int(c.y - d * sqrt(3) / 2) });
	add(Point{ c.x - d/2 , int(c.y - d * sqrt(3) / 2) });
};

int main()
{
	const double height = sqrt(3) / 2;

	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	const Point start {10,10};
	const int distance = 10;
	const Point offset {int(distance * 1.5), int(distance * height)};

	// To tile draw two sets of hexagons offsetting the right amount

	Vector_ref<Regular_Hexagon> ref {};

	for (int i = 0; i < 100 ;i+=1){ 
		for (int j = 0; j < 100 ;j+=1){ 
			ref.push_back(new Regular_Hexagon {
					Point {
					start.x + distance * 3 * i, 
					int(start.y +  distance * height * 2 * j) 
					}, distance});
		}

		for (int j = 0; j < 100 ;j+=1){ 
			ref.push_back(new Regular_Hexagon {
					Point {
					offset.x + start.x + distance * 3 * i, 
					offset.y + int(start.y +  distance * height * 2 * j) 
					}, distance});
		}
	}

	for (int i = 0; i < ref.size(); i++) win.attach(ref[i]);

	win.wait_for_button();   // display!
}





