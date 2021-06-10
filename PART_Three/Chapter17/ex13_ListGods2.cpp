#include "../std_lib_facilities.h"

/* 
*/

struct God 
{
	God (string n, string m, string v, string w) 
		:name{n}, myth{m}, vehicle{v}, weapon{w} { }

	string name;
	string myth;
	string vehicle;
	string weapon;
};

class Link {
	public:
		God god;

		Link(const God& g, Link* p = nullptr, Link* s = nullptr)
			: god{g}, prev{p}, succ{s} { }

		Link* insert(Link* n) ;                                   // insert n before this object
		Link* add(Link* n) ;                                       // insert n after this object
		Link* erase() ;                                                  // remove this object from list
		Link* find(const string& s);                          // find s in list
		const Link* find(const string& s) const;    // find s in const list (see §18.5.1)

		Link* advance(int n);                          // move n positions in list

		Link* next() const { return succ; }
		Link* previous() const { return prev; }

		// Added for the exercise
		Link* add_ordered(Link* p);
	private:
		Link* prev;
		Link* succ;
};

Link* Link::insert(Link* n)    // insert n before this object; return n
{
	if (n==nullptr) return this;
	if (this==nullptr) return n;
	n->succ = this;              // this object comes after n
	if (prev) prev->succ = n;
	n->prev = prev;            // this object’s predecessor becomes n’s predecessor
	prev = n;                        // n becomes this object’s predecessor return n;
	return n;
}

Link* Link::add( Link* n)        
{
	if (n==nullptr) return this;
	if (this==nullptr) return n;
	n->prev = this;              
	if (succ) succ->prev = n;
	n->succ = succ;            
	succ = n;                    
	return this; //returning this makes more sense, you still are on the head of the list
}

Link* Link::erase()                    // remove *p from list; return p’s successor
{
	if (this==nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
	// NO DELETE FOR ANYTHING?
}

Link* Link::find( const string& s)              // find s in list;
	// return nullptr for “not found”
{
	Link* p = this;
	while (p) {
		if (p->god.name == s) return p;
		p = p->succ;
	}
	return nullptr;
}

Link* Link::advance(int n)                        // move n positions in list
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

			  
void print_all(Link* p)
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
		if (p=p->next()) cout << '\n';
	}
	cout << '\n' << "}";
}

Link* Link::add_ordered(Link* newlink)
{
	
	Link* p {this};

	// go to the head first, maybe not the best optimization but works for this
	while (p->prev)	p = p->prev;

	cerr << p->god.name << endl;

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
	God t {"Thor", "Nordic", "Car", "Hammer"};
	God o {"Odin", "Nordic", "Truck", "Hammer"};
	God z {"Zeus", "Greek", "Moped", "Lightning"};
	God h {"Hera", "Greek", "Rollerblades", "Arrow"};
	God a {"Athena", "Greek", "Skis", "Bat"};
	God m {"Mars", "Greek", "Cart", "Chaos"};
	God z2 {"zzzzz", "Greek", "Cart", "Chaos"};

	Link* norse_gods = new Link{t};
	norse_gods = norse_gods->add_ordered(new Link{o});
	norse_gods = norse_gods->add_ordered(new Link{z});

	print_all(norse_gods);
	cout<<"\n";

	Link* greek_gods = new Link{h};
	greek_gods = greek_gods->add_ordered(new Link{a});
	greek_gods = greek_gods->add_ordered(new Link{m});
	greek_gods = greek_gods->add_ordered(new Link{z2});

	print_all(greek_gods);
	cout<<"\n";

	Link* p = greek_gods->find("Mars");

	if (p) p->god.name = "Ares";
	Link* tmp = p;
	p->erase();
	greek_gods = greek_gods->add_ordered(tmp);

	Link* p2 = norse_gods->find("Zeus");
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




