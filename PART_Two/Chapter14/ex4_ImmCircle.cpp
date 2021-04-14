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

class ImmCircle : public Circle 
{
	public:
	using Circle::Circle;

	// Okay not the most elegant but technically works, 
	// I couldn't find a better way to do it in the chapter.
	void move(int,int) {error("The Immobile Circle cannot be moved!\n");};
};

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	ImmCircle circle {Point{500,500}, 300};

	// SHould trigger the error, move() was overridden
	circle.move(44,44);

	win.attach(circle);
	win.wait_for_button();   // display!
}

