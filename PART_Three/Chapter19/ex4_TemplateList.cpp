
#include "../std_lib_facilities.h"

/* 
*/


template <typename T, typename U, typename V, typename Z>
struct God 
{
	God (T n, U m, V v, Z w) 
		:name{n}, myth{m}, vehicle{v}, weapon{w} { }

	T name;
	U myth;
	V vehicle;
	Z weapon;
};

template <typename T, typename U, typename V, typename Z>
class Link {
	public:
		God<T,U,V,Z> god;

		Link(const God<T,U,V,Z>& g, Link* p = nullptr, Link* s = nullptr)
			: god{g}, prev{p}, succ{s} { }

		Link* insert(Link* n) ;                                   // insert n before this object
		Link* add(Link* n) ;                                       // insert n after this object
		Link* erase() ;                                                  // remove this object from list
		Link* find(const T& s);                          // find s in list
		const Link* find(const T& s) const;    // find s in const list (see §18.5.1)

		Link* advance(int n);                          // move n positions in list

		Link* next() const { return succ; }
		Link* previous() const { return prev; }

		// Added for the exercise
		Link* add_ordered(Link* p);
	private:
		Link* prev;
		Link* succ;
};

template <typename T, typename U, typename V, typename Z>
Link<T,U,V,Z>* Link<T,U,V,Z>::insert(Link* n)    // insert n before this object; return n
{
	if (n==nullptr) return this;
	if (this==nullptr) return n;
	n->succ = this;              // this object comes after n
	if (prev) prev->succ = n;
	n->prev = prev;            // this object’s predecessor becomes n’s predecessor
	prev = n;                        // n becomes this object’s predecessor return n;
	return n;
}

template <typename T, typename U, typename V, typename Z>
Link<T,U,V,Z>* Link<T,U,V,Z>::add( Link* n)        
{
	if (n==nullptr) return this;
	if (this==nullptr) return n;
	n->prev = this;              
	if (succ) succ->prev = n;
	n->succ = succ;            
	succ = n;                    
	return this; //returning this makes more sense, you still are on the head of the list
}

template <typename T, typename U, typename V, typename Z>
Link<T,U,V,Z>* Link<T,U,V,Z>::erase()                    // remove *p from list; return p’s successor
{
	if (this==nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
	// NO DELETE FOR ANYTHING?
}

template <typename T, typename U, typename V, typename Z>
Link<T,U,V,Z>* Link<T,U,V,Z>::find( const T& s)              // find s in list;
	// return nullptr for “not found”
{
	Link* p = this;
	while (p) {
		if (p->god.name == s) return p;
		p = p->succ;
	}
	return nullptr;
}

template <typename T, typename U, typename V, typename Z>
Link<T,U,V,Z>* Link<T,U,V,Z>::advance(int n)                        // move n positions in list
	// return nullptr for “not found”
	// positive n moves forward, negative backward
{
	Link* p = this;

	if (p==nullptr) return nullptr;
	if (0<n) {
		while (n--) {
			if (p->succ == nullptr) return nullptr;
			p = p->succ;
		}
	}
	else if (n<0) {
		while (n++) {
			if (p->prev == nullptr) return nullptr;
			p = p->prev;
		}
	}
	return p;
}

			  
template <typename T, typename U, typename V, typename Z>
void print_all(Link<T,U,V,Z>* p)
{
	// go to the head first
	while (p->previous()) {
		p = p->previous();
	}

	cout << "{" << '\n';
	while (p) {
		cout  << "{ " <<
			p->god.name << '\t' <<
			p->god.myth << '\t' <<
			p->god.vehicle << '\t' <<
			p->god.weapon << " }";
		if (p->next()) cout << '\n';
		p=p->next();
	}
	cout << '\n' << "}";
}

template <typename T, typename U, typename V, typename Z>
Link<T,U,V,Z>* Link<T,U,V,Z>::add_ordered(Link* newlink)
{
	Link* p {this};

	// go to the head first, maybe not the best optimization but works for this
	while (p->prev)	p = p->prev;

	// should it be before the head?
	if (p->god.name > newlink->god.name) {
		return p->insert(newlink);
	}

	while (p) {
		if (p->god.name > newlink->god.name) return p->insert(newlink);
		if (!p->succ) return p->add(newlink); // are we at the end? -> add as last
		p = p->succ;
	}

	return nullptr;
}

int main() 
{
	God<string,string,string,string> t {"Thor", "Nordic", "Car", "Hammer"};
	God<string,string,string,string> o {"Odin", "Nordic", "Truck", "Hammer"};
	God<string,string,string,string> z {"Zeus", "Greek", "Moped", "Lightning"};
	God<string,string,string,string> h {"Hera", "Greek", "Rollerblades", "Arrow"};
	God<string,string,string,string> a {"Athena", "Greek", "Skis", "Bat"};
	God<string,string,string,string> m {"Mars", "Greek", "Cart", "Chaos"};
	God<string,string,string,string> z2 {"zzzzz", "Greek", "Cart", "Chaos"};

	Link<string,string,string,string>* norse_gods = new Link<string,string,string,string>{t};
	norse_gods = norse_gods->add_ordered(new Link<string,string,string,string>{o});
	norse_gods = norse_gods->add_ordered(new Link<string,string,string,string>{z});

	print_all(norse_gods);
	cout<<"\n";


	Link<string,string,string,string>* greek_gods = new Link<string,string,string,string>{h};
	greek_gods = greek_gods->add_ordered(new Link<string,string,string,string>{a});
	greek_gods = greek_gods->add_ordered(new Link<string,string,string,string>{m});
	greek_gods = greek_gods->add_ordered(new Link<string,string,string,string>{z2});

	print_all(greek_gods);
	cout<<"\n";

	Link<string,string,string,string>* p = greek_gods->find("Mars");

	if (p) p->god.name = "Ares";
	Link<string,string,string,string>* tmp = p;
	p->erase();
	greek_gods = greek_gods->add_ordered(tmp);

	Link<string,string,string,string>* p2 = norse_gods->find("Zeus");
	if (p2) {
		if (p2==norse_gods) norse_gods = p2->next();
		p2->erase();
		greek_gods = greek_gods->add_ordered(p2);
	}

	print_all(norse_gods);
	cout<<"\n";

	print_all(greek_gods);
	cout<<"\n";
}




