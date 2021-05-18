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

class Scale {                   // data value to coordinate conversion
	int cbase;             // coordinate base
	int vbase;            // base of values
	double scale;
	public:
	Scale(int b, int vb, double s) :cbase{b}, vbase{vb}, scale{s} { }
	int operator()(int v) const { return cbase + (v-vbase)*scale; } // see §21.4
};

using namespace Graph_lib;

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

	DataFrame(vector<string> cn) :colnames{cn} { values = vector<vector<double>>(cn.size()); };
	void add_entry(vector<double> v);
	vector<double> calculate_means();
};

void DataFrame::add_entry(vector<double> v) 
{ 
	if (v.size() != colnames.size()) error("wrong number of values"); 

	for ( int i = 0; i < v.size(); i++ ) {
		values[i].push_back(v[i]); 
	}
}

vector<double> DataFrame::calculate_means()
{
	vector<double> v {};
	for ( vector<double> x : values ) { v.push_back( mean(x)); }
	return v;
}


class BarChart : public Shape
{
	Vector_ref<Rectangle> bars;
	Vector_ref<Text> labels;
	bool color;
	Scale xs;
	Scale ys;
	DataFrame df;
	Point origin;

	public:
	BarChart ( DataFrame& df, Point origin, double scalex, double scaley, bool color );
	void color_switch(bool c) { color = c; };
	void draw_lines() const override;
};

BarChart::BarChart ( DataFrame& df, Point origin, double scalex, double scaley, bool color )
	:df{df}, xs{Scale{origin.x, 0, scalex}}, ys{Scale{origin.y, 0, -scaley}}, origin{origin}
{ // The origin is defined has the bottom-left point, usually the origin of the axes
	vector<double> means = df.calculate_means();

	// Calculate Shapes
	for ( int i = 0; i < means.size(); i++ ) {
		Point rect1 { xs(i), ys(means[i]) };
		Point rect2 { xs(i+1), origin.y };
		bars.push_back(new Rectangle{ rect1, rect2 });

		labels.push_back( new Text{ Point{ rect1.x, rect2.y + 15 }, df.colnames[i] } );
	}

	// colorize?
	if (color) {
		for (int i = 0; i < bars.size(); i++) bars[i].set_fill_color(i+1);
	}
}

void BarChart::draw_lines() const
{
	for (int i = 0; i < bars.size(); i++) bars[i].draw_lines();
	for (int i = 0; i < labels.size(); i++) labels[i].draw_lines();
}

int main()
{
	constexpr int xmax = 600;                 // window size
	constexpr int ymax = 600;

	constexpr int x_orig = 100;         // position of (0,0) is center of window
	constexpr int y_orig = 500;
	constexpr Point orig {x_orig,y_orig};

	constexpr int xoffset = 100;  // distance from left-hand side of window to y axis
	constexpr int yoffset = 100;  // distance from bottom of window to x axis

	constexpr int xspace = 100;  // space beyond axis
	constexpr int yspace = 100;

	constexpr int xlength = 400;
	constexpr int ylength = 400;

	constexpr int xscale = double(xlength)/3;
	constexpr int yscale = double(ylength)/5;

	constexpr Point tl {100,100};              // top left corner of our window

	constexpr int lim_l = -10;
	constexpr int lim_r = 11;

	Graph_lib::Window win {tl,xmax,ymax,"Function Graphs"};



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

	BarChart bc { df, orig, xscale, yscale, true};

	Axis x {Axis::x,orig, xlength, int(colnames.size()), ""};
	Axis y {Axis::y,orig, ylength, yscale, ""};

	win.attach(x);
	win.attach(bc);
	win.attach(y);

//-----------------------------------------------------------------------------
	gui_main();
}



