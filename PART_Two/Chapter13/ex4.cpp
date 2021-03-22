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

Point n(const Rectangle& r)
{
	Point p {r.point(0).x + r.width()/2, r.point(0).y};
	return p;
}

Point s(const Rectangle& r)
{
	Point p {r.point(0).x + r.width()/2, r.point(0).y + r.height()};
	return p;
}

Point e(const Rectangle& r)
{
	Point p {r.point(0).x + r.width()/2, r.point(0).y + r.height()/2};
	return p;
}

Point w(const Rectangle& r)
{
	Point p {r.point(0).x, r.point(0).y + r.height()/2};
	return p;
}

Point center(const Rectangle& r)
{
	Point p {r.point(0).x + r.width()/2, r.point(0).y + r.height()/2};
	return p;
}

Point ne(const Rectangle& r)
{
	Point p {r.point(0).x + r.width(), r.point(0).y};
	return p;
}

Point se(const Rectangle& r)
{
	Point p {r.point(0).x + r.width(), r.point(0).y + r.height()};
	return p;
}

Point sw(const Rectangle& r)
{
	Point p {r.point(0).x, r.point(0).y + r.height()};
	return p;
}

Point nw(const Rectangle& r)
{
	return r.point(0);
}

int main()
{
	Rectangle r {Point{100,100}, 100, 200};
	cout << "n=  " << n(r).x << "," << n(r).y << '\n' <<
		"s=  " << s(r).x << "," << s(r).y << '\n' <<
		"e=  " << e(r).x << "," << e(r).y << '\n' <<
		"w=  " << w(r).x << "," << w(r).y << '\n' <<
		"center=  " << center(r).x << "," << center(r).y << '\n' <<
		"ne=  " << ne(r).x << ","<< ne(r).y << '\n' <<
		"se=  " << se(r).x << ","<< se(r).y << '\n' <<
		"sw=  " << sw(r).x << ","<< sw(r).y << '\n' << 
		"nw=  " << nw(r).x << ","<< nw(r).y << '\n';
}





