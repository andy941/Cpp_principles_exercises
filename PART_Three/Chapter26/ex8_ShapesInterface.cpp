#include "../hello_fltk/Graph.h"
#include "../hello_fltk/Window.h"
#include <vector>
//#include "../std_lib_facilities.h"

/*
 * The only way to make this work is to clone this repository:
 *		https://github.com/cortical-iv/hello_fltk.git
 *
 *	g++ -w -Wall -std=c++11 <file.cpp> Graph.cpp Window.cpp GUI.cpp
 *	Simple_window.cpp `fltk-config --ldflags --use-images` -o <file.o>
 *
 */

using namespace std;
using namespace Graph_lib;

template <class T> void print(ostream &os, vector<T> v) {
  for (auto &x : v)
    os << x << ' ';
}

struct shape_descr {
  string sh;
  vector<int> coord;
  vector<int> dim;
};

istream &operator>>(istream &is, shape_descr &sd) {

  char lb, lc, rc, ld, rd, rb;
  is >> lb;
  if (lb != '{') {
    is.clear(std::ios::failbit);
    return is;
  }
  is >> sd.sh;
  is >> lc;
  if (lc != '{') {
    is.clear(std::ios::failbit);
    return is;
  }

  while (is >> rc && rc != '}') {
    is.putback(rc);
    int i;
    is >> i;
    sd.coord.push_back(i);
  }

  is >> ld;
  if (ld != '{') {
    is.clear(std::ios::failbit);
    return is;
  }

  while (is >> rd && rd != '}') {
    is.putback(rd);
    int i;
    is >> i;
    sd.dim.push_back(i);
  }

  is >> rb;
  if (rb != '}') {
    is.clear(std::ios::failbit);
    return is;
  }

  return is;
}

ostream &operator<<(ostream &os, const shape_descr &sd) {
  os << "{ " << sd.sh << " { ";
  print(os, sd.coord);
  os << "} { ";
  print(os, sd.dim);
  os << "} }";
  return os;
}

void read_shapes(istream &is, vector<shape_descr> &v) {
  for (shape_descr sd; is >> sd; sd = {}) {
    v.push_back(sd);
  }
}

vector<Shape *> create_shapes(vector<shape_descr> &v) {
  vector<Shape *> vs(v.size());
  for (auto x : v) {
    if (x.sh == "circle")
      vs.push_back(new Circle{Point{x.coord[0], x.coord[1]}, x.dim[0]});
    if (x.sh == "rectangle")
      vs.push_back(
          new Rectangle{Point{x.coord[0], x.coord[1]}, x.dim[0], x.dim[1]});
  }
}

int main() {
  ifstream ifs{"shapes_interface.txt"};
  if (!ifs)
    error("File not found\n");
  vector<shape_descr> vsd;
  read_shapes(ifs, vsd);
  for (shape_descr &sd : vsd)
    cout << sd << endl;

  constexpr int xmax = 600; // window size
  constexpr int ymax = 600;
  constexpr Point tl{100, 100}; // top left corner of our window
  Graph_lib::Window win{tl, xmax, ymax, "Shapes"};

  vector<Shape *> shapes = create_shapes(vsd);
  for (Shape *sd : shapes) {
    win.attach(*sd);
  }

  gui_main();
}
