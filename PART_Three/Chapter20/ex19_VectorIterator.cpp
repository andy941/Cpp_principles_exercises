#include <cstring>		//for memcpy
#include "../Chapter19/ex13_Tracer.cpp"
#include "../std_lib_facilities.h"

template<typename T> 
class Allocator 
{
	public:
		T* allocate(int n);                  // allocate space for n objects of type T
		void deallocate(T* p);        // deallocate n objects of type T starting at p
		void construct(T* p, const T& v);    // construct a T with the value v in p
		void destroy(T* p);                  // destroy the T in p

};

template<typename T> 
T* Allocator<T>::allocate(int n)
{
	return static_cast<T*>((T*) malloc(n*sizeof(T)));
}

template<typename T> 
void Allocator<T>::deallocate(T* p) // (T* p, int n) why  specify the n? can't deallocate the "middle" of a vector I think...
{
	free(p);			// Shouldn't this deallocate all the memory allocated with malloc after the pointer given? that's the only thing that make sense.
}

template<typename T> 
void Allocator<T>::construct(T* p, const T& v)
{
	//new (p) T{v};		// this constructs one object that is immediately destroyed (unnecessary), not sure how to fix it yet?
	memcpy(p,&v,sizeof(T));		// Maybe this is more efficient, it seem more efficient at least. After construction the class is just copied, not constructed again.
}

template<typename T> 
void Allocator<T>::destroy(T* p)
{
	p->~T();			// explicit destructor needed in this case, there is no "placement delete" after the placement new.
}

template<typename T, typename A = Allocator<T>>
class MyVector {                // read “for all types T” (just like in math)

	A alloc;
	int sz;                                                                 
	T* elem;                                                               
	int space;                                                            

public:

	class iterator;

	iterator begin() { return iterator(elem, elem, sz); }
	iterator end() { return iterator(elem+sz, elem, sz); }

	MyVector() : sz{0}, elem{nullptr}, space{0} { }
	explicit MyVector(int s) 
		:sz{s}, elem{alloc.allocate(s)}, space{s}
	{
		for (int i=0; i<sz; ++i) alloc.construct(&elem[i], T());              // elements are initialized
	}

	MyVector(const MyVector&);                                 // copy constructor
	MyVector& operator=(const MyVector&);						 // copy assignment

	MyVector(MyVector&&);                                      // move constructor
	MyVector& operator=(MyVector&&);							 // move assignment

	~MyVector();

	T& operator[](int n) { return elem[n]; }					 // access: return reference
	const T& operator[](int n) const { return elem[n]; }

	int size() const { return sz; }                            // the current size
	int capacity() const { return space; }

	void resize(int newsize, T val);                                  // growth
	void push_back(const T& val);
	void reserve(int newalloc);
};

template<typename T, typename A>
MyVector<T,A>::~MyVector()
{ 
		for (int i=0; i<sz; ++i)  alloc.destroy(&elem[i]);
		alloc.deallocate(elem);
}

template<typename T, typename A>
MyVector<T,A>::MyVector(const MyVector& arg)
	:sz{arg.sz}, elem{alloc.allocate(arg.sz)}, space{arg.sz}
{
		for (int i=0; i<sz; ++i) alloc.construct(&elem[i], arg[i]);              // elements are initialized
}

template<typename T, typename A>
MyVector<T,A>& MyVector<T,A>::operator=(const MyVector& a)
{
          if (this==&a) return *this;      // self-assignment, no work needed

          if (a.sz<=space) {                     // enough space, no need for new allocation
                    for (int i = 0; i<a.sz; ++i) alloc.construct(&elem[i], a.elem[i]);        // copy elements
                    sz = a.sz;
                    return *this;
          }

          T* p = alloc.allocate(a.sz);                         // allocate new space
          for (int i = 0; i<a.sz; ++i) alloc.construct(&elem[i], a.elem[i]);        // copy elements
          for (int i = 0; i<a.sz; ++i) alloc.destroy(&a.elem[i]);                                    // deallocate old space
		  alloc.deallocate(elem);
          space = sz = a.sz;                             // set new size
          elem = p;                                           // set new elements
          return *this;                                      // return a self-reference
}

