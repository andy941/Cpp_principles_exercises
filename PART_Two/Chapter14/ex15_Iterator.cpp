
/*
 * It would be nice to be able to use a vector reference to construct the class
 * and then move the pointer in next() with vector arithmetics.
 * I can't get it to work with vector but maybe is only possible with array indexing.
 * it's elegant where the *array[] pointer points to the first element already.
 * This was eye opening --> https://www3.ntu.edu.sg/home/ehchua/programming/cpp/cp4_PointerReference.html
 */

#include "std_lib_facilities.h"           // if we want that “Next” button

using namespace std;

class Iter 
{
	protected:
		virtual double* next() =0;
};

class Vector_iterator : public Iter
{
	vector<double> vec {};
	int index {0};

	public:
	Vector_iterator() {};
	Vector_iterator (vector<double> v): vec{v} {};

	double* next () override 
	{ 
		if (index >= vec.size()) error("vector out of range.");

		double* result = &vec[index];
		index += 1;
		return result;
	};
};


class List_iterator : public Iter
{
	list<double> lst;
	list<double>::iterator it {lst.begin()};
	list<double>::iterator end {lst.end()};

	public:
	List_iterator() {};
	List_iterator (list<double> l): lst{l} {};

	double* next () override 
	{ 
		if (it == end) error("list out of range.");					// this is probably wrong to rely on ...

		double* result = &(*it);

		std::advance(it, 1);

		return result;
	};
};

int main () 
{
    vector<double> vec {34.0, 45.0, 34.4};
	Vector_iterator iterator { vec };

	cout << *iterator.next() << '\n';
	cout << *iterator.next() << '\n';
	cout << *iterator.next() << '\n';
	//cout << *iterator.next() << '\n';

    list<double> lst {34.0, 45.0, 34.4};
	List_iterator iterator2{ lst };

	cout << *iterator2.next() << '\n';
	cout << *iterator2.next() << '\n';
	cout << *iterator2.next() << '\n';
	cout << *iterator2.next() << '\n';

	return 0;
}
