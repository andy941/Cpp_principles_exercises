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

class Striped_Circle : public Circle 
{
	public:
		using Circle::Circle;

		void draw_lines() const override;
};

void Striped_Circle::draw_lines() const
{
	// Draw the Circle first
	Circle::draw_lines();

	// Get the top-center point and radius
	int rad = radius();
	Point p {center().x, center().y - rad}; 

	// Strategy here is to use simple pitagoras theorem to
	// calculate half the length of each line and then add the
	// line coordinates to the Lines object.
	Lines ll;
	int halfline = 0;

	for (int i = 2; i < rad*2 ; i+=2) {

		halfline = sqrt(pow(rad,2) - pow(rad-i,2));
		ll.add( {p.x + halfline, p.y + i}, {p.x - halfline , p.y + i} );		
	}

	ll.draw_lines();
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Striped_Circle circle { Point{500,500}, 400 };
	win.attach(circle);

	win.wait_for_button();   // display!
}



