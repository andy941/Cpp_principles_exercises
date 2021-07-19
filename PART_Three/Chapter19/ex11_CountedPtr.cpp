#include"ex13_Tracer.cpp"

/*
 * I am doing an implementation more similar to the shared_ptr fro the standard. 
 * The count is not passed but managed through the copy constructors and assingments.
 */

template<typename T>
class CountedPtr
{
	T* p = nullptr;
	int* count = nullptr;

	public:
	CountedPtr() 
	{ 
		count = new int{0}; 
		cerr << "Constructed CountedPtr with count" << *count << endl;
	}

	CountedPtr(T* t)
		:p{t}
	{
		count = new int{1};
		cerr << "Constructed CountedPtr with count" << *count << endl;
	}

	CountedPtr(const CountedPtr& c) 
	{
		p = c.p;
		*c.count += 1;
		count = c.count;
		cerr << "Copy Constructed CountedPtr with count" << *count << endl;
	}

	CountedPtr& operator=(const CountedPtr& c)
	{
		if (this==&c)	return *this;			// Self assingment

		p = c.p;
		*c.count += 1;
		count = c.count;
		cerr << "Copy Assignment for CountedPtr with count" << *count << endl;
		return *this;
	}

	// No moving around, only copy
	CountedPtr(CountedPtr&&) = delete;
	CountedPtr& operator=(CountedPtr&&) = delete;

	~CountedPtr()
	{
		if (!count && !p) return;
		if (!count) return;

		if (*count > 0) {
			*count -= 1;
			cerr << "Destructor not called on object yet , count is now " << *count << endl;
			return;
		}

		if (p) {
			if (p) {
				delete p;
				p = nullptr;
			}
			if (count) {
				delete count;
				count = nullptr;
			}
			cerr << "Destroyed CountedPtr and object" << endl;
			return;
		}

		cerr << "Destroyed empty CountedPtr with count " << *count << endl;
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
		if (count) delete count;
		count = nullptr;
		return t;
	}
};


int main()
{
	CountedPtr<Tracer> p_init {new Tracer{1}};

	cerr << "# Release tracer 1 and assign to a regular ptr" << endl;
	Tracer* p2 {p_init.release()};
	cerr << "# tracer 1 becomes 2" << endl;
	p2->num = 2;
	cerr << "New Value = " << p2->num << endl;
	cerr << "# Manually destroy ptr 2 and tracer 2" << endl;
	delete p2;

	cerr << "# Construct 2 more counted pointers sharing p1" << endl;
	CountedPtr<Tracer> p1 {new Tracer{999}};
	CountedPtr<Tracer> p1_share = p1;
	CountedPtr<Tracer> p2_share = p1;

	cerr << "# Manually call destructor" << endl;
	p1_share.~CountedPtr();

	cerr << "# Construct Empty counted pointer" << endl;
	CountedPtr<Tracer> p_empty;

	cerr << "# Construct counted pointer and tracer 300" << endl;
	CountedPtr<Tracer> p3 {new Tracer{300}};
	cerr << "# END------------------------" << endl;
}

