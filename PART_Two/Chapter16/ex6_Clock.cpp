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

#include "../hello_fltk/Window.h"  
#include "../hello_fltk/GUI.h"  
#include "../hello_fltk/Graph.h"
#include<ctime>
#include<unistd.h>

using namespace Graph_lib;

// Find the tick of the clock
class Scale_ticks {
	
	static constexpr double halfC = M_PI/180.0;
	Point c;
	double r;
	int m;
	double tick;

	public:
	Scale_ticks(Point center, double radius, int max) 
		: c{center}, r{radius}, m{max}, tick{360.0/max} { };
	
	Point operator() (int ticks) {
		double angle = tick*ticks*halfC - M_PI/2;
		return Point {
			int(c.x + r * cos(angle)),
			int(c.y + r * sin(angle))
		};
	}
};

struct Clock_window : Graph_lib::Window {

	Clock_window(Point xy, int w, int h, const string& title);

	void clock_main();
	void quit() { hide(); };

	private:
	Point center;
	double radius;
	int hour;
	int min;
	int sec;
	Vector_ref<Circle> h_dot {};
	Vector_ref<Circle> m_dot {};
	Vector_ref<Circle> s_dot {};
	Vector_ref<Line> h_arm {};
	Vector_ref<Line> m_arm {};
	Vector_ref<Line> s_arm {};

	void show_hours(int h) { 
		for (int i = 0; i < 12; i++) {
			h_dot[i].set_fill_color(Color::invisible);
			h_arm[i].set_color(Color::invisible);
		}
		h_dot[h].set_fill_color(Color::yellow);
		h_arm[h].set_color(Color::yellow);
	}
	void show_min(int min) { 
		for (int i = 0; i < 60; i++) {
			m_dot[i].set_fill_color(Color::invisible);
			m_arm[i].set_color(Color::invisible);
		}
		m_dot[min].set_fill_color(Color::blue);
		m_arm[min].set_color(Color::blue);
	}
	void show_sec(int sec) { 
		for (int i = 0; i < 60; i++) {
			s_dot[i].set_fill_color(Color::invisible);
			s_arm[i].set_color(Color::invisible);
		}
		s_dot[sec].set_fill_color(Color::red);
		s_arm[sec].set_color(Color::red);
	}
};

Clock_window::Clock_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	center{Point{xy.x + w/2, xy.y + h/2}},
	radius{ w/2.0+h/2.0-abs(w-h) -20 }
{
	//Scale_ticks sh;
	//Scale_ticks sm;
	Scale_ticks sh = Scale_ticks{center, radius, 12};
	Scale_ticks sm = Scale_ticks{center, radius*0.9, 60};
	Scale_ticks ss = Scale_ticks{center, radius*0.8, 60};

	for (int i = 0; i < 12; i++) {
		h_dot.push_back(new Circle{sh(i), 6});
		h_arm.push_back(new Line{center, sh(i)});
	}

	for (int i = 0; i < 12; i++) attach(h_dot[i]);
	for (int i = 0; i < 12; i++) attach(h_arm[i]);
	for (int i = 0; i < 12; i++) h_dot[i].set_color(Color::yellow);
	for (int i = 0; i < 12; i++) h_dot[i].set_color(Color::yellow);

	for (int i = 0; i < 60; i++) {
		m_dot.push_back(new Circle{sm(i), 5});
		m_arm.push_back(new Line{center, sm(i)});
	}

	for (int i = 0; i < 60; i++) attach(m_dot[i]);
	for (int i = 0; i < 60; i++) attach(m_arm[i]);
	for (int i = 0; i < 60; i++) m_dot[i].set_color(Color::blue);
	for (int i = 0; i < 60; i++) m_dot[i].set_color(Color::blue);

	for (int i = 0; i < 60; i++) {
		s_dot.push_back(new Circle{ss(i), 4});
		s_arm.push_back(new Line{center, ss(i)});
	}

	for (int i = 0; i < 60; i++) attach(s_dot[i]);
	for (int i = 0; i < 60; i++) attach(s_arm[i]);
	for (int i = 0; i < 60; i++) s_dot[i].set_color(Color::red);
	for (int i = 0; i < 60; i++) s_dot[i].set_color(Color::red);

	clock_main();
}

void Clock_window::clock_main()
{
	while (1) {

		Fl::wait(1);

		time_t now = time(nullptr);
		tm* ltm = localtime(&now);

		hour = ltm->tm_hour;
		min = ltm->tm_min;
		sec = ltm->tm_sec;


		cerr << 
			"Hour:" << hour << '\t' <<
			"Minutes:" << min << '\t' <<
			"Seconds:" << sec << '\t' <<
			'\n';


		show_hours(hour%12);
		show_min(min);
		show_sec(sec);

		redraw();
	}

}
											
int main()
{
	try {
		Clock_window win {Point{100,100},600,400,"Clock"};
		return gui_main();
	}
	catch(exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
}





