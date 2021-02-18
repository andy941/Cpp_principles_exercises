#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include "../std_lib_facilities.h"
using namespace std;

struct Point 
{
	double x;
	double y;
};

// operator overload
istream& operator>>(istream& is, Point& p)
{
	char l,c,r;
	double x,y;

	if (is >> l && l != '(') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	is >> x >> c >> y >> r;
	//if (!is || r != ')') error("bad reading of a point");

	p.x = x;
	p.y = y;

	return is;
}

ostream& operator<<(ostream& os, Point& p)
{
	os << '(' << p.x << ',' << p.y << ')';
	return os;
}

int main () 
{
	ofstream ost {"mydata.txt"};           // ost is an output stream for a file named oname
	if (!ost) error("can't open output file ");

	vector<Point> original_points;

	for (int i = 0; i < 3 ; i++) {
		Point p; 
		cout << "Please insert a point coordinates in format (x,y)\n";
		cin>>p;
		original_points.push_back(p);
	}

	for (Point p : original_points) {ost << p << '\n'; cout << p << '\n';}

	ost.close(); // This is problematic, always better to put it in the scope of a function

	ifstream ist {"mydata.txt"};          // ist is an input stream for the file named name
	if (!ist) error("can't open input file ");

	cout << "Reading form file ... \n";
	vector<Point> processed_points;
	for (Point p; ist >> p;) {
		processed_points.push_back(p);
		if (cin.eof()) break;
	}

	for (Point p : processed_points) cout << p << '\n';

	if (original_points.size() != processed_points.size()) cerr << "Something went wrong!\n";
	return 0;
};
