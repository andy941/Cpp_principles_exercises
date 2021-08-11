
#include "../Chapter19/ex13_Tracer.cpp"
#include "../std_lib_facilities.h"

template<typename T>
class ovector { 

	vector<T*> elem;

public:

	explicit ovector() = default;

	explicit ovector(int s) 
		:elem{vector<T*>(s, new T{0})}
	{
	}

	ovector(const ovector& v)                            // copy constructor
		:elem{vector<T*>(v.size(), new T{0})}			// I think this is awful
	{
		for (int i = 0; i < v.size(); i++) elem[i] = new (elem[i]) T{v[i]};
	}

	ovector& operator=(const ovector& v)					 // copy assignment
	{
		if (this==&v) return *this;
	
		elem.resize(v.size());
		for (int i = 0; i < v.size(); i++) elem[i] = new (elem[i]) T{v[i]};

		return *this;
	}

	ovector(ovector&& v)                                  // move constructor
		:elem{v.elem}
	{
		for ( auto it = v.elem.begin(); it != v.elem.end(); it++ ) {
			if (*it) (*it)->~T();
			*it = nullptr;
		}
	}

	ovector& operator=(ovector&& v)						 // move assignment
	{
		elem.resize(v.size());
		elem = v.elem;

		for ( auto it = v.elem.begin(); it != v.elem.end(); it++ ) {
			if (*it) (*it)->~T();
			*it = nullptr;
		}

		return *this;
	}

	~ovector()
	{
		for ( auto it = elem.begin(); it != elem.end(); it++ ) {
			if (*it) (*it)->~T();
		}
	}

	T& operator[](int n) { return *elem[n]; }					 // access: return reference
	const T& operator[](int n) const { return *elem[n]; }

	int size() const { return elem.size(); }                            // the current size
	int capacity() const { return elem.capacity(); }

	void resize(int newsize) { elem.resize(newsize); }
	void push_back(const T* val) { elem.push_back(val); }
	void push_back(T* val) { elem.push_back(val); }
	void reserve(int newalloc) { elem.reserve(newalloc) ;}
};

int main() 
{
	//ovector<ovector<ovector<int>>> v_empty;
	ovector<int> v_empty;

	cerr << "---------------------------------------------------" << endl;
	cerr << "Checking size of implementation:\n" <<
		"sizeof(int) = " << sizeof(int*)	<< '\t' <<
		"sizeof(vector<int>) = " << sizeof(v_empty) << endl;
	cerr << "---------------------------------------------------" << endl;

	ovector<Tracer> v {};
	ovector<Tracer> v2 {};

	for (int i = 0; i < 8; i++) v.push_back(new Tracer(i));
	for (int i = 0; i < 8; i++) v2.push_back(new Tracer(i));

	for (int i = 0; i < v.size(); i++) cerr << v[i].num << '\t';
	cerr << endl;
	for (int i = 0; i < v2.size(); i++) cerr << v2[i].num << '\t';
	cerr << endl;

	v2 = v;
	v2.push_back(new Tracer{888});

	cerr << "---------------------------------------------------" << endl;
	for (int i = 0; i < v2.size(); i++) cerr << v2[i].num << '\t';
	cerr << endl;

	ovector<Tracer> v3 = v;
	v3 = move(v);
	ovector<Tracer> v4 = move(v);

	for (int i = 0; i < v3.size(); i++) cerr << v3[i].num << '\t';
	cerr << endl;
}
