#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

class Name_pairs 
{
	vector<string> names {};
	vector<double> ages {};

	public:
	void read_names();
	void read_ages();
	ostream& print(ostream&);
	void sort();
	vector<string> names_vec() {return names;}
	vector<double> ages_vec() {return ages;}
};

void Name_pairs::read_names() 
{
	string name;

	while (true) {
	cout << "\nPlease insert a name (end with 'end'): ";
	cin >> name;
	if (name == "end") break;
	names.push_back(name);
	}

}

void Name_pairs::read_ages() 
{
	double age;

	for (string x : names) {
		cout << "\nPlease insert " << x << "'s age: ";
		cin >> age;
		ages.push_back(age);
	}
}

ostream& operator<<(ostream& os, Name_pairs& np)
{
	vector<string> names = np.names_vec();
	vector<double> ages = np.ages_vec();

	os << '\n' << "Names" << '\t' << "Ages" << '\n';

	for (int i = 0; i < names.size(); i++) {
		os << names[i] << '\t' << ages[i] << '\n';
	}
	return os;
}

void Name_pairs::sort() 
{
	vector<double> ordered(names.size());
	vector<string> copy = names;

	std::sort(names.begin(), names.end());
	
	for (int i = 0; i < names.size(); i++) {
		for (int j = 0; j < names.size(); j++) {
			if (copy[i] == names[j]) ordered[j] = ages[i];
		}
	}
	ages = ordered;
}

int main () 
{
	Name_pairs pairs;

	pairs.read_names();
	pairs.read_ages();
	cout << pairs;

	cout << "\nAfter sorting...";
	pairs.sort();
	cout << pairs;

	return 0;
}
