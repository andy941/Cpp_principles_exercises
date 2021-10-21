
#include "../std_lib_facilities.h"
#include "Matrix/Matrix.h"
#include "Matrix/MatrixIO.h"
#include <chrono>
#include <map>

using namespace Numeric_lib;
using namespace std;

typedef Numeric_lib::Matrix<double, 2> _Matrix;

class Timer {

  std::chrono::high_resolution_clock::time_point begin =
      std::chrono::high_resolution_clock::now();

public:
  Timer() = default;
  ~Timer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time: \t\t\t\t%.10f seconds.\n", elapsed.count() * 1e-9);
  }
};

int main() {

  vector<int> tests{500000, 5000000};
  std::default_random_engine ran{};                   // generates integers
  uniform_real_distribution<> ureal{-100000, 100000}; // maps ints into doubles

  cout << "--- Vector of doubles ------------------" << endl;
  for (auto x : tests) {
    cout << "Elements = " << x << endl;
    vector<double> v;
    v.reserve(x);
    for (int i = 0; i < x; i++) {
      v.emplace_back(ureal(ran));
    }
    Timer t{};
    sort(v);
  }

  cout << "--- Vector of strings of random size ---" << endl;
  for (auto x : tests) {
    cout << "Elements = " << x << endl;
    vector<string> v(x);
    for (int i = 0; i < x; i++) {
      int len = rand() % 100;
      for (int j = 0; j < len; j++) {
        char c = rand() % (127 - 33) + 33;
        v[i].push_back(c);
      }
    }
    Timer t{};
    sort(v);
  }

  cout << "--- Map of strings of random size ---" << endl;
  for (auto x : tests) {
    cout << "Elements = " << x << endl;
    Timer t{};
    map<string, int> v;
    for (int i = 0; i < x; i++) {
      string s;
      int len = rand() % 100;
      s.reserve(len);
      for (int j = 0; j < len; j++) {
        char c = rand() % (127 - 33) + 33;
        s.push_back(c);
      }
      v[s]++;
    }
  }
}
