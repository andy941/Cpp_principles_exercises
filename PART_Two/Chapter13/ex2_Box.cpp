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

struct Box : Lines
{
	// The radius or "smoothing of the vertices is defined as a ratio relative
	// to the height of the box.
	Box() {};
	Box (Point p, int w, int h, double r) 
	:ww{w}, hh{h}
	{
		if (r >1) error("not a valid ratio for vertices smoothing.\n");

		radius = int(hh * r / 2);

		// add the points for the vertices, anticlockwise, from top-left
		Shape::add(Point{ p.x, p.y });
		Shape::add(Point{ p.x, p.y + h - 2*radius});
		Shape::add(Point{ p.x + w - 2*radius, p.y + h - 2*radius});
		Shape::add(Point{ p.x + w - 2*radius, p.y });

		// add points to Lines to make the hedges
		hedges.add(Point{ p.x, p.y + radius }, Point{ p.x, p.y + h -radius} );
		hedges.add(Point{ p.x + radius, p.y + h }, Point{ p.x + w -radius, p.y + h } );
		hedges.add(Point{ p.x + w, p.y + h - radius }, Point{ p.x + w, p.y + radius } );
		hedges.add(Point{ p.x + w - radius, p.y}, Point{ p.x + radius, p.y } );

	};

	void draw_lines() const;

	private: 
	int ww;
	int hh;
	int radius;
	Lines hedges {};
};

void Box::draw_lines()  const
{
	if (color().visibility()) {
		// Draw lines for hedges
		//hedges.set_color(color().as_int());
		hedges.draw_lines();

		// Draw arcs for vertices, clockwise
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,radius*2,radius*2,90,180);
		fl_arc(point(1).x,point(1).y,radius*2,radius*2,180,270);
		fl_arc(point(2).x,point(2).y,radius*2,radius*2,270,360);
		fl_arc(point(3).x,point(3).y,radius*2,radius*2,0,90);
	}
}

int main()
{
	Point tl {100,100};              // top left corner of our window
	Vector_ref<Box> ref {};

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	for (int i = 10; i < 1000 ;i+=10){ 
		ref.push_back(new Box {Point {100 - i,500 - i }, i*2,i*2, 0.2});
	}

	for (int i = 0; i < ref.size(); i++) win.attach(ref[i]);
	Box box {Point {100,400}, 255,255, 0.9999};
	box.set_color(Color::red);
	win.attach(box);

	Rectangle rec {Point {98,398}, 259,259};
	rec.set_color(Color::blue);
	win.attach(rec);

	win.wait_for_button();   // display!
}



