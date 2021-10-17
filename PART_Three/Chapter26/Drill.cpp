#include "../std_lib_facilities.h"
#include <algorithm>

using namespace std;

template <class RAIter, class T> bool alg(RAIter b, RAIter e, T t) {

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
    if (t <= *m)
      e = m - 1;
    if (t >= *m)
      b = m + 1;
    m = b + (e - b) / 2;
  }
  return false;
}

struct Test {
  string label{""};
  int val{0};
  vector<int> seq{};
  bool res{false};
  Test() = default;
};

istream &operator>>(istream &is, Test &t) {

  char r1;
  char r2;
  char l1;
  char l2;
  is >> l1 >> t.label >> t.val >> l2;
  if (l1 != '{' || l2 != '{') {
    is.clear(std::ios::failbit);
    return is;
  }

  for (int i; is >> i;) {
    t.seq.push_back(i);
  }
  is.clear();

  is >> r1 >> t.res >> r2;
  if (r1 != '}' || r2 != '}') {
    is.clear(std::ios::failbit);
    return is;
  }

  return is;
}

int test_all(istream &is) {
  int error_count = 0;
  for (Test t; is >> t; t = {}) {
    bool r = alg(t.seq.begin(), t.seq.end(), t.val);
    if (r != t.res) {
      cout << "failure: test " << t.label << " binary_search: " << t.seq.size()
           << " elements, val==" << t.val << " –> " << t.res << '\n';
      ++error_count;
    }
  }

  return error_count;
}

vector<int> generate_num(int min, int max, int length) {
  vector<int> v;
  v.reserve(length);
  for (int i = 0; i < length; i++)
    v.emplace_back(rand() % max + min);
  sort(v);
  return v;
}

vector<string> generate_s(int length, vector<string> s) {
  vector<string> v;
  v.reserve(length);
  for (int i = 0; i < length; i++)
    v.emplace_back(s[rand() % s.size()]);
  sort(v);
  return v;
}

template <class T>
void test_bin(const vector<vector<T>> tests, const vector<T> tofind,
              const vector<bool> answer) {
  int n = 0;
  for (auto x : tests) {
    cout << "Test num " << n + 1;
    if (alg(x.begin(), x.end(), tofind[n]) != answer[n])
      cout << " NOT PASSED";
    else
      cout << " PASSED";
    cout << endl;
    n++;
  }
}

template <class T> void print(vector<T> v) {
  for (auto &x : v)
    cout << x << ' ';
}

int main() {

  //// Read tests from file
  // ifstream ifs{"tests.txt"};
  // if (!ifs)
  //   return 1;
  // int errors = test_all(ifs);
  // cout << "number of errors: " << errors << "\n";

  //// Test a very large sequence
  constexpr int m = 10000000;
  vector<vector<int>> tests(1);
  tests[0] = generate_num(0, 100000, m);
  vector<int> tofind{tests[0][rand() % m]};
  vector<bool> answer{true};

  // cout << "Test large sequence of " << m << " values to find " << tofind[0]
  //      << endl;
  // test_bin(tests, tofind, answer);

  ////  Generate 10 tests of various sizes
  // tests.resize(10);
  // tofind.resize(10);
  // answer = {};
  // for (int i = 0; i < 10; i++) {
  //   tests[i] = generate_num(0, 10, rand() % 10);
  //   print(tests[i]);
  //   cout << endl;
  //   if (tests[i].size() != 0) {
  //     tofind[i] = tests[i][rand() % tests[i].size()];
  //     answer.push_back(true);
  //   } else {
  //     tofind[i] = 0;
  //     answer.push_back(false);
  //   }
  //   cout << i << endl;
  // }
  // test_bin(tests, tofind, answer);

  ////  Generate 10 tests of increasing sizes
  // tests.resize(10);
  // tofind.resize(10);
  // answer = {};
  // bool a = false;
  // cout << tests.size() << tofind.size() << answer.size() << endl;
  // for (int i = 0; i < 10; i++) {
  //   tests[i] = generate_num(0, 10, i);
  //   print(tests[i]);
  //   cout << endl;
  //   if (tests[i].size() != 0) {
  //     tofind[i] = tests[i][rand() % tests[i].size()];
  //     answer.push_back(true);
  //   } else {
  //     tofind[i] = 0;
  //     answer.push_back(false);
  //   }
  // }
  // test_bin(tests, tofind, answer);
  //
  //  Generate 10 tests of increasing sizes for strings
  vector<string> s;
  string word;
  ifstream ifs{"Drill.cpp"};
  while (ifs >> word)
    s.push_back(word);

  vector<vector<string>> tests_s(10);
  vector<string> tofind_s(10);
  vector<bool> answer_s;
  for (int i = 0; i < 10; i++) {
    tests_s[i] = generate_s(i, s);
    print(tests_s[i]);
    cout << endl;
    if (tests_s[i].size() != 0) {
      tofind_s[i] = tests_s[i][rand() % tests_s[i].size()];
      answer_s.push_back(true);
    } else {
      tofind_s[i] = "";
      answer_s.push_back(false);
    }
  }
  test_bin(tests, tofind, answer);
}
