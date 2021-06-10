#include "../std_lib_facilities.h"

/* 
 * Singly linked lists should be faster and occupy less memory.
 * You have however to always have a pointer for the head of the list to do any meaningful operation.
 * if operations involve moving in both directions of the list frequently they could be a bad choice.
 * If the opreations you are doing are just scanning the whole list all the time (i.e. find() or adding an 
 * element in a specific spot along the list) they are a viable option (my intuition).
*/

class Link {
	public:
		string value;


		Link(const string& v, Link* s = nullptr)
			: value{v} { }


		Link* advance(int n);                          // move n positions in list
		Link* next() const { return succ; }
		void point_to(Link* ss) { succ = ss; }

	private:
		Link* succ;
};

class List {

		Link* head {nullptr};
		Link* tail {nullptr};

	public:
		List() {};
		List(Link* l) :head{l}, tail{l} { };

		Link* find(const string& s);						// find link called s
		Link* get_head() const {return head;}
		void push_back(Link* n);
		void insert(const string& s , Link* n) ;				// Add after link called s
		void erase(const string& s) ;						// erase link called s

};

Link* List::find(const string& s)
{
	Link* p = head;
	while (p) {
		if (p->value == s) return p;
		p = p->next();
	}

	return nullptr;
}

void List::erase(const string& s)
{
	if (head->value == s) {
		head = head->next();
		return;
	}

	Link* p = head;

	while (p->next()) {
		if (p->next()->value == s) {
			p->point_to(p->next()->next());
			if (!p->next()) tail=p;
			return;
		}
		p = p->next();
	}

	cerr << "Warning: Trying to erase non-existing link.\n";
}
			  
void List::insert(const string& s, Link* n)
{
	if (head->value == s) {
		n->point_to(head);
		head = n;
		return;
	}

	Link* p = head;

	while (p->next()) {
		if (p->next()->value == s) {
			n->point_to(p->next()->next());
			p->point_to(n);
			return;
		}
		p = p->next();
	}

	cerr << "Warning: Trying to insert non-existing link.\n";
}

void List::push_back(Link* n) 
{
	if (!head) {
		head = n;
		tail = n;
		return;
	}

	tail->point_to(n);
	tail = n;
	n->point_to(nullptr);
}

void print_all(Link* p)
{
	
	cout << "{ ";
	while (p) {
		cout << p->value;
		if (p=p->next()) cout << ", ";
	}
	cout << " }";
}

int main() 
{
	List norse_gods;
	norse_gods.push_back(new Link{"Thor"});
	norse_gods.push_back(new Link{"Odin"});
	norse_gods.push_back(new Link{"Zeus"});
	norse_gods.push_back(new Link{"Freia"});

	List greek_gods;
	greek_gods.push_back(new Link{"Hera"});
	greek_gods.push_back(new Link{"Athena"});
	greek_gods.push_back(new Link{"Mars"});
	greek_gods.push_back(new Link{"Poseidon"});

	print_all(norse_gods.get_head());
	cout<<"\n";
	print_all(greek_gods.get_head());
	cout<<"\n";

	Link* p = greek_gods.find("Mars");
	if(p) p->value = "Ares";

	cout<<"\n";
	print_all(norse_gods.get_head());
	cout<<"\n";
	print_all(greek_gods.get_head());
	cout<<"\n";

	Link* p2 = norse_gods.find("Zeus");
	norse_gods.erase("Zeus");
	greek_gods.insert("Hera", p2);

	cout<<"\n";
	print_all(norse_gods.get_head());
	cout<<"\n";
	print_all(greek_gods.get_head());
	cout<<"\n";
}





