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

class Striped_Rect : public Rectangle 
{
	public:
		using Rectangle::Rectangle;

		void draw_lines() const override;
};

void Striped_Rect::draw_lines() const
{
	// Draw the Rectangle first
	Rectangle::draw_lines();

	// Get the top left corner
	Point p = point(0); 

	// Calculate the vectors of points necessary to draw
	// the lines for the striped fill
	Lines ll;
	for (int i = 2; i< height() ; i+=2) {
		ll.add( {p.x + 1, p.y + i}, {p.x + width() -1 , p.y + i} );			// adjust one pixel on each side
	}																		// just to meke it nicer

	ll.draw_lines();
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Striped_Rect rect { Point{300,300}, 400, 200 };
	win.attach(rect);

	win.wait_for_button();   // display!
}


