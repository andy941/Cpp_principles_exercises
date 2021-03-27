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
	

};

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Vector_ref<Regular_Hexagon> ref {};

	for (int i = 10; i < 1000 ;i+=10){ 
		ref.push_back(new Regular_Hexagon {Point {100 - i,500 - i }, i*2});
	}

	for (int i = 0; i < ref.size(); i++) win.attach(ref[i]);

	win.wait_for_button();   // display!
}





