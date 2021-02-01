#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;


class Money 
{
	long int amount {0};

	string currency {"USD"};
	vector<string> labels {"USD", "EUR", "GBP"};
	long int conv_table[3][3] = {
		{100,83,73},
		{121,100,88},
		{137,113,100},
	};

	int decimal {2};

	public:
	Money() {};
	Money(long int, string) {};
	Money(long int, string, int);
	long int Amount();
	string Curr() {return currency;};
	int Decimal() {return decimal;};
	void Conv(string);
};

Money::Money(long int aa, string cc, int dec)
{
	bool check;
	for (string x : labels) {if (x == cc) check = true;};
	if (!check) {cerr << "Error, Currency not in database\n"; return;};

	currency = cc;
	amount = aa;
	decimal = dec;
}

long int Money::Amount()
{

	return amount;
}

void Money::Conv(string b)
{
	string a {currency};

	bool check {false};
	for (string x : labels) {if (x == b) check = true;};
	if (!check) {cerr << "Error, Currency not in database\n"; return;};

	int x;
	int y;

	for (int i; i < labels.size(); i++) {
		if (labels[i] == a) x = i;
		if (labels[i] == b) y = i;
	}

	amount = amount * conv_table[x][y];
	cout << conv_table[x][y] << '\n';
	currency = b;
	decimal +=2;

}

//operator overloading
istream& operator>>(istream& is, Money& mon)
{
	long int aa;
	string cc;

	is >> cc >> aa;
	mon = Money(aa*100,cc);

	return is;
};

ostream& operator<<(ostream& os, Money& mon)
{
	int dec = pow(10, mon.Decimal());
	double am;

	if (mon.Amount() %(dec/10) >= 5*dec/100) am = ceil(double(mon.Amount()) / dec * 100) / 100;
	if (mon.Amount() %(dec/10) <= 5*dec/100) am = floor(double(mon.Amount()) / dec * 100) / 100;


	os << mon.Curr() << " " << am;
	return os;
};

Money operator+(Money& a, Money& b)
{

};

int main ()
{
	Money a {100, "EUR", 2};
	Money b {1358, "USD", 2};
	Money c {};

	a.Conv("USD");

	cout << a << '\n' << b << '\n' << c <<endl;
	return 0;
};