template<typename T, typename A>
MyVector<T,A>::MyVector(MyVector&& a)
	:sz{a.sz}, elem{a.elem}, space{a.space}
{
	a.sz = 0;
	a.elem = nullptr;
	a.space = 0;
}

template<typename T, typename A>
MyVector<T,A>& MyVector<T,A>::operator=(MyVector<T,A>&& a)
{
	for (int i = 0; i < sz; i++) alloc.destroy(&elem[i]);
	alloc.deallocate(elem);
	elem = a.elem;
	sz = a.sz;
	space = a.space;
	a.sz = 0;
	a.elem = nullptr;
	a.space = 0;
	return *this;
}

template<typename T, typename A>
void MyVector<T,A>::reserve(int newalloc)
{
	if (newalloc<=space) return;               // never decrease allocation
	T* p = alloc.allocate(newalloc);          // allocate new space
	for (int i=0; i<sz; ++i) alloc.construct(&p[i],elem[i]);       // copy
	for (int i=0; i<sz; ++i) alloc.destroy(&elem[i]);                 // destroy
	alloc.deallocate(elem,space);             // deallocate old space
	elem = p;
	space = newalloc;
}

template<typename T, typename A>
void MyVector<T,A>::resize(int newsize, T val)
          // make the vector have newsize elements
          // initialize each new element with the default value 0.0
{
	reserve(newsize);
	for (int i=sz; i<newsize; ++i) alloc.construct(&elem[i],val);   // construct
	for (int i = newsize; i<sz; ++i) alloc.destroy(&elem[i]);            // destroy
	sz = newsize;
}

template<typename T, typename A>
void MyVector<T,A>::push_back(const T& val)
          // increase vector size by one; initialize the new element with d
{
	if (space==0) reserve(8);                            // start with space for 8 elements
	else if (sz==space) reserve(2*space);      // get more space
	alloc.construct(&elem[sz],val);                 // add val at end
	++sz;                                                              // increase the size
}

// ITERATOR implementation *********************************************************************************
template<typename T, typename A>
class MyVector<T,A>::iterator
{
	T* curr;
	T* first;
	T* last;

	public:
	iterator(T* p, T* elem, int size) :curr{p}, first{elem}, last{elem + size} {  };

	iterator& operator++() { 
		if (curr == last) throw(std::out_of_range("already on end()"));
		T* tmp = curr-1;
		++curr;
		return *this; }   // forward
	iterator& operator--() { 
		if (curr == first) throw(std::out_of_range("already on begin()"));
		--curr;
		return *this; }   // backward

	T& operator*() { return *curr; }
	T* operator->() { return curr; }

	bool operator==(const iterator& b) const { return curr==b.curr; }
	bool operator!= (const iterator& b) const { return curr!=b.curr; }


};


int main() 
{
	MyVector<Tracer> v (8);
	MyVector<Tracer> v2 (8);

	for (int i = 0; i < v.size(); i++) v[i] = Tracer(i);

	for (int i = 0; i < v.size(); i++) cerr << v[i].num << '\t';
	cerr << endl;

	for (int i = 0; i < v.size(); i++) cerr << v2[i].num << '\t';
	cerr << endl;

	v2 = v;
	for (int i = 0; i < v.size(); i++) cerr << v2[i].num << '\t';
	cerr << endl;

	MyVector<Tracer> v3 = v;
	for (int i = 0; i < v.size(); i++) cerr << v2[i].num << '\t';
	cerr << endl;

	cout << "Try range check ------------------------------------" << endl;
	auto it = v.begin();
	try { --it; }
	catch ( exception& e ) { cerr << e.what() << endl; }
	it = v.end();
	try { ++it; }
	catch ( exception& e ) { cerr << e.what() << endl; }
	cerr << "END" << endl;
}
