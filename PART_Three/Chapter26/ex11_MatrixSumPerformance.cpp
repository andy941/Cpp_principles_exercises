#include "../std_lib_facilities.h"
#include "Matrix/Matrix.h"
#include "Matrix/MatrixIO.h"
#include <chrono>

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

_Matrix random_matrix(Index n) {
  _Matrix v(n, n);
  std::default_random_engine ran{};           // generates integers
  uniform_real_distribution<> ureal{-10, 10}; // maps ints into doubles

  for (Index i = 0; i < v.dim1(); i++) {
    for (Index j = 0; j < v.dim2(); j++) {
      v[i][j] = ureal(ran);
    }
  }
  return v;
}

double row_sum(_Matrix m, int n) {
  double sum = 0;
  for (Index i = 0; i < m.dim2(); i++)
    sum += m(n, i);
  return sum;
}
double row_accum(_Matrix m, int n) // sum of elements in m[0:n)
{
  double s = 0;
  for (int i = 0; i < n; ++i) {
    s += row_sum(m, i);
  }
  return s;
}

void tests_alloc(const vector<int> &tests, vector<_Matrix> &matrix_tests) {
  cout << "Allocating matrices" << endl;
  for (int x : tests) {
    cout << "Allocating " << x << endl;
    matrix_tests.push_back(random_matrix(sqrt(x)));
  }
}

int main() {
  vector<int> tests{100, 10000, 1000000, 100000000}; // Number of elements
  vector<_Matrix> matrix_tests;
  tests_alloc(tests, matrix_tests);

  {
    cout << "Naive method O(N2)" << endl;
    for (auto x : matrix_tests) {
      cout << "Elements = " << x.size() << endl;
      Timer t{};
      vector<double> v;
      for (int i = 0; i < x.dim1(); ++i)
        v.push_back(row_accum(x, i + 1));
      cout << "SUM = " << v.back() << endl;
    }
  }

  {
    cout << "fast method O(N)" << endl;
    for (auto x : matrix_tests) {
      cout << "Elements = " << x.size() << endl;
      Timer t{};
      vector<double> v;
      double tmp = 0;
      for (int i = 0; i < x.dim1(); ++i) {
        v.push_back(tmp + row_sum(x, i));
        tmp = v[i];
      }
      cout << "SUM = " << v.back() << endl;
    }
  }
}
