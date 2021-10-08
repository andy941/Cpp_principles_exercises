#include "../std_lib_facilities.h"
#include "../Chapter19/ex13_Tracer.cpp"
using namespace std;

/* 
 * This is still not optimal, I wonder if there is a better way.
 * Avoiding th new operator would be good, I don't know how one can have
 * a vector class that is not dynamic. Tha would be more like an array.
 * Destructors and constructors are called a bit too many times, I don't 
 * fully understand why.
 */

template<typename T, int N>
class Pool {                               // Pool of N objects of type T
	public:
		explicit Pool();                            // make pool of N Ts
		~Pool();
		T* get();                         // get a T from the pool; return 0 if no free Ts
		void free(T*);               // return a T given out by get() to the pool
		int available() const { return avail.count(0); };
	private:
		T* elem;
		bitset<N> avail;
		unsigned int sz { N };
};

template<typename T, int N>
Pool<T,N>::Pool():
	elem	{ static_cast<T*>(malloc(sizeof(T)*N)) },
	sz		{ N }
{  }
template<typename T, int N>
Pool<T,N>::~Pool()
{
	for (unsigned int i = 0; i < sz; i++) {
		if (avail[i]) (elem + sizeof(T)*i) -> ~T();
	}
	free(elem);
}

template<typename T, int N>
T* Pool<T,N>::get()
{
	for (unsigned int i = 0; i < sz; i++) {
		if (!avail[i]) {
			avail[i] = 1;
			return elem + sizeof(T);
		}
	}
	return nullptr;
}

template<typename T, int N>
void Pool<T,N>::free(T* t)
{
	t->~T();
	//cerr << *t << " " << t-elem << " break" << endl;
	avail[t-elem] = 0;
}


// Vector implementation ---------------------------------------------------------
// You have to go with a static vector, dynamic allocation is not allowed, Pool is
// going to manage the resource for you (i.e. limited number of connections). the user can
// create as many small vectors (really arrays) are needed until the Pool is exhausted.
template<class T, int N>
class PoolVector
{	// This is a very stripped down implementation 
	// (missing constructors and full suite of facilities).
	Pool<T,N>& pool;
	T** p;
	int sz;
	int sp;
	
	public:
	PoolVector(Pool<T,N>& pp, int n): 
		pool	{ pp },
		p		{ new T* [n] },			// I know new is not great, ideally though the pool is what is managing the critical resources.
		sz		{ 0 },
		sp		{ n }
	{  };

	~PoolVector()
	{
		for (int i = 0; i < sz; i++) pool.free(p[i]);
		//cerr << "break" << endl;
		delete[] p;
	}

	void push_back(T t) { 
		T* tmp = pool.get();
		if (!tmp) error("pool memory exhausted");
		tmp = new (tmp) T(t);
		if (sz < sp) p[sz++] = tmp;
		else error("no more space in vector");
	};

	int size() { return sz; };
	int space() { return sp; };
	T& operator[](int n) { return *p[n]; };
};

// -------------------------------------------------------------------------------
int main () 
{
	// cout << "size = " << sizeof(long int) << endl;
	Pool<Tracer,300> p;
	// long int* n = p.get();
	// *n = 1;
	// long int* n2 = p.get();
	// *n2 = 2;
	// p.free(n);
	// p.free(n2);
	// long int* n3 = p.get();
	// *n3 = 3;

	// cout << *n << '\t' << *n2 << '\t' << *n3 <<  endl;
	// cout << n << '\n' << n2 << '\n' << n3 << endl;
	PoolVector v { p, 8 };
	v.push_back(Tracer{1});
	//v.push_back(Tracer{2});
	cout << v[0].num << endl;
	//cout << v[1].num << endl;
	//v.push_back(999);
	//v.push_back(9);
	//for(int i = 0; i < v.size(); i++) {
	//	cout << v[i] << '\t';
	//}
	//cout  << endl;
}
