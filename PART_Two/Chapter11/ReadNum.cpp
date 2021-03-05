#include "../std_lib_facilities.h"

int main()
{
	vector<double> nums;

	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open input file ",iname);
	
	for (double n; ifs >> n;) nums.push_back(n);

	cout << scientific << setprecision(8);

	for (int i = 0; i < nums.size(); i++) {

		if (i % 4 == 0 ) {cout << '\n' << setw(5) << nums[i] << '\t'; continue;}
		cout << setw(5) << nums[i] << '\t';
	}

	cout << '\n';

	return 0;
}



