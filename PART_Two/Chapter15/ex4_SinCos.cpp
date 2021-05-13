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

double s (double x) {return sin(x);}
double c (double x) {return cos(x);}
double sc (double x) {return sin(x) + cos(x);}
double sscc (double x) {return sin(x)*sin(x) + cos(x)*cos(x);}

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

	Function sine { s, lim_l, lim_r, orig, 400, scale, scale };
	Text lab_s { Point{ x_orig + lim_l*scale, y_orig + int(s(lim_l) - 20)}, "sine" };
	sine.set_color(Color::blue);
	lab_s.set_color(Color::blue);

	Function cosine { c, lim_l, lim_r, orig, 400, scale, scale };
	Text lab_c { Point{ x_orig + lim_l*scale, y_orig + int(c(lim_l) - 30)}, "cosine" };
	cosine.set_color(Color::green);
	lab_c.set_color(Color::green);

	Function sinecosine { sc, lim_l, lim_r, orig, 400, scale, scale };
	Text lab_sc { Point{ x_orig + lim_l*scale, y_orig + int(sc(lim_l) - 40)}, "sine+cosine" };
	sinecosine.set_color(Color::red);
	lab_sc.set_color(Color::red);

	Function ss_cc { sscc, lim_l, lim_r, orig, 400, scale, scale };
	Text lab_sscc { Point{ x_orig + lim_l*scale, y_orig + int(sscc(lim_l) - 50)}, "sine*sine+cosine*cosine" };
	ss_cc.set_color(Color::cyan);
	lab_sscc.set_color(Color::cyan);

	win.attach(sine);
	win.attach(lab_s);
	win.attach(cosine);
	win.attach(lab_c);
	win.attach(sinecosine);
	win.attach(lab_sc);
	win.attach(ss_cc);
	win.attach(lab_sscc);
	win.attach(x);
	win.attach(y);

	gui_main();
}


