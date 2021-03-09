
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

#include "Simple_window.h"           // if we want that “Next” button
#include "Graph.h"

using namespace Graph_lib;

int main()
{
	static const double PI {3.14159265};
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,600,400,"Canvas"};
	win.label("My window");

	// Points are named anticlockwise for the top (or top left)
	// NOTE: There could be a procedural way to get an infinite series of polygons inscribed
	// in each other. Not sure how straight forward it is.
	// Maybe some clever trigonometry knowing that the length of the side is fixed and regular
	// and the distance between the vertices can be calculated.
	
	int side {300};
	// Triangle
	Point A {400,200}; 
	Point B {400 - side/2, 200 + int((side*0.866))};
	Point C {400 + side/2, 200 + int((side*0.866))};

	Polygon triangle;
	triangle.add(A);
	triangle.add(B);
	triangle.add(C);
	triangle.set_color(Color::red);
	win.attach(triangle);

	// Square
	Point As {B.x,B.y-side};
	Point Bs {B};
	Point Cs {C};
	Point Ds {C.x,B.y-side};
	
	Polygon square;
	square.add(As);
	square.add(Bs);
	square.add(Cs);
	square.add(Ds);
	square.set_color(Color::blue);
	win.attach(square);

	// Pentagon
	Point Bp {B.x - int(side*cos((180-108)*PI/180)), B.y - int(side*sin((180-108)*PI/180))};
	Point Cp {B};
	Point Dp {C};
	Point Ep {C.x + int(side*cos((180-108)*PI/180)), C.y - int(side*sin((180-108)*PI/180))};
	Point Ap {A.x, A.y - int(side*cos((108/2)*PI/180))};
	
	Polygon pentagon;
	pentagon.add(Ap);
	pentagon.add(Bp);
	pentagon.add(Cp);
	pentagon.add(Dp);
	pentagon.add(Ep);
	pentagon.set_color(Color::green);
	win.attach(pentagon);

	win.wait_for_button();   // display!
}

