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

	if (b.y >= a.y) {
		l = Point { int(b.x - length * sin(langle)), int(b.y - length * cos(langle))};
		r = Point { int(b.x - length * cos(rangle)), int(b.y - length * sin(rangle))};
	}

	else {
		l = Point { int(b.x + length * sin(langle)), int(b.y + length * cos(langle))};
		r = Point { int(b.x + length * cos(rangle)), int(b.y + length * sin(rangle))};
	}

	arrow.add(b,a);
	arrow.add(b,l);
	arrow.add(b,r);
};

void Arrow::draw_lines() const
{
	arrow.draw_lines();
};

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	//for (int i = 10; i < 1000 ;i+=10){ 
	//	ref.push_back(new Box {Point {100 - i,500 - i }, i*2,i*2, 0.2});
	//}

	//for (int i = 0; i < ref.size(); i++) win.attach(ref[i]);
	Arrow arrow {Point{200,200},Point{350,200}, 60, 60};
	arrow.set_color(Color::red);
	win.attach(arrow);

	Arrow arrow2 {Point{600,700},Point{600,400}, 15, 60};
	arrow2.set_color(Color::blue);
	win.attach(arrow2);

	win.wait_for_button();   // display!
}




