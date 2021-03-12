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

#include "Simple_window.h"           // if we want that “Next” button
#include "Graph.h"

using namespace Graph_lib;

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1000,"Canvas"};
	win.label("My window");

	Lines grid;
	Vector_ref<Rectangle> recs;

	for (int i = 0; i < 801; i += 100) {
		grid.add(Point{i,0},Point{i,800});
		grid.add(Point{0,i},Point{800,i});

		if (i < 701) {
			recs.push_back(new Rectangle{Point{i,i}, Point{i+100,i+100}});
			recs[recs.size()-1].set_fill_color(Color::red);
			win.attach(recs[recs.size()-1]);
		}
	}

	win.attach(grid);

	Image img {Point{0,0},"image.jpg"};
	img.set_mask(Point{0,0},100,100);
	win.attach(img);



	win.wait_for_button();   // display!

	int x,y, actualx{0}, actualy{0}, posx{0}, posy{0};

	for (int i = 0; i < 30; i++) {

		while(true) {
			x = (rand()%4 -  2) * 100;
			y = (rand()%4 -  2) * 100;

			if (x ==0 && y == 0) continue;

			posx = actualx + x;
			posy = actualy + y;

			cerr << posx << "  " << posy << endl;

			// if new position is legal move the image, otherwise pick another
			if(posx >0 && posy >0 && posx < 800 && posy < 800) break;
		}

		actualx = posx;
		actualy = posy;
		
		img.move(x,y);

		win.wait_for_button();   // display!
	}
}

