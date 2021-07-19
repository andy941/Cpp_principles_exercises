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
	new (p) T{v};
}

template<typename T> 
void Allocator<T>::destroy(T* p)
{
	p->~T();			// explicit destructor needed in this case, there is no "placement delete" after the placement new.
}

//int main() 
//{
//	vector<Tracer> trace(4);
//	for (int i = 0; i < 4; i++) trace[i].num = i;
//
//	Allocator<Tracer> alloc;
//	Tracer* p = alloc.allocate(4);
//
//	for (int i = 0; i < 4; i++) alloc.construct(&p[i], trace[i]);
//	for (int i = 0; i < 4; i++) cerr << p[i].num << endl;
//	for (int i = 0; i < 4; i++) alloc.destroy(&p[i]);
//	alloc.deallocate(p);
//}

