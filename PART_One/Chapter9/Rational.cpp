#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

class Rational 
{
	int num {0};
	int den {1};

	public:
	Rational() {};
	Rational(int,int);
	int Num() const {return num;}
	int Den() const {return den;}
	double Convert() {return double(num)/den;}
	class Invalid_Denominator {};

};

// Check that the denominator is non zero and inizialize the class
Rational::Rational (int n, int d)
	:num{n},den{d}
{
	if (d ==0) throw Invalid_Denominator{};
}

// Operator overloading, give some useful operations

// The minimum common multiple could be found using the sets of prime numbers
// that are divisors of each denominator. but is a complicated implementation
// and I am lazy. So I did this awful one (that still works for small denominators).
Rational operator+(Rational l, Rational r)
{
	int den = l.Den() * r.Den();
	int num = (r.Den() * l.Num()) + (l.Den() * r.Num());
	Rational result {num,den};
	return result;
}

Rational operator-(Rational l, Rational r)
{
	int den = l.Den() * r.Den();
	int num = (den/r.Den() * l.Num()) - (den/l.Den() * r.Num());
	Rational result {num,den};
	return result;
}


Rational operator*(Rational l, Rational r)
{
	int den = l.Den() * r.Den();
	int num = l.Num() * r.Num();
	Rational result {num,den};
	return result;
}


Rational operator/(Rational l, Rational r)
{
	int den = l.Den() / r.Den();
	int num = l.Num() / r.Num();
	Rational result {num,den};
	return result;
}

bool operator==(Rational l, Rational r)
{
	return l.Convert() == r.Convert();

}

bool operator!=(Rational l, Rational r)
{
	return l.Convert() != r.Convert();

}

ostream& operator<<(ostream& os, Rational r)
{
	os << r.Num() << '/' << r.Den();
	return os;

}

int main ()
{

	try {

		Rational zero;
		Rational r1 {2,3};
		Rational r2 {5,2};

		cout << r1 + r2 << '\t' << r1 * r2 << '\n';

		return 0;
	}
	catch (Rational::Invalid_Denominator) {cerr << "Denominator must be != 0!\n";}
	catch (...) {cerr << "unknown exception";}

}
