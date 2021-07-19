#include "../std_lib_facilities.h"

template<typename T> struct S { 

	explicit S(T v) :val{ v } { };
	const T& get() const;
	T& get();
	void set(T t);
	S<T>& operator=(const T& t);

	private:
	T val;
};

template<typename T> 
const T& S<T>::get() const
{
	return val; 
};

template<typename T> 
T& S<T>::get()			// Interesting solution would be to cast away the "const" for more invoved code.
{
	return val; 
};


template<typename T> 
void S<T>::set(T t) 
{ 
	val = t; 
};

template<typename T> 
S<T>& S<T>::operator=(const T& t)
{
	val = t;		// Doesn't allow type change, is it desirable/possible?
	return *this;
};

template<typename T> 
void read_val(T& t)
{
	auto tmp { t.get() };
	cin >> tmp;
	if (cin.fail()) return; 
	t = tmp;
}

int main() 
{
	S<int> s1 { 5 };
	S<char> s2 { 's' };
	S<double> s3 { 7.0 };
	S<string> s4 { "TODAY" };
	S<vector<int>> s5 { vector<int>{5,6,7} };

	cout << s1.get() << " <- " << &s1.get() << endl;
	cout << static_cast<void*>(&s2.get()) << " <- " << &s2.get() << endl;
	cout << s3.get() << " <- " << &s3.get() << endl;
	cout << s4.get() << " <- " << &s4.get() << endl;
	for (int& x : s5.get()) cout << x << " <- " << &x << '\t';
	cout << endl;

	cout << "-------------------" << endl;

	s1.set(6);
	s2.set('n');
	s3.set(8.0);
	s4.set("YESTERDAY");
	s5.set(vector<int>{10,11,21});

	cout << s1.get() << " <- " << &s1.get() << endl;
	cout << static_cast<void*>(&s2.get()) << " <- " << &s2.get() << endl;
	cout << s3.get() << " <- " << &s3.get() << endl;
	cout << s4.get() << " <- " << &s4.get() << endl;
	for (int& x : s5.get()) cout << x << " <- " << &x << '\t';
	cout << endl;

	cout << "-------------------" << endl;

	S<int> tmp {18};
	s1 = tmp;
	cout << s1.get() << " <- " << &s1.get() << endl;

	cout << "-------------------" << endl;

	read_val(s1);
	read_val(s2);
	read_val(s3);
	read_val(s4);

	cout << s1.get() << " <- " << &s1.get() << endl;
	cout << s2.get() << " <- " << &s2.get() << endl;
	cout << s3.get() << " <- " << &s3.get() << endl;
	cout << s4.get() << " <- " << &s4.get() << endl;
	cout << endl;
	
}
