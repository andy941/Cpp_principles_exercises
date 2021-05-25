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
#include <random>

using namespace Graph_lib;

inline int rand_int(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min,max}(ran);
}

// The first positions of button and image are always messed up 
// at least when using i3, they fix after the first click
// I think it's due to the button implementation adjusting the proportions of the buttons
// to the proportions of the window. It doesn't seem to do it with the Image.

struct MyWindow : public Graph_lib::Window {

	MyWindow(Point xy, int w, int h, const string& title);

	private:

	static constexpr int side {40}; 
	Point xy_start {100,100}; 
	int width;
	int height;

	Button next_button;          
	Button quit_button;

	Button button; 
	Image image;

	void next() { redraw(); };
	void quit() { hide(); };
	void move_button();
};

MyWindow::MyWindow(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title}, width{w}, height{h},
	next_button{Point{x_max()-150,0}, 70, 20, "Next",
		[](Address, Address pw) {reference_to<MyWindow>(pw).next();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<MyWindow>(pw).quit();}},
	button{Button{ xy_start, side, side, "",
		[](Address, Address pw) { reference_to<MyWindow>(pw).move_button();}}},
	image{ Point{xy_start.x,xy_start.y + side }, "../hello_fltk/image.jpg" }
{
	attach(next_button);
	attach(quit_button);
	attach(button);
	attach(image);
}
		
void MyWindow::move_button() 
{
	int x = rand_int(-20, 20);
	int y = rand_int(-20, 20);

	// Check boundaries
	if ( button.loc.x + side + x > width ) x *= -1;
	if ( button.loc.x + x < 0 ) x *= -1;
	if ( button.loc.y + side + y > height ) y *= -1;
	if ( button.loc.y + y < 0 ) y *= -1;

	button.move(x,y);
	image.move(x,y);
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







