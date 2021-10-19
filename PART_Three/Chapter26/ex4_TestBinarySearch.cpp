#include "../std_lib_facilities.h"
#include <algorithm>

using namespace std;

template <class RAIter, class T> bool alg(RAIter b, RAIter e, T t) {

  if (b == e)
    return true; // Trigger error
  if (t > *(e - 1))
    return false;
  if (t < *b)
    return false;

  RAIter m = b + (e - b) / 2;
  while (b <= e) {
    if (t == *m)
      return true;
    if (t <= *m)
      e = m - 1;
    if (t >= *m)
      b = m + 1;
    m = b + (e - b) / 2;
  }
  return false;
}

template <class T> struct Test {
  string label{""};
  T val{};
  vector<T> seq{};
  bool res{false};
  Test() = default;
};

template <class T> istream &operator>>(istream &is, Test<T> &t) {

  char r1;
  char l1;
  is >> l1 >> t.label >> t.val >> t.res >> r1;
  if (l1 != '{' || r1 != '}') {
    is.clear(std::ios::failbit);
    return is;
  }
  return is;
}

template <class T> void read_seq(istream &is, vector<T> &v) {
  char r1;
  char r2;
  char l1;
  char l2;
  is >> l1 >> l2;
  if (l1 != '{' || l2 != '{') {
    is.clear(std::ios::failbit);
    return;
  }

  while (is >> r1 && r1 != '}') {
    is.putback(r1);
    T i;
    is >> i;
    v.push_back(i);
  }
  cout << endl;
  is.putback(r1);

  is >> r1 >> r2;
  if (r1 != '}' || r2 != '}') {
    is.clear(std::ios::failbit);
    return;
  }

  return;
}

template <class T> void print(vector<T> v) {
  for (auto &x : v)
    cout << x << ' ';
}

template <class T> int test_all(istream &is) {
  vector<T> v;
  read_seq(is, v);
  sort(v);
  int error_count = 0;
  for (Test<T> t; is >> t; t = {}) {
    t.seq = v;
    print(t.seq);
    cout << endl;
    bool r = alg(t.seq.begin(), t.seq.end(), t.val);
    if (r != t.res) {
      cout << "failure: test " << t.label << " binary_search: " << t.seq.size()
           << " elements, val==" << t.val << " –> " << t.res << '\n';
      ++error_count;
    }
  }

  return error_count;
}

int main() {

  // Read tests from file
  ifstream ifs{"tests_multiple.txt"};
  if (!ifs)
    return 1;
  int errors = test_all<string>(ifs);
  cout << "number of errors: " << errors << "\n";
}
