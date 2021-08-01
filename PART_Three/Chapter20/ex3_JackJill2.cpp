/*
 *
 * I assume the question means "try to iterate from both ends".
 *
 */

#include "../std_lib_facilities.h"

template<typename Iter>
Iter High(Iter f1, Iter e1)
{
	if(f1==e1) return e1;			// Check for empty

	--e1;		// The end points to the value AFTER the last element, put it back;
	Iter result = f1;
	while(f1<=e1) // while the pointers don't cross in the middle
	{
		if (*f1 > *result) result = f1;
		if (*e1 > *result) result = e1;
		++f1;
		--e1;
	}
	return result;
}

int main() 
{
	int* jack = new int[]{ 0, 1, 2, 12, 17, 19, 6, 7, 8, 9 };
	int jack_count = 10;		// Jack gives back the count of the elements int the array
	vector<int>* jill = new vector<int>{ 0, 1, 2, 3, 20, 15, 6, 7, 8 };
	vector<int>* empty = new vector<int>{  };

	cerr << "\nJack:\n ";
	for (int i = 0; i < 10; i++) 
	{
		cerr << jack[i] << '\t';
	}

	int* res_jack = High(jack, jack+jack_count);
	cout << "\nHighest Jack = " << *res_jack << endl;

	cerr << "\nJill:\n ";
	for (int i = 0; i < jill->size(); i++) 
	{
		cerr << (*jill)[i] << '\t';
	}

	vector<int>::iterator res_jill = High(jill->begin(), jill->end());
	cout << "\nHighest Jill = " << *res_jill << endl;

	vector<int>::iterator res_empty = High(empty->begin(), empty->end());
	if (res_empty==empty->end()) cout << "\nHighest empty = nullptr" << endl;

	delete[] jack;
	delete jill;
}



