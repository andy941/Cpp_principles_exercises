#include "../std_lib_facilities.h"
#include <algorithm>

using namespace std;

// the comparison function should return true when going to the "lower" value
// in a sequence of ordered values, following some arbitrary user specified
// criterion. It's difficult to test this one because the user could easily
// break the function using the wrong comparison.
template <class RAIter, class T>
bool alg(RAIter b, RAIter e, T t, bool (*cmp)(T, RAIter)) {

  if (b == e)
    return false;
  if (t > *(e - 1))
    return false;
  if (t < *b)
    return false;

  RAIter m = b + (e - b) / 2;
  while (b <= e) {
    if (t == *m)
      return true;
    // if (t <= *m)
    if (cmp(t, m))
      e = m - 1;
    // if (t >= *m)
    if (!cmp(t, m))
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
  char r2;
  char l1;
  char l2;
  is >> l1 >> t.label >> t.val >> l2;
  if (l1 != '{' || l2 != '{') {
    is.clear(std::ios::failbit);
    return is;
  }

  while (is >> r1 && r1 != '}') {
    is.putback(r1);
    T i;
    is >> i;
    t.seq.push_back(i);
  }
  cout << endl;
  is.putback(r1);

  is >> r1 >> t.res >> r2;
  if (r1 != '}' || r2 != '}') {
    is.clear(std::ios::failbit);
    return is;
  }

  return is;
}

template <class T> void print(vector<T> v) {
  for (auto &x : v)
    cout << x << ' ';
}

template <class T, class R> inline bool comparison(T t, R e) { return t < *e; }

template <class T> int test_all(istream &is) {
  int error_count = 0;
  for (Test<T> t; is >> t; t = {}) {
    sort(t.seq); // forgot to sort the names in the file;
    print(t.seq);
    cout << endl;
    bool r = alg(t.seq.begin(), t.seq.end(), t.val, comparison);

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
  ifstream ifs{"tests_strings.txt"};
  if (!ifs)
    return 1;
  int errors = test_all<string>(ifs);
  cout << "number of errors: " << errors << "\n";
}
