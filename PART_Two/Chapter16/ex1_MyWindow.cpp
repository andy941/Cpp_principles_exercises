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

using namespace Graph_lib;

struct MyWindow : Graph_lib::Window {

	MyWindow(Point xy, int w, int h, const string& title);

	private:

	Button next_button;          // add (next_x,next_y) to lines
	Button quit_button;

	void next();
	void quit() { hide(); };
};

MyWindow::MyWindow(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	next_button{Point{x_max()-150,0}, 70, 20, "Next point",
		[](Address, Address pw) {reference_to<MyWindow>(pw).next();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<MyWindow>(pw).quit();}}
{
	attach(next_button);
	attach(quit_button);

}
		
void MyWindow::next()
{
	redraw();
}

											
int main()
{
	try {
		MyWindow win {Point{100,100},600,400,"MyWindow"};
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





