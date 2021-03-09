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


vector<Point> SuperEllipse(double a, double b, double m, double n, int N, int scaling, Point center)
{
	static constexpr double halfC = M_PI / 180;

	// this is difficult to do due to an error: two points in the polygon lie in a straight line
	// if the requested points are very dense it refuses to draw the polygon
	// I got rid of that error for a moment in Graph.cpp line 218
	double increment = double(90) / N;
	int centerx = center.x;
	int centery = center.y;

	vector<Point> points;
	vector<Point> points1;
	vector<Point> points2;
	vector<Point> points3;
	vector<Point> points4;
	Polygon poly;
	Point p;



	for (double i = 0; i < 90; i+=increment) {
		//Quadrant +|+
		points1.push_back(Point{
				int(a*pow(abs(cos(i*halfC)),2/m)*scaling +centerx),
				int(b*pow(abs(sin(i*halfC)),2/n)*scaling +centery)
				});
		//Quadrant -|+
		points2.push_back(Point{
				int(-a*pow(abs(cos((i+90)*halfC)),2/m)*scaling +centerx),
				int(b*pow(abs(sin((i+90)*halfC)),2/n)*scaling +centery)
				});
		//Quadrant -|-
		points4.push_back(Point{
				int(-a*pow(abs(cos((i+180)*halfC)),2/m)*scaling +centerx),
				int(-b*pow(abs(sin((i+180)*halfC)),2/n)*scaling +centery)
				});
		//Quadrant +|-
		points3.push_back(Point{
				int(a*pow(abs(cos((i+270)*halfC)),2/m)*scaling +centerx),
				int(-b*pow(abs(sin((i+270)*halfC)),2/n)*scaling +centery)
				});
	}

	for (Point x : points1) points.push_back(x); 
	for (Point x : points2) points.push_back(x); 
	for (Point x : points4) points.push_back(x); 
	for (Point x : points3) points.push_back(x); 

	// Clean the points that are repetitive
	vector<Point> result {points[0]};
	for (int i = 1; i < points.size(); i++) {
		if (points[i] != points[i-1]) result.push_back(points[i]); 
	}
	
	return result;
}

int main()
{
	Point tl {100,100};              // top left corner of our window
	Point center {100+300,100+300};              // center of the ellipse
	int scaling {200};

	Simple_window win {tl,600,600,"Canvas"};
	win.label("My window");


	// I would have loved to use a for loop here but it doesn't seem
	// that straight forward. The Polygon class doesn't have the assignment =
	// operator overloaded. I can't reset the ebject at every cycle of the loop
	// maybe I am missing something though....
	double a,b,m,n;
	Polygon poly;

	a = double(rand()% 50+100) /100;
	b = double(rand()% 50+100) /100;
	m = double(rand()% 50+100) /100;
	// Starlike patterns are for 1 < n < 2
	n = double(rand()% 200+100) /100;

	cerr << 
		"a = " << a << '\n' <<
		"b = " << b << '\n' <<
		"m = " << m << '\n' <<
		"n = " << n << '\n';

	for (Point x : SuperEllipse(a,b,m,n,1000, scaling, center)) {
		cerr << "x = " << x.x << '\t' << "y = " << x.y << '\n';
		poly.add(x);
	}

	Polygon poly2;

	a = double(rand()% 50+100) /100;
	b = double(rand()% 50+100) /100;
	m = double(rand()% 50+100) /100;
	// Starlike patterns are for 1 < n < 2
	n = double(rand()% 200+100) /100;

	cerr << 
		"a = " << a << '\n' <<
		"b = " << b << '\n' <<
		"m = " << m << '\n' <<
		"n = " << n << '\n';

	for (Point x : SuperEllipse(a,b,m,n,1000, scaling, center)) {
		cerr << "x = " << x.x << '\t' << "y = " << x.y << '\n';
		poly2.add(x);
	}

	Polygon poly3;

	a = double(rand()% 50+100) /100;
	b = double(rand()% 50+100) /100;
	m = double(rand()% 50+100) /100;
	// Starlike patterns are for 1 < n < 2
	n = double(rand()% 200+100) /100;

	cerr << 
		"a = " << a << '\n' <<
		"b = " << b << '\n' <<
		"m = " << m << '\n' <<
		"n = " << n << '\n';

	for (Point x : SuperEllipse(a,b,m,n,1000, scaling, center)) {
		cerr << "x = " << x.x << '\t' << "y = " << x.y << '\n';
		poly3.add(x);
	}

	poly.set_color(Color::red);
	poly.set_color(Color::blue);
	poly.set_color(Color::green);

	poly.set_style(4);

	win.attach(poly);
	win.attach(poly2);
	win.attach(poly3);

	win.wait_for_button();   // display!
}


