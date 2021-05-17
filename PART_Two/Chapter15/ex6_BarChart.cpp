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

#include "../hello_fltk/Window.h"  
#include "../hello_fltk/Graph.h"
#include<numeric>

using namespace Graph_lib;

// I used a modified version of the famous iris dataset. I will calculate the means of the 
// first three columns and draw a barchart.

//bool find (const string& name, const vector<string>& vec) 
//{
//	for (string x : vec ) {
//		if ( x == name ) return true;
//	}
//	return false;
//}

vector<string> split ( const string& line, const string& delim = ",")
{
	char x;
	vector<string> v;
	string token;
	istringstream iss { line };

	while ( iss >> x ) {

		if ( x == ',' ) {
			v.push_back(token);
			token = {};
			continue;
		}

		token.push_back(x);
	}

	v.push_back(token);

	return v;
}

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

double mean( vector<double> L )
{
	   return accumulate( L.begin(), L.end(), 0.0 ) / (double)L.size();
}

struct DataFrame
{
	vector<string> colnames;
	vector<vector<double>> values;
	vector<double> means;

	DataFrame(vector<string> cn) :colnames{cn} { values = vector<vector<double>>(cn.size()); };
	void add_entry(vector<double> v);
	void calculate_means();
};

void DataFrame::add_entry(vector<double> v) 
{ 
	if (v.size() != colnames.size()) error("wrong number of values"); 

	for ( int i = 0; i < v.size(); i++ ) {
		values[i].push_back(v[i]); 
	}
}

void DataFrame::calculate_means()
{
	for ( vector<double> x : values ) { means.push_back( mean(x)); }
}

//{
//		if ( find( name, colnames ) ) {
//			for (int i =0 ; i < colnames.size(); i++) {
//				if (name == colnames[i]) values[i].push_back(value); return;
//			}
//		} else { 
//			colnames.push_back(name); 
//			values.push_back(vector<double> {value}); 
//		}
//	}
//

class BarChart
{
};

int main()
{
	constexpr int xmax = 600;                 // window size
	constexpr int ymax = 600;

	constexpr int x_orig = 300;         // position of (0,0) is center of window
	constexpr int y_orig = 300;
	constexpr Point orig {x_orig,y_orig};

	constexpr int xoffset = 100;  // distance from left-hand side of window to y axis
	constexpr int yoffset = 100;  // distance from bottom of window to x axis

	constexpr int xspace = 100;  // space beyond axis
	constexpr int yspace = 100;

	constexpr int xlength = 400;
	constexpr int ylength = 400;

	constexpr int scale = 20;

	constexpr Point tl {100,100};              // top left corner of our window

	constexpr int lim_l = -10;
	constexpr int lim_r = 11;

	Graph_lib::Window win {tl,xmax,ymax,"Function Graphs"};

	Axis x {Axis::x,Point{xspace,y_orig}, xlength, scale, ""};
	Axis y {Axis::y,Point{x_orig, ylength+yspace}, ylength, scale, ""};

	win.attach(x);
	win.attach(y);

//-----------------------------------------------------------------------------

	ifstream ifs { "iris.csv" };

	string line;
	
	getline(ifs, line);
	vector<string> colnames = split(line, ",");

	DataFrame df { colnames };

	while ( getline(ifs, line) ) {
		vector<double> values = split_val(line, ",");
		df.add_entry(values);
	}

	df.calculate_means();
	for (double x : df.means) cerr << x << '\n';


//-----------------------------------------------------------------------------
	//gui_main();
}



