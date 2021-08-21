#include "../std_lib_facilities.h"

struct Item 
{
	string name;
	int iid;
	double value;

	explicit Item() = default;
	Item (string name, int iid, double value) :name{name}, iid{iid}, value{value} {  };
};

istream& operator>>(istream& is, Item& item)
{
	char comma = ',';
	char c;
	string name;

	while (is.get(c)) {	
		if (c == ',') break;
		if (isalpha(c) || c == ' ') name.push_back(c);
	}

	item.name = name;
	is >> item.iid >> comma >> item.value;
	if (comma != ',') error("bad format, not CSV");
	return is;
}

ostream& operator<<(ostream& os, Item& item)
{
	cout << item.name << '\t' << '\t' << item.iid << '\t' << item.value;
	return os;
}

int main() 
{
	// Vector version
	ifstream ifs { "Items.csv" };
	istream_iterator<Item> ii {ifs}; 
	istream_iterator<Item> eos; 
	vector<Item> vi { ii, eos };
	for (Item& x : vi) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Sorting by name |........" << endl;
	sort(vi.begin(), vi.end(), [](Item& x, Item& y) { return x.name < y.name; });
	for (Item& x : vi) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Sorting by iid |........" << endl;
	sort(vi.begin(), vi.end(), [](Item& x, Item& y) { return x.iid > y.iid; });
	for (Item& x : vi) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Sorting by value |........" << endl;
	sort(vi.begin(), vi.end(), [](Item& x, Item& y) { return x.value > y.value; });
	for (Item& x : vi) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Add two Items and erase two others |........" << endl;
	vi.push_back(Item{ "horse shoe", 99, 12.34 });
	vi.push_back(Item{ "Canon S400", 9988, 499.95 });

	cout << endl;
	for (Item& x : vi) cout << x << endl;
	cout << endl;

	auto it = find_if(vi.begin(), vi.end(), [](Item& it) { return it.name == "Andrea"; });
	vi.erase(it);
	it = find_if(vi.begin(), vi.end(), [](Item& it) { return it.name == "Bennett"; });
	vi.erase(it);

	cout << endl;
	for (Item& x : vi) cout << x << endl;
	cout << endl;
	cout << endl;

	// List version
	ifstream ifs_l { "Items.csv" };
	istream_iterator<Item> ii_l {ifs_l}; 
	istream_iterator<Item> eos_l; 
	list<Item> li { ii_l, eos_l };

	for (Item& x : li) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Sorting by name |........" << endl;
	li.sort([](Item& x, Item& y) { return x.name < y.name; });
	for (Item& x : li) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Sorting by iid |........" << endl;
	li.sort([](Item& x, Item& y) { return x.iid > y.iid; });
	for (Item& x : li) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Sorting by value |........" << endl;
	li.sort([](Item& x, Item& y) { return x.value > y.value; });
	for (Item& x : li) cout << x << endl;
	cout << endl;
	cout << endl;

	cout << "........| Add two Items and erase two others |........" << endl;
	li.push_back(Item{ "horse shoe", 99, 12.34 });
	li.push_back(Item{ "Canon S400", 9988, 499.95 });

	cout << endl;
	for (Item& x : li) cout << x << endl;
	cout << endl;

	auto it_l = find_if(li.begin(), li.end(), [](Item& it) { return it.name == "Andrea"; });
	li.erase(it_l);
	it_l = find_if(li.begin(), li.end(), [](Item& it) { return it.name == "Bennett"; });
	li.erase(it_l);

	cout << endl;
	for (Item& x : li) cout << x << endl;
	cout << endl;
	cout << endl;

	// Use a Map
	map<string,int> msi;
	for (auto it = vi.begin(); it != vi.end(); it++) {
		msi[it->name]=it->iid;
	}

	cout << endl;
	for (pair<string,int> x : msi) cout << x.first << " : " << x.second << endl;
	cout << endl;
	cout << endl;

	cout << "........| Erase Whatever |........" << endl;
	auto mit = msi.find("Whatever");
	if (mit == msi.end()) cerr << "NULL" << endl;
	msi.erase(mit);
	cout << endl;
	for (pair<string,int> x : msi) cout << x.first << " : " << x.second << endl;
	cout << endl;
	cout << endl;

	cout << "........| Sum the values |........" << endl;
	double sum = accumulate(msi.begin(), msi.end(), 0, 
			[&](double a, pair<string,double> b){ return a + b.second; });
	cout << endl;
	cout << "The sum is " << sum << endl;
	cout << endl;
	cout << endl;

	map<int,string> mis;
	for (auto it = msi.begin(); it != msi.end(); it++) {
		mis[it->second]=it->first;
	}

	cout << endl;
	for (auto& x : mis) cout << x.first << " : " << x.second << endl;
	cout << endl;
	cout << endl;

	// More Vector use
	vector<double> vd;
	for (Item& x : vi) vd.push_back(x.value); 
	vector<int> vin(vd.size());
	copy(vd.begin(), vd.end(), vin.begin());

	cout << endl;
	for (unsigned int i = 0; i < vi.size(); i++) {
		cout << vd[i] << '\t' << vin[i] << endl;
	}
	cout << endl;
	cout << endl;

	cout << "........| Operations |........" << endl;
	double dsum = accumulate(vd.begin(), vd.end(), 0.0);
	int isum = accumulate(vin.begin(), vin.end(), 0);
	cout << endl;
	cout << "The sum is " << dsum << endl;
	cout << "The difference is " << dsum - isum << endl;
	cout << "The mean is " << dsum/vd.size() << endl;
	cout << endl;
	cout << endl;

	cout << "........| Reverse vd |........" << endl;
	cout << endl;
	for (unsigned int i = 0; i < vd.size(); i++) {
		cout << vd[i] << '\t';
	}
	reverse(vd.begin(), vd.end());
	cout << endl;
	for (unsigned int i = 0; i < vd.size(); i++) {
		cout << vd[i] << '\t';
	}
	cout << endl;
	cout << endl;

	cout << "........| conditional copy vd |........" << endl;
	int s = accumulate(vd.begin(), vd.end(), 0, 
			[&](int a, double b)
			{ 
			if (b < dsum/vd.size()) return ++a; 
			return a;
			});
	cout << "Size: " << s << endl;
	vector<double> vd2(s);	
	copy_if(vd.begin(), vd.end(), vd2.begin(), 
			[&](auto x) { return x < dsum/vd.size(); });
	for (auto& x : vd2) cout << x << '\t';
	cout << endl;
	sort(vd.begin(), vd.end());
	for (auto& x : vd) cout << x << '\t';
	cout << endl;
}



