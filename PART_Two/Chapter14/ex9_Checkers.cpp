
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

// This is a mess, i don't understand why not just use the vector_ref to build the checkers board,
// it would make a lot more sense, this should work at least to move one checker but move() has a 
// strange behaviour moving always bottom-right a bit for some reason no matter the value.
// The script is amixture of things I tried to circumvent the fact that I am building a useless
// class on top of the vector_ref that would work perfectly as it is to hold all the shapes I need.
// THere wa a lot of trial-and-error-google-fu involved and I learnt some new things at least... 
// I can't spend anymore time on this, have to move on at some point.

class Group
{
	public:
		Group () { };

		void move (int idx, int x, int y) { group[idx].move(x,y); }
		void add(Shape*);
		int size() const { return group.size(); }
		void draw_lines() const { for (int i = 0; i < group.size(); i++) group[i].draw(); }
		void set_color(int idx, Color color) { group[idx].set_fill_color(color); };

		Shape& operator[](int);

	private:
		Vector_ref<Shape> group;
};

Shape& Group::operator[] (int index)
{
	    return group[index];
}

void Group::add(Shape* s)
{
	group.push_back(s);
}

// Create a Checker class which is just a circle with info about the current square position
class Checker : public Circle
{
	public:
	Checker ( Point corner, int x, int y, int square_size );

	void move(int x2, int y2);
	int cx() const { return x; };
	int cy() const { return y; };

	private:
		Point corner;
		int square_size;
		int x {0};
		int y {0};
		
};

Checker::Checker ( Point corner, int x, int y, int square_size )
	: Circle { 
		Point {  corner.x+x*square_size + square_size/2, corner.y+y*square_size + square_size/2 },
			  int(square_size*0.7/2)
	},
	x{x}, y{y}, square_size{square_size}, corner{corner}
{
}

void Checker::move(int x2, int y2)
{
	Circle::set_point( 0, 
			Point {  corner.x+x*square_size + square_size/2, corner.y+y*square_size + square_size/2 } );
}

class Board : public Shape
{
	public:
		Board ( Point, int );
		void draw_lines () const override;
		void move (int,int, int,int);				// Move checker in coordinate int,int to int,int

	private:
		int size;
		Group board;
		Group white;
		vector<Point> cd_w;			// Coordinates in squares
		Group black;
		vector<Point> cd_b;			// Coordinates in squares
};

Board::Board (Point corner, int hw)
{
	size = hw / 8;

	// add the board
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board.add( new Rectangle{ Point{ corner.x+i*size, corner.y+j*size }, size, size } );
			if ((i+j)%2 == 1) board.set_color(board.size()-1, Color::dark_blue);
		}
	}

	// add the white checkers
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			if ((i+j)%2 == 1) {
				white.add( new Checker{ corner, i, j, size } );
				white.set_color(white.size()-1, Color::white);
				cd_w.push_back(Point{i,j});
			}
		}
	}

	// add the black checkers
	for (int i = 0; i < 8; i++) {
		for (int j = 5; j < 8; j++) {
			if ((i+j)%2 == 1) {
				black.add( new Checker{ corner, i, j, size } );
				black.set_color(black.size()-1, Color::black);
				cd_b.push_back(Point{i,j});
				cerr << "Black " << i << ' ' << j;
			}
		}
	}
}

void Board::draw_lines() const 
{
	board.draw_lines();
	white.draw_lines();
	black.draw_lines();
}

void Board::move (int x1, int y1, int x2, int y2)
{
	for ( int i = 0; i < white.size(); i++ ) {
		if ( cd_w[i].x == x1  && cd_w[i].y == y1) {
			cd_w[i].x += x1;
			cd_w[i].y += y1;
			white.move(i, x2*size, y2*size);
		}
	}

	for ( int i = 0; i < black.size(); i++ ) {
		if ( cd_b[i].x == x1  && cd_b[i].y == y1) {
			cd_b[i].x += x1;
			cd_b[i].y += y1;
			black.move(i, x2*size, y2*size);
			cerr<< x2*size << ' ' << y2*size << " \n";
		}
	}
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Board b { Point{10,10}, 800 };
	b.move(0,5, -3, -3);
	win.attach(b);

	win.wait_for_button();   // display!
}




