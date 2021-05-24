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

	const Point xy_buttons;
	static constexpr int side {40}; 
	Button next_button;          // add (next_x,next_y) to lines
	Button quit_button;
	Vector_ref<Button>  buttons;

	void next() { square_show(); redraw(); };
	void quit() { hide(); };
	void square_show();

	static void cb_square(Address, Address);
};

MyWindow::MyWindow(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	xy_buttons{ Point{xy.x + 10, xy.y + 10} },
	next_button{Point{x_max()-150,0}, 70, 20, "Next",
		[](Address, Address pw) {reference_to<MyWindow>(pw).next();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<MyWindow>(pw).quit();}}
{
	attach(next_button);
	attach(quit_button);

	// Initialize the buttons displayed in 4x4 matrix, can't reference itself, big problem, I will only define 4.
	// It doesn't really matter. there is no way to vectorize the process.
	buttons.push_back( new Button { Point{ xy_buttons.x + 1*side, xy_buttons.y + 1*side }, side, side, "",
		[](Address, Address pw) { reference_to<MyWindow>(pw).square_show(); reference_to<MyWindow>(pw).buttons[0].hide();}} );
	buttons.push_back( new Button { Point{ xy_buttons.x + 1*side, xy_buttons.y + 2*side }, side, side, "",
		[](Address, Address pw) { reference_to<MyWindow>(pw).square_show(); reference_to<MyWindow>(pw).buttons[1].hide();}} );
	buttons.push_back( new Button { Point{ xy_buttons.x + 2*side, xy_buttons.y + 1*side }, side, side, "",
		[](Address, Address pw) { reference_to<MyWindow>(pw).square_show(); reference_to<MyWindow>(pw).buttons[2].hide();}} );
	buttons.push_back( new Button { Point{ xy_buttons.x + 2*side, xy_buttons.y + 2*side }, side, side, "",
		[](Address, Address pw) { reference_to<MyWindow>(pw).square_show(); reference_to<MyWindow>(pw).buttons[3].hide();}} );

	for (int i = 0; i < buttons.size(); i++) { attach(buttons[i]); }
}
		
void MyWindow::square_show() 
{
	for (int i = 0; i < buttons.size(); i++) { buttons[i].show(); }
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






