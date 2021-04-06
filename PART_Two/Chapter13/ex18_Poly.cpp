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

using namespace Graph_lib;

inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel) 
{
    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;
    double x4 = p4.x;
    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;
    double y4 = p4.y;

    double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
    if (denom == 0){
        parallel= true;
        return pair<double,double>(0,0);
    }
    parallel = false;
    return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
                                ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}

//------------------------------------------------------------------------------

//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
}

struct Poly : Closed_polyline
{
    Poly() {};

	// the original way was to use an inizilizer_list but that can't be subscripted
	// and I can't find a way around it with the thighs I know so far in the book.
    Poly(vector<Point> lst);


};

Poly::Poly (vector<Point> lst)
{
	if (lst.size() < 3) error("vertices have to be > 2 ... \n");

	// if 3 vertices no need to check anything
	if (lst.size() >3) {

		Point ignore{0,0};

		for (int i = 2; i < lst.size(); i++) {

			for (int j = 1; j < i-1; j++) {

				if (line_segment_intersect(lst[i], lst[i-1], lst[j], lst[j-1], ignore)) {
					cerr << ignore.x << ',' << ignore.y << '\n'; error("intersect in polygon");
				}
			}
		}
	
	}

	// If all checks are passed and no error thrown add the points
	for (Point x : lst ) Closed_polyline::add(x); 
};

int main()
{
	Point tl {100,100};              // top left corner of our window

	Simple_window win {tl,800,1200,"Canvas"};
	win.label("My window");

	// This shouldn't work
	Poly pol {vector<Point>{{100,100},{300,100},{300,300},{150,50}}};
	win.attach(pol);

	win.wait_for_button();   // display!
}







