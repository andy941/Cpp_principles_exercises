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

// From Chapter15 ex6:
vector<double> split_val ( const string& line, const string& delim = ",")
{
	char x;
	double val;
	vector<double> v;
	istringstream iss { line };

	while (iss >> val) {
		v.push_back(val);
		iss >> x;
		if (x != ',') error("This doesn't seem a csv file... \n");
	}

	return v;
}


//------------------------------------------------------------------------
//
struct Shapes_window : public Graph_lib::Window {

	Shapes_window(Point xy, int w, int h, const string& title);

	ifstream ifs;
	char current_shape {'c'};
	Vector_ref<Shape> shapes;
	Button quit_button;
	Button next_button;          // add (next_x,next_y) to lines

	Menu shapes_menu;
	Button shapes_button;

	void next();
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
	next_button{Point{x_max()-150,0}, 70, 20, "Next point",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).next();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).quit();}},
	
	shapes_menu{Point{x_max()-70,40},70,20,Menu::vertical,"Shapes:"},
	shapes_button{Point{x_max()-80,30}, 80, 20, "Shapes menu",
		[](Address, Address pw) {reference_to<Shapes_window>(pw).menu_pressed();}},
	ifs{"coordinates.csv"}

{
	if(!ifs) {error("Sorry can't open file 'coordinates.csv'"); quit();}

	attach(next_button);
	attach(quit_button);

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

void Shapes_window::next()
{
	string line;
	
	getline(ifs, line);
	if (ifs.eof()) {cerr << "\nEND OF coordinates.csv FILE reached\n"; quit();}

	vector<double> values = split_val(line, ",");
	if (values.size() != 3) {cerr << "Sorry the coordinates file seem to have "
		"more than 3 columns\n"; quit();}

	int x = values[0];
	int y = values[1];
	int s = values[2];

	switch (current_shape) {
		case 'c':
			shapes.push_back( new Circle{ Point{x,y}, s } );
			attach(shapes[shapes.size()-1]);
			break;
		case 's':
			s /= sqrt(2);
			shapes.push_back( new Rectangle{ Point{x-s,y-s}, s*2, s*2 } );
			attach(shapes[shapes.size()-1]);
			break;
		case 't':
			shapes.push_back( new Regular_Polygon{ Point{x,y}, 3, s } );
			attach(shapes[shapes.size()-1]);
			break;
		case 'h':
			shapes.push_back( new Regular_Polygon{ Point{x,y}, 6, s } );
			attach(shapes[shapes.size()-1]);
			break;
	}

	redraw();
}
		
void Shapes_window::circle_pressed()
{
	current_shape = 'c';
	shapes_menu_hide();
	redraw();
}

void Shapes_window::square_pressed()
{
	current_shape = 's';
	shapes_menu_hide();
	redraw();
}

void Shapes_window::triangle_pressed()
{
	current_shape = 't';
	shapes_menu_hide();
	redraw();
}
											
void Shapes_window::hexagon_pressed()
{
	current_shape = 'h';
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






