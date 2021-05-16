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

#include "../hello_fltk/Window.h"  
#include "../hello_fltk/Graph.h"

using namespace Graph_lib;

struct DataFrame
{
};


class BarChart
{
};

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

	constexpr int lim_l = -10;
	constexpr int lim_r = 11;

	Graph_lib::Window win {tl,xmax,ymax,"Function Graphs"};

	Axis x {Axis::x,Point{xspace,y_orig}, xlength, scale, ""};
	Axis y {Axis::y,Point{x_orig, ylength+yspace}, ylength, scale, ""};

	win.attach(x);
	win.attach(y);

	gui_main();
}



