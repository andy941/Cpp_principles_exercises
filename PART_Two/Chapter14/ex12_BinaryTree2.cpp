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
#include "ex11_BinaryTree.cpp"


//------------------------------------------------------------------------
// Some helper functions and classes

class Triangle : public Polygon
{
	Point center;
	int height;
	int side;

	public:
		Triangle () {};
		Triangle ( Point center, int height )
		: center{center}, height{height} 
		{
			side = height * 2 / sqrt(3); 

			Polygon::add( n() );
			Polygon::add( Point { s().x - int(side/2), s().y } );
			Polygon::add( Point { s().x + int(side/2), s().y } );
			
		};

		Point n() const;
		Point s() const;

};

Point Triangle::n() const
{
	Point p {center.x, center.y  - int(0.66666*height)};
	return p;
}

Point Triangle::s() const
{
	Point p {center.x, center.y  + int(0.33333*height)};
	return p;
}


//------------------------------------------------------------------------
// Define the Binary Tree, save the points where nodes should go
// in the Shape (Shape::add()), should make things easier when overriding
// The draw function later

class BinaryTree_Triangle : public BinaryTree 
{
	constexpr static double halfC = M_PI / 180;

	public:
		using BinaryTree::BinaryTree;

		void draw_lines () const override;
};

void BinaryTree_Triangle::draw_lines () const
{
	if ( levels == 0 ) return;

	vector<Point> vec {root};
	Vector<Point> vec2 {};

	Vector_ref<Triangle> triangles {};
	Lines lines;
	double angle = 160;
	double height = 70;
	int delta = height * tan(angle/2*halfC);
	int radius {10};

	Triangle first_node { root, radius };
	first_node.set_fill_color(Color::green);
	first_node.draw_lines();

	if ( levels == 1 ) return;

	for ( int i = 0; i < levels; i++) {
		for ( Point x : vec ) {

			vec2.push_back(Point {x.x - delta, int(x.y + height)});
			triangles.push_back(new Triangle { vec2[vec2.size()-1], radius });
			lines.add(Point{ x.x, x.y + int(0.33333*radius) }, Point{ triangles[triangles.size()-1].n() });

			vec2.push_back(Point {x.x + delta, int(x.y + height)});
			triangles.push_back(new Triangle { vec2[vec2.size()-1], radius });
			lines.add(Point{ x.x, x.y + int(0.33333*radius) }, Point{ triangles[triangles.size()-1].n() });

		}

		vec = vec2;
		vec2 = {};

		delta *= 0.5;
	}

	lines.draw_lines();
	for (int i=0; i < triangles.size(); i++) triangles[i].set_fill_color(Color::dark_blue);
	for (int i=0; i < triangles.size(); i++) triangles[i].draw_lines();
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	BinaryTree_Triangle nodes { Point { 700, 100 }, 7 };
	win.attach(nodes);
	
	win.wait_for_button();   // display!
}



