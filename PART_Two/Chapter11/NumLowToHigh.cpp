
#include "../std_lib_facilities.h"

int main()
{
	vector<double> nums;
	double y;
	int count;

	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs {iname};
	if (!ifs) error("can't open input file ",iname);
	
	for (double n; ifs >> n;) nums.push_back(n);
	sort(nums.begin(), nums.end());
	y = nums[0];

	//for (int i = 0; i < nums.size(); i++) {
	for (double x : nums) {

		if (x == y) {count +=1; continue;}

		if (count == 1) cout << y << '\n';
		else cout << y << '\t' << count << '\n';

		y = x;
		count = 1;
	}

	cout << '\n';

	return 0;
}
