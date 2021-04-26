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

// The general idea is to find the heghest and lowest points in terms of 
// y value, and then go through all the segments with each y value
// to find the x values necassary to draw the lines.
// Coded properly should work even with complicated polylines that maybe
// have more that one stripe segment on the same x axis. The key problem is
// always in those cases were the lines go back up/cross themselves, 
// Then you have to be careful to draw the stripes only on the "inside" of
// the polyline.
// The bad thing about this algorithm is that is very expensive, increases
// quadratically with the number of points.
// It doesn't cover all the inside of the polyline completely, when it crosses itself.
// I am not sure if this is okay, probabl is not quite a success. It produces very nice modern art though.


int Solve_for_x(const Point& a, const Point& b, const int y)
{
	if (a.x == b.x) return a.x; // no need to calculate, special case slope is infinite

	double slope = double(a.y - b.y) / (a.x - b.x); 
	double intercept = a.y - slope * a.x;

	int x = (y - intercept) / slope;

	return x;
}

class Striped_Closed_polyline : public Closed_polyline
{
	using Closed_polyline::Closed_polyline;

	void draw_lines() const override;

};

void Striped_Closed_polyline::draw_lines() const
{
	Closed_polyline::draw_lines();

	Lines lines;
	vector<Point> points;

	for (int i = 0; i < number_of_points(); i++) {
		points.push_back(point(i));
	}

	int highest = points[0].y, lowest = points[0].y;

	for (Point p : points) {
		if (p.y > highest) highest = p.y;
		if (p.y < lowest) lowest = p.y;
	}

	cerr << "H=" << highest << '\t' << "L=" << lowest << '\n';

	vector<int> x_coordinates;

	for (int i = lowest; i < highest; i+=2) {	

		for (int j = 0; j < points.size(); j++) {

			// if stripe (y=i) hits the segment then solve to find the x
			// is a bit clunky because it wraps around and accounts for the 
			// "Closing segment"

			if ( !(points[j].y-1 < i) != !(points[(j+1)%points.size()].y-1 < i) ) {
				x_coordinates.push_back(Solve_for_x(points[j], points[(j+1)%points.size()], i));
			}
		}

		//if (x_coordinates.size() % 2 != 0) error("Something went wrong...");
		sort(x_coordinates.begin(), x_coordinates.end());

		for (int x : x_coordinates) cerr << x << ',' << i << '\t';
		cerr << '\n';
		
		for (int k = 1; k < x_coordinates.size(); k+=2) {
			lines.add( Point{ x_coordinates[k], i }, 
					Point{ x_coordinates[k-1], i } );
		}

		x_coordinates = {};
	}

	lines.draw_lines();
}

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	Striped_Closed_polyline closed {
		{100,100},
		{230,400},
		{400,200},
		{350,200},
		{300,300},
		{300,300},
		{800,800},
		{100,500},
		{900,800},
		{500,900},
		{200,300},
		{600,400},
	};

	win.attach(closed);
	win.wait_for_button();   // display!
}




