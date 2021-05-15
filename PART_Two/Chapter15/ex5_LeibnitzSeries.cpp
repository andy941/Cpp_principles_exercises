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

#include "../hello_fltk/Simple_window.h"  
#include "../hello_fltk/Graph.h"

using namespace Graph_lib;

double Leibnitz(int n) 
{
	double r = 1;
	int den = 1;
	int sign = 1;

	while (n>1) {
		sign *= -1;
		den += 2;
		r += sign * 1.0/den;
		--n;
	}

	return r;
}

int main()
{
	constexpr int xmax = 600;                 // window size
	constexpr int ymax = 600;

	constexpr int x_orig = 100;         // position of (0,0) is center of window
	constexpr int y_orig = 300;
	constexpr Point orig {x_orig,y_orig};

	constexpr int xoffset = 100;  // distance from left-hand side of window to y axis
	constexpr int yoffset = 100;  // distance from bottom of window to x axis

	constexpr int xspace = 100;  // space beyond axis
	constexpr int yspace = 100;

	constexpr int xlength = 1000;
	constexpr int ylength = 400;

	constexpr int scale_x = 4;
	constexpr int scale_y = 200;

	constexpr Point tl {100,100};              // top left corner of our window

	constexpr int lim_l = 0;
	constexpr int lim_r = 100;

	Simple_window win {tl,xmax,ymax,"Function Graphs"};

	Axis x {Axis::x,Point{xspace,y_orig}, xlength, scale_x, ""};
	Axis y {Axis::y,Point{x_orig, ylength+yspace}, ylength, scale_y, ""};

	win.attach(x);
	win.attach(y);

	for (int n = 1; n < 100; ++n) {
		int dummy = 0; // dummy variable to circumvent weird contruction problems ([] empty doesn't work

		Function e { [dummy] (double xx) { return Leibnitz(xx); }, lim_l, double(n), orig, 800, scale_x, scale_y };

		win.attach(e);
		win.wait_for_button();
	}
}



