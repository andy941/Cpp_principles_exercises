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

#include "../Chapter13/ex10_RegularPolygon.cpp"
#include "../hello_fltk/Window.h"  
#include "../hello_fltk/GUI.h"  
#include "../hello_fltk/Graph.h"

using namespace Graph_lib;

struct Shapes_window : public Graph_lib::Window {

	Shapes_window(Point xy, int w, int h, const string& title);

	Vector_ref<Shape> shapes;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	In_box size; // generic size of the shape

	Menu shapes_menu;
	Button shapes_button;

	void quit() { hide(); };

	// Shapes Menu
	void circle_pressed();
	void triangle_pressed();
	void square_pressed();
	void hexagon_pressed();
	//void blue_pressed() { change(Color::blue); hide_menu(); }

	void shapes_menu_hide() { shapes_menu.hide(); shapes_button.show(); }
	void menu_pressed() { shapes_button.hide(); shapes_menu.show(); }
};

Shapes_window::Shapes_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).quit();}},
	next_x{Point{x_max()-310,0}, 50, 20, "next x:"},
	next_y{Point{x_max()-210,0}, 50, 20, "next y:"},
	size{Point{x_max()-410,0}, 50, 20, "next shape size:"},
	
	shapes_menu{Point{x_max()-70,40},70,20,Menu::vertical,"Shapes:"},
	shapes_button{Point{x_max()-80,30}, 80, 20, "Shapes menu",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).menu_pressed();}}

{
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(size);

	// Color Menu
	shapes_menu.attach(new Button{Point{0,0},0,0,"Circle",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).circle_pressed();}});
	shapes_menu.attach(new Button{Point{0,0},0,0,"Square",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).square_pressed();}});
	shapes_menu.attach(new Button{Point{0,0},0,0,"Triangle",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).triangle_pressed();}});
	shapes_menu.attach(new Button{Point{0,0},0,0,"Hexagon",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).hexagon_pressed();}});

	attach(shapes_menu);
	shapes_menu.hide();
	attach(shapes_button);
}
		
void Shapes_window::circle_pressed()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	int s = size.get_int();

	shapes.push_back( new Circle{ Point{x,y}, s } );
	attach(shapes[shapes.size()-1]);

	shapes_menu_hide();

	redraw();
}

void Shapes_window::square_pressed()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	int s = size.get_int();
	s /= sqrt(2);

	shapes.push_back( new Rectangle{ Point{x-s,y-s}, s*2, s*2 } );
	attach(shapes[shapes.size()-1]);

	shapes_menu_hide();

	redraw();
}

void Shapes_window::triangle_pressed()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	int s = size.get_int();

	shapes.push_back( new Regular_Polygon{ Point{x,y}, 3, s } );
	attach(shapes[shapes.size()-1]);

	shapes_menu_hide();

	redraw();
}
											
void Shapes_window::hexagon_pressed()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	int s = size.get_int();

	shapes.push_back( new Regular_Polygon{ Point{x,y}, 6, s } );
	attach(shapes[shapes.size()-1]);

	shapes_menu_hide();

	redraw();
}

int main()
{
	try {
		Shapes_window win {Point{100,100},600,400,"lines"};
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





