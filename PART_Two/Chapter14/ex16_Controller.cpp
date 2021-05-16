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


class Controller
{
	protected:
	Shape& s;
	bool state { 0 };
	int level { 0 };

	public:
	Controller (Shape& ss): s{ss} {};

	virtual void const on() { state = 1; };
	virtual void const off() { state = 0; };
	virtual void const set_level(const int&  l) { level = l; };
	virtual void const show() { if (state) cerr << "ON Level=" << level << '\n'; else cerr << "OFF Level=" << level << '\n';};
};

class Controller_color : public Controller
{
	Color old_color { Color::black };

	public:
	using Controller::Controller;

	void const on() override;
	void const off() override;
};

void const Controller_color::on()
{
	Controller::on();

	old_color = s.color();

	s.set_fill_color(level);
}

void const Controller_color::off()
{
	Controller::off();

	s.set_fill_color(old_color);
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Rectangle r {Point{300, 500}, 200, 400};
	Rectangle r2 {Point{550, 500}, 200, 400};

	Controller_color control { r };
	control.set_level(4);
	control.on();
	control.show();

	Controller_color control2 { r2 };
	control2.set_level(2);
	control2.show();

	win.attach(r);
	win.attach(r2);

	win.wait_for_button();   // display!
}

