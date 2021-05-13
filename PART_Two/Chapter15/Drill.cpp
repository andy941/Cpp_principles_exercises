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

#include "../hello_fltk/Window.h"           // if we want that “Next” button
#include "../hello_fltk/Graph.h"

using namespace Graph_lib;

double s (double x) {return x/2;}
double sq (double x) {return x*x;}
double sloping_cos (double x) {return cos(x) + x/2;}

int main()
{
	constexpr int xmax = 600;                 // window size
	constexpr int ymax = 600;

	constexpr int x_orig = 300;         // position of (0,0) is center of window
	constexpr int y_orig = 300;
	constexpr Point orig {x_orig,y_orig};

	constexpr int xoffset = 100;  // distance from left-hand side of window to y axis
	constexpr int yoffset = 100;  // distance from bottom of window to x axis

	constexpr int xspace = 100;  // space beyond axis
	constexpr int yspace = 100;

	constexpr int xlength = 400;
	constexpr int ylength = 400;

	constexpr int scale = 20;

	constexpr Point tl {100,100};              // top left corner of our window

	Graph_lib::Window win {tl,xmax,ymax,"Function Graphs"};

	Axis x {Axis::x,Point{xspace,y_orig}, xlength, scale, "1 == 20 pixels"};
	Axis y {Axis::y,Point{x_orig, ylength+yspace}, ylength, scale, "1 == 20 pixels"};

	x.set_color(Color::red);
	y.set_color(Color::red);

	Function one { [](double){return 1;}, -10, 11, orig, 400, scale, scale };

	Function slope { s, -10, 11, orig, 400, scale, scale };
	Text lab_slope { Point{ x_orig - xlength / 2, y_orig + 80}, "x/2" };

	Function square { sq, -10, 11, orig, 400, scale, scale };
	Function cosine { cos, -10, 11, orig, 400, scale, scale };
	cosine.set_color(Color::blue);

	Function slopecos { sloping_cos, -10, 11, orig, 400, scale, scale };

	win.attach(one);
	win.attach(slope);
	win.attach(lab_slope);
	win.attach(square);
	win.attach(cosine);
	win.attach(slopecos);
	win.attach(x);
	win.attach(y);

	gui_main();
}

