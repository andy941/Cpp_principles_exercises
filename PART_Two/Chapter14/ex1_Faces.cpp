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

class Smiley : public Circle 
{
	constexpr static double eye_coeff = 0.1;
	constexpr static double wmouth_coeff = 0.4;
	constexpr static double hmouth_coeff = 0.3;

	using Circle::Circle;

	void draw_lines() const;
};

void Smiley::draw_lines() const
{

	Point cc = center();			// Get the center of the face

	// Draw the eyes
	Point eyel {int(cc.x - radius()/2), int(cc.y - radius()/2)};
	Point eyer {int(cc.x + radius()/2), int(cc.y - radius()/2)};

	int r_eye = radius() * eye_coeff;

	Circle eye_left { eyel, r_eye };
	Circle eye_right { eyer, r_eye };

	eye_left.draw_lines();
	eye_right.draw_lines();

	// Draw the mouth
	int width_mouth = radius() * wmouth_coeff;
	int height_mouth = radius() * hmouth_coeff;

	cerr << r_eye << '\n' << width_mouth << '\n';

    if (color().visibility())
        fl_arc(cc.x - width_mouth, cc.y - height_mouth, width_mouth*2, height_mouth*2, 180, 360);

	Circle::draw_lines();			// Draw the face Circle
}

class Frowney : public Circle 
{
	constexpr static double eye_coeff = 0.1;
	constexpr static double wmouth_coeff = 0.4;
	constexpr static double hmouth_coeff = 0.3;

	using Circle::Circle;

	void draw_lines() const;
};

void Frowney::draw_lines() const
{

	Point cc = center();			// Get the center of the face

	// Draw the eyes
	Point eyel {int(cc.x - radius()/2), int(cc.y - radius()/2)};
	Point eyer {int(cc.x + radius()/2), int(cc.y - radius()/2)};

	int r_eye = radius() * eye_coeff;

	Circle eye_left { eyel, r_eye };
	Circle eye_right { eyer, r_eye };

	eye_left.draw_lines();
	eye_right.draw_lines();

	// Draw the mouth
	int width_mouth = radius() * wmouth_coeff;
	int height_mouth = radius() * hmouth_coeff;

    if (color().visibility())
        fl_arc(cc.x - width_mouth, cc.y - height_mouth, width_mouth*2, height_mouth*2, 0, 180);

	Circle::draw_lines();			// Draw the face Circle
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Smiley smile {Point {220,600}, 150};
	Frowney frown {Point {800,600}, 150};

	win.attach(smile);
	win.attach(frown);

	win.wait_for_button();   // display!
}
