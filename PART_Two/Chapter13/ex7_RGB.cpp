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

// NOTE: The red colour gamut does not display properly on my Manjaro i3 installation, the script seem to work
// properly though outputting the right hex values.
// Example: Color {0xFF0000} does not output bright Red but green for some reason




#include "Simple_window.h"           // if we want that “Next” button
#include "Graph.h"
// this is needed for the setfill() function to have the 0 before each hex value for r g b. (see RGB function).
#include  <iomanip>


using namespace Graph_lib;

int RGB(int r, int g, int b)
{
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) error("RGB values out of range ... \n");

	stringstream stream;
	stream << "0x" << setfill('0') << setw(2) << right << hex << r 
		<< right << setw(2) << g
		<< right << setw(2) << b;

	int result;
	stream  >> hex >> result;
	
	//cerr  << hex << stream.str() << '\t' << dec << stream.str() << '\n';
	//cerr  << hex << result << '\t' << dec << result  << '\n' << '\n';

	return result;
}

int main()
{
	// how big do you want the squares? how segmented the
	// RGB color space should be?
	constexpr int segment = 8;
	constexpr int square_size = 4;

	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Vector_ref<Rectangle> vr;
	int x,y;
	int cell = 256 / segment;

	for (int i = 0; i<256; i+=segment){
		for (int j = 0; j<256; j+=segment) {
			for (int k = 0; k<256; k+=segment) {
				x = (j/segment*cell + k/segment) * square_size;
				y = i / segment * square_size;

				vr.push_back(new Rectangle{Point{x,y},square_size,square_size});
				vr[vr.size()-1].set_fill_color(Color{ RGB(i,j,k) });

				//vr[vr.size()-1].set_fill_color(Color{ 0xFF0000 });  <-- This should output all red squares!!
				cerr << x << ',' << y << '\n';
				win.attach(vr[vr.size()-1]);
			}
		}
	}

	win.wait_for_button();   // display!
}




