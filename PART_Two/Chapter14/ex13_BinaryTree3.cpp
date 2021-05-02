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

//------------------------------------------------------------------------
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


//------------------------------------------------------------------------
// Some helper functions and classes

Point n(const Circle& r)
{
	Point p {r.center().x, r.center().y - r.radius()};
	return p;
}

Point s(const Circle& r)
{
	Point p {r.center().x, r.center().y + r.radius()};
	return p;
}


//------------------------------------------------------------------------
// Define the Binary Tree, save the points where nodes should go
// in the Shape (Shape::add()), should make things easier when overriding
// The draw function later

class BinaryTree : public Shape 
{
	constexpr static double halfC = M_PI / 180;

	public:
	int levels;
	Point root;
	string flow;

	BinaryTree () {};
	BinaryTree (Point r, int l, string f);

	virtual void draw_lines () const override;
};

BinaryTree::BinaryTree (Point r, int l, string f)
	: levels{l}, root{r}
{
	if (f=="up" || f=="down") flow = f;
	else error("flow can only be 'up' or 'down'.\n");
}

void BinaryTree::draw_lines () const
{
	if ( levels == 0 ) return;

	vector<Point> vec {root};
	Vector<Point> vec2 {};

	Vector_ref<Circle> circles {};
	Vector_ref<Arrow> arrows {};

	double angle = 140;
	double height = 70;
	int delta = height * tan(angle/2*halfC);
	int radius {5};

	double arrow_angle = 20;
	int arrow_length = height/4;

	Circle first_node { root, radius };
	first_node.set_fill_color(Color::green);
	first_node.draw_lines();

	if ( levels == 1 ) return;

	for ( int i = 0; i < levels; i++) {
		for ( Point x : vec ) {

			vec2.push_back(Point {x.x - delta, int(x.y + height)});
			circles.push_back(new Circle { vec2[vec2.size()-1], radius });
			if (flow == "down") arrows.push_back( new Arrow{ Point{ x.x, x.y+radius }, Point{ n(circles[circles.size()-1]) }, arrow_angle, arrow_length } );
			if (flow == "up") arrows.push_back( new Arrow{ Point{ n(circles[circles.size()-1]) }, Point{ x.x, x.y+radius }, arrow_angle, arrow_length } );

			vec2.push_back(Point {x.x + delta, int(x.y + height)});
			circles.push_back(new Circle { vec2[vec2.size()-1], radius });
			if (flow == "down") arrows.push_back( new Arrow{ Point{ x.x, x.y+radius }, Point{ n(circles[circles.size()-1]) }, arrow_angle, arrow_length } );
			if (flow == "up") arrows.push_back( new Arrow{ Point{ n(circles[circles.size()-1]) }, Point{ x.x, x.y+radius }, arrow_angle, arrow_length } );
		}

		vec = vec2;
		vec2 = {};

		delta *= 0.5;
		arrow_length *= 0.9;
	}

	for (int i=0; i < circles.size(); i++) circles[i].set_fill_color(Color::dark_blue);
	for (int i=0; i < circles.size(); i++) circles[i].draw_lines();
	for (int i=0; i < arrows.size(); i++) arrows[i].draw_lines();
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	BinaryTree nodes { Point { 500, 100 }, 10, "up"};
	win.attach(nodes);

	win.wait_for_button();   // display!
}



