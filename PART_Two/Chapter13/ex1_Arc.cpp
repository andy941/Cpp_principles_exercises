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

struct Arc : Shape
{
	Arc() {};
	Arc (Point p, int w, int h, double a, double b) 
	:ww{w}, hh{h}, a_start{a}, a_end{b} 
	{
		add(Point{ p.x - w, p.y - h });
	};

	void draw_lines() const;

	private: 
	int ww;
	int hh;
	double a_start;
	double a_end;
};

void Arc::draw_lines()  const
{
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,ww+ww,hh+hh,a_start,a_end);
	}
}

int main()
{
	Point tl {100,100};              // top left corner of our window
	Vector_ref<Arc> ref {};

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	for (int i = 1; i < 1000 ;i+=2){ 
		ref.push_back(new Arc {Point {100,500}, i*2,i, 0, 90});
	}

	for (int i = 0; i < ref.size(); i++) win.attach(ref[i]);
	Arc arc {Point {100,400}, 255,255, 0, 90};
	arc.set_color(Color::red);
	win.attach(arc);

	win.wait_for_button();   // display!
}


