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
#include <FL/fl_draw.H>           // if we want that “Next” button
#include "Graph.h"

using namespace Graph_lib;

// Modify box definition from exercise 2 to hold a text box
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

// Use the arrow definition from exercise 3
struct Arrow : Shape
{
	const double halfC = M_PI / 180;
	// The arrow is a particular case of Lines.
	// I chose to store three lines to draw the final arrow using draw_lines() from Lines.
	// User can define the angle at which the arrow head spreads (the whole head) and the length of the
	// arrow head.
	// The head is at  point B.
	Arrow () {};
	Arrow (Point a, Point b, double an, int length);

	void draw_lines() const;

	private: 
	double angle;
	int length;
	Lines arrow {};
};

Arrow::Arrow (Point a, Point b, double an, int length)
	:angle{an*halfC}, length{length}		// Store angle in radians, easier to use with cos/sin
{
	if (an > 90) error("Invalid angle > 45 degrees\n");

	// Calculate the arrow head and save it has two lines bifurcating from the head. 
	double arrow_length = sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));

	double langle = asin(abs(a.x - b.x) / arrow_length) - angle;
	double rangle = acos(abs(a.x - b.x) / arrow_length) - angle;

	Point l,r;

	if (b.y <= a.y && b.x <= a.x) {
		l = Point { int(b.x + length * sin(langle)), int(b.y + length * cos(langle))};
		r = Point { int(b.x + length * cos(rangle)), int(b.y + length * sin(rangle))};
	}

	if (b.y <= a.y && b.x > a.x) {
		l = Point { int(b.x - length * sin(langle)), int(b.y + length * cos(langle))};
		r = Point { int(b.x - length * cos(rangle)), int(b.y + length * sin(rangle))};
	}

	if (b.y >= a.y && b.x <= a.x) {
		l = Point { int(b.x + length * sin(langle)), int(b.y - length * cos(langle))};
		r = Point { int(b.x + length * cos(rangle)), int(b.y - length * sin(rangle))};
	}

	if (b.y >= a.y && b.x > a.x) {
		l = Point { int(b.x - length * sin(langle)), int(b.y - length * cos(langle))};
		r = Point { int(b.x - length * cos(rangle)), int(b.y - length * sin(rangle))};
	}

	arrow.add(b,a);
	arrow.add(b,l);
	arrow.add(b,r);
};

void Arrow::draw_lines() const
{
	arrow.draw_lines();
};


//-------------------------------------------------------------------
// Now Define a text box class using th existing Box and Text classes
//-------------------------------------------------------------------


// The text box is defined by a top-left point, a ratio that defines the "boundary"
// between the text itself and the box, and the dimensions of the box itself.

struct Text_Box : Shape
{
	Text_Box (string text, Point p, double r, int b)
		: t(text), p(p), r(r), boundary(b)
	{
		if (r >1 || r <= 0) error( "Invalid ratio! Valid between 0 and 1.\n");

		// Measure the size of the text to calculate the enclosing box
		int w = 0;
		int h = 0;

		fl_font(FL_HELVETICA, 16);
		fl_measure(text.c_str(), w, h);

		t_width = w;
		t_height = h;

		// Calculate the box dimensions
		p_box = Point{p.x - b, p.y - b - h };
		width = w + b*2;
		height = h + b*2;
	};

	void draw_lines() const;

	Point n()
	{
		Point p {p_box.x + width/2, p_box.y};
		return p;
	}

	Point s()
	{
		Point p {p_box.x + width/2, p_box.y + height};
		return p;
	}

	private:
		// Text related
		string t;
		Point p;
		double r;
		int t_width, t_height;

		// Box related
		Point p_box ;
		int boundary;
		int width,height;

};

void Text_Box::draw_lines() const
{

	// Draw the text
	fl_draw(t.c_str(),
			p.x, 
			p.y);

	// Calculate the box
	Box box {p_box, width, height, r};
	box.draw_lines();
}

int main()
{
	Point tl {100,100};              // top left corner of our window
	Vector_ref<Box> ref {};

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	// Draw the boxes
	string s {"Trial"};
	Text_Box box {s , Point {500,200}, 0.60, 15};
	win.attach(box);

	string s1 {"Lower 1"};
	Text_Box box1 {s1 , Point {300,700}, 0.60, 15};
	win.attach(box1);

	string s2 {"Lower 2"};
	Text_Box box2 {s2 , Point {700,700}, 0.60, 15};
	win.attach(box2);

	// Draw the arrows
	Arrow a1 {box1.n(), box.s(), 30, 20};	
	Arrow a2 {box2.n(), box.s(), 30, 20};	

	win.attach(a1);
	win.attach(a2);

	win.wait_for_button();   // display!

}


















