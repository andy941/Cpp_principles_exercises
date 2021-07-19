#include"ex13_Tracer.cpp"

template<typename T>
class UniquePtr
{
	T* p = nullptr;

	public:
	UniquePtr() = default;
	UniquePtr(T* t)
		:p{t}
	{
		cerr << "Constructed UniquePtr" << endl;
	}

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	~UniquePtr()
	{
		if (p) {
			cerr << "Destroyed UniquePtr and object" << endl;
			delete p;
			return;
		}
		cerr << "Destroyed UniquePtr" << endl;
	}

	T* operator->()
	{
		return p;
	}

	T operator*()
	{
		return *p;
	}

	T* release()
	{
		T* t = p;
		p = nullptr;
		return t;
	}
};


int main()
{
	cerr << "# Construct unique pointer and tracer 1" << endl;
	UniquePtr<Tracer> p1 {new Tracer{1}};

	cerr << "# Release tracer 1 and assign to a regular ptr" << endl;
	Tracer* p2 {p1.release()};
	cerr << "# tracer 1 becomes 2" << endl;
	p2->num = 2;
	cerr << "# Manually destroy ptr 2 and tracer 2" << endl;
	delete p2;

	cerr << "# Construct unique pointer and tracer 3" << endl;
	UniquePtr<Tracer> p3 {new Tracer{3}};
	cerr << "# Destroyed ptr 3 and tracer 3, ptr1" << endl;
}
