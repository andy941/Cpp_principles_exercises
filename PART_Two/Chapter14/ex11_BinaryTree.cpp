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

	int levels;
	Point root;

	public:
		BinaryTree () {};
		BinaryTree (Point r, int l);

		void draw_lines () const override;
};

BinaryTree::BinaryTree (Point r, int l)
	: levels{l}, root{r}
{
}

void BinaryTree::draw_lines () const
{
	if ( levels == 0 ) return;

	vector<Point> vec {root};
	Vector<Point> vec2 {};

	Vector_ref<Circle> circles {};
	Lines lines;
	double angle = 160;
	double height = 70;
	int delta = height * tan(angle/2*halfC);
	int radius {5};

	Circle first_node { root, radius };
	first_node.set_fill_color(Color::green);
	first_node.draw_lines();

	if ( levels == 1 ) return;

	for ( int i = 0; i < levels; i++) {
		for ( Point x : vec ) {

			vec2.push_back(Point {x.x - delta, int(x.y + height)});
			circles.push_back(new Circle { vec2[vec2.size()-1], radius });
			lines.add(Point{ x.x, x.y+radius }, Point{ n(circles[circles.size()-1]) });

			vec2.push_back(Point {x.x + delta, int(x.y + height)});
			circles.push_back(new Circle { vec2[vec2.size()-1], radius });
			lines.add(Point{ x.x, x.y+radius }, Point{ n(circles[circles.size()-1]) });
		}

		vec = vec2;
		vec2 = {};

		delta *= 0.5;
	}

	lines.draw_lines();
	for (int i=0; i < circles.size(); i++) circles[i].set_fill_color(Color::dark_blue);
	for (int i=0; i < circles.size(); i++) circles[i].draw_lines();
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	BinaryTree nodes { Point { 700, 100 }, 10 };
	win.attach(nodes);

	win.wait_for_button();   // display!
}


