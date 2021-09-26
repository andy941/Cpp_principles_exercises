
#include "../std_lib_facilities.h"
#include <random>
#include <functional>

using namespace std;

vector<int> gen_rand(unsigned seed, double n, int d)
{
	vector<int> v(n, 0);
	std::default_random_engine ran {seed};
	uniform_real_distribution<> ureal {0,n};
	for (int i = 0; i < d; ++i) {
		int r = ureal(ran);
		v[r] += 1;
	}
	return v;
}

int main () 
{
	unsigned int seed {1};
	double n {0};
	unsigned int d {10};

	cout << "insert a seed : ";
	cin >> seed;
	cout << "insert n : ";
	cin >> n;
	cout << "insert d : ";
	cin >> d;

	vector<int> result = gen_rand(seed,n,d);
	//sort(result);

	for (auto j = 0; j < result.size(); j++) {
		cout << j << "\t: ";
		for (int i = 0; i < result[j]; i++) {
			cout << "|";
		}
		cout << endl;
	}
}
