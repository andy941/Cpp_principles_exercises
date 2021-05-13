
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

// The patched library I am using already used the Fct name that is
// asked in the exercise. I changed it in Fct_store to avoid problems.
//
// I don't know if what I did (a wrapper) is the correct solution here but I can't
// find a way to reset the points in the Shape base class. This way is probably very
// inefficient by constructing the class everytime one parameter is changed. it doesn't
// work when I try to change the value of count and build the class again. I have no
// idea how to overcome the problem. 
//
// ANYWAY, IT DOESN'T WORK.
// It's also probably against the very concept of having a virtual class with private objects
// and specific constraints like Shape.

template<class T> class Fct_store : public Shape
{
	Function* F {nullptr};
	Fct func {};
	double limit_l;
	double limit_r;
	Point origin {};
	int c;
	double xscale;
	double yscale;

	public:
    Fct_store(Fct f, double r1, double r2, Point orig,
        int count = 100, double xscale = 25, double yscale = 25, T precision = 1.0);

    Fct_store(double (*f)(double), double r1, double r2, Point orig,
		int count = 100, double xscale = 25, double yscale = 25, T precision= 1.0);

	void draw_lines() const override;
	void set_count(int);
};

template<class T> Fct_store<T>::Fct_store(Fct f, double r1, double r2, Point orig,
        int count, double xscale, double yscale, T precision)

{
    if (r2-r1<=0) error("bad graphing range");
    if (count <=0) error("non-positive graphing count");

	func = f;
	limit_l = r1;
	limit_r = r2;
	origin = orig;
	c = count;
	xscale = xscale;
	yscale = yscale;

	F = new Function{ func, limit_l, limit_r, origin, c, xscale, yscale };
};


template<class T> Fct_store<T>::Fct_store(double (*f)(double), double r1, double r2, Point orig,
        int count, double xscale, double yscale, T precision)
{
    if (r2-r1<=0) error("bad graphing range");
    if (count <=0) error("non-positive graphing count");

	func = static_cast<Fct>(f);
	limit_l = r1;
	limit_r = r2;
	origin = orig;
	c = count;
	xscale = xscale;
	yscale = yscale;

	F = new Function{ func, limit_l, limit_r, origin, c, xscale, yscale };
};

template<class T>
void Fct_store<T>::set_count(int cc) 
{
	// DOESN'T DISPLAY
	c = cc;

	F -> ~Function();
	F = new Function{ func, limit_l, limit_r, origin, c, xscale, yscale };
}

template<class T>
void Fct_store<T>::draw_lines() const
{
	// Both are ways to access structures at pointer address, I get the info about colors
	// form the base class everytime the draw_lines is called.
	(*F).set_color(color());
	F -> set_fill_color(fill_color());
	F -> set_style(style());

	F -> draw();
}

double cosine (double x) {return cos(x);};

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

	Fct_store<double> one { cosine, -10, 11, orig, 400, scale, scale};
	one.set_color(Color::blue);

	one.set_count(400);

	win.attach(x);
	win.attach(y);
	win.attach(one);

	gui_main();
}

