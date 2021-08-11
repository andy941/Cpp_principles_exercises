#include "../std_lib_facilities.h"

template<typename Elem>
struct Link {

	explicit Link(Elem v = Elem{}, Link* s = nullptr) :val{v}, succ{s} {  }

	Link* succ;               // successor (next) link
	Elem val;                   // the value
};

template<typename Elem>
class List {

          Link<Elem>* first = nullptr;
          Link<Elem>* last = nullptr; // last member for fast access 

public:
		  explicit List() = default;
		  explicit List(Elem& v) :first{new Link<Elem>{v}}, last{first} {  }

          class iterator;                 // member type: iterator

          iterator begin() { return iterator(first); }            // iterator to first element
          iterator end() { return nullptr; }	              // iterator to one beyond last element

          iterator insert(iterator p, const Elem& v);	        // insert v into List after p
          iterator erase(iterator p);                           // remove p from the List

          void push_back(const Elem& v);                      // insert v at end
          void push_front(const Elem& v);                     // insert v at front
          void pop_front();          // remove the first element
          // not possible --> void pop_back();          // remove the last element

          Elem& front() { return first->val; }               // the first element
          Elem& back() { return last->val; }               // the last element
};

template<typename Elem>         // requires Element<Elem>() (§19.3.3)
class List<Elem>::iterator {
          Link<Elem>* curr;              // current link
public:
          iterator(Link<Elem>* p) :curr{p} { }

          iterator& operator++() {curr = curr->succ; return *this; }   // forward
          // impossible --> iterator& operator--() { curr = curr->prev; return *this; }   // backward
          Elem& operator*() { return curr->val; }   // get value (dereference)	// CHANGED: get underlying Link dereferenced
		  Link<Elem>* operator->() { return curr; }
		  Link<Elem>* self() { return curr; }

          bool operator==(const iterator& b) const { return curr==b.curr; }
          bool operator!= (const iterator& b) const { return curr!=b.curr; }
};

template<typename Elem>
typename List<Elem>::iterator List<Elem>::insert(List<Elem>::iterator p, const Elem& v)
{
	// Check if empty
	if (first == nullptr) {
		first = new Link<Elem>{v}; 
		last = first;
		return first;
	}

	p->succ = new Link<Elem>{v, p->succ};		
	if (p->succ->succ == nullptr) last = p->succ;

	return p->succ;
}

template<typename Elem>
typename List<Elem>::iterator List<Elem>::erase(List<Elem>::iterator p)
{
	// Check if empty
	if (first == nullptr) {
		return nullptr;
	}

	if (first == p.self()) {
		pop_front();
		return first;
	}

	Link<Elem>* tmp = nullptr;

	for (auto it = first; first != nullptr; ++it) {
		if (it->succ == p.self()) {
			tmp = it;
			break;
		}
	}

	if (!tmp) return nullptr;		// not found

	tmp->succ = p->succ;
	cerr << "REACH 1" << endl;

	return p;
}

template<typename Elem>
void List<Elem>::push_back(const Elem& v) {
	if (first == nullptr) {
		first = new Link<Elem>{ v };
		last = first;
		return;
	}

	last->succ = new Link<Elem>{ v, nullptr};
	last = last->succ;
}

template<typename Elem>
void List<Elem>::push_front(const Elem& v) {
	if (first == nullptr) {
		first = new Link<Elem>{ v };
		last = first;
		return;
	}

	first = new Link<Elem>{ v, first };
}

template<typename Elem>
void List<Elem>::pop_front() {
	if (first == nullptr) return;
	auto tmp = first;
	first = first->succ;
	delete tmp;
}

template<typename Iter>
//typename List<Elem>::iterator List<Elem>::erase(List<Elem>::iterator p)
Iter High(Iter first, Iter last)
{
	if (first == nullptr) return last;

	Iter h = first;
	for (auto& it = first; first != last; ++it) {
		cerr << "# " << *h << '\t' << *it << endl;
		if (*it > *h) h = it;
	}
	return h;
}


int main() 
{
	List<int> lst;
	lst.insert(lst.begin(), 3);
	lst.insert(lst.begin(), 4);
	lst.insert(lst.begin(), 5);
	lst.insert(lst.begin(), 6);
	lst.insert(lst.begin(), 7);
	cerr << lst.front() << " # " << lst.back() << endl;
	for (auto x : lst) cout << x << '\t';
	cout << endl;
	lst.erase(++lst.begin());
	lst.erase(lst.begin());
	cerr << lst.front() << " # " << lst.back() << endl;
	for (auto x : lst) cout << x << '\t';
	cout << endl;
	lst.push_back(18);
	lst.push_front(18);
	cerr << lst.front() << " # " << lst.back() << endl;
	for (auto x : lst) cout << x << '\t';
	cout << endl;
	auto e = lst.erase(lst.begin());
	cerr << lst.front() << " # " << lst.back() << endl;
	for (auto x : lst) cout << x << '\t';
	cout << endl;

	auto h = High(lst.begin(), lst.end());
	cout << "The highest number is: " << *h << endl;
}



