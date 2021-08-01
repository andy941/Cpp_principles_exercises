#include "../std_lib_facilities.h"

template<typename Iter>
Iter High(Iter f1, Iter e1)
{
	if(f1==e1) return e1;			// Check for empty

	Iter result = f1;
	while(f1!=e1) {
		if (*f1 > *result) result = f1;
		++f1;
	}
	return result;
}

int main() 
{
	int* jack = new int[]{ 0, 1, 2, 12, 4, 5, 6, 7, 8, 9 };
	int jack_count = 10;		// Jack gives back the count of the elements int the array
	vector<int>* jill = new vector<int>{ 0, 1, 2, 3, 21, 5, 6, 7, 8, 9 };
	vector<int>* empty = new vector<int>{  };

	cerr << "\nJack:\n ";
	for (int i = 0; i < 10; i++) 
	{
		cerr << jack[i] << '\t';
	}

	int* res_jack = High(jack, jack+jack_count);
	cout << "\nHighest Jack = " << *res_jack << endl;

	cerr << "\nJill:\n ";
	for (int i = 0; i < 10; i++) 
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



