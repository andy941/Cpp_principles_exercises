
#include "ex13_Tracer.cpp"
#include "../std_lib_facilities.h"

template<typename T>
class VectorLight {                // read “for all types T” (just like in math)

	vector<T>* elem {nullptr};

public:

	VectorLight() :elem{new vector<T>()} {  };

	explicit VectorLight(int s) 
		:elem{new vector<T>(s)}
	{
	}

	VectorLight(const VectorLight& v)                                 // copy constructor
		:elem{new vector<T>(*v.elem)}
	{
	}

	VectorLight& operator=(const VectorLight& v)						 // copy assignment
	{
		if (this==&v) return *this;
		delete elem;
		elem = new vector<T>(*v.elem);
		return *this;
	}

	VectorLight(VectorLight&& v)                                      // move constructor
		:elem{v.elem}
	{
		v.elem = nullptr;
	}

	VectorLight& operator=(VectorLight&& v)							 // move assignment
	{
		elem = v.elem;
		v.elem = nullptr;
		return *this;
	}

	~VectorLight()
	{
		delete elem;
	}

	T& operator[](int n) { return (*elem)[n]; }					 // access: return reference
	const T& operator[](int n) const { return (*elem)[n]; }

	int size() const { return elem->size(); }                            // the current size
	int capacity() const { return elem->capacity(); }

	void resize(int newsize) { elem->resize(newsize); }
	void push_back(const T& val) { elem->push_back(val); }
	void reserve(int newalloc) { elem->reserve(newalloc) ;}
};

int main() 
{
	//VectorLight<VectorLight<VectorLight<int>>> v_empty;
	VectorLight<int> v_empty;
	cerr << "---------------------------------------------------" << endl;
	cerr << "Checking size of implementation:\n" <<
		"sizeof(int) = " << sizeof(int*)	<< '\t' <<
		"sizeof(vector<int>) = " << sizeof(v_empty) << endl;
	cerr << "---------------------------------------------------" << endl;

	VectorLight<Tracer> v (8);
	VectorLight<Tracer> v2 (8);

	for (int i = 0; i < v.size(); i++) v[i] = Tracer(i);

	for (int i = 0; i < v.size(); i++) cerr << v[i].num << '\t';
	cerr << endl;
	for (int i = 0; i < v2.size(); i++) cerr << v2[i].num << '\t';
	cerr << endl;
	v2 = v;
	v2.push_back(888);
	cerr << "---------------------------------------------------" << endl;
	for (int i = 0; i < v2.size(); i++) cerr << v2[i].num << '\t';
	cerr << endl;

	VectorLight<Tracer> v3 = v;
	v3 = move(v);
	VectorLight<Tracer> v4 = move(v);
	for (int i = 0; i < v3.size(); i++) cerr << v3[i].num << '\t';
	cerr << endl;
}
