#include "../std_lib_facilities.h"

template<typename Elem>
struct Link {

	explicit Link(Elem v = Elem{}, Link* p = nullptr, Link* s = nullptr) :val{v}, prev{p}, succ{s} {  }

	Link* prev;               // previous link
	Link* succ;               // successor (next) link
	Elem val;                   // the value
};

template<typename Elem>
class List {

          Link<Elem>* first = nullptr;
          Link<Elem>* last = nullptr;    // one beyond the last link

public:
		  explicit List() = default;
		  explicit List(Elem& v) :first{new Link<Elem>{v}}, last{first} {  }

          class iterator;                 // member type: iterator

          iterator begin() { return iterator(first); }            // iterator to first element
          iterator end() { return nullptr; }	              // iterator to one beyond last element

          iterator insert(iterator p, const Elem& v);	        // insert v into List after p
          iterator erase(iterator p);                                    // remove p from the List

          void push_back(const Elem& v);                      // insert v at end
          void push_front(const Elem& v);                     // insert v at front
          void pop_front();          // remove the first element
          void pop_back();          // remove the last element

          Elem& front() { return first->val; }               // the first element
          Elem& back() { return last->val; }               // the last element
};

template<typename Elem>         // requires Element<Elem>() (§19.3.3)
class List<Elem>::iterator {
          Link<Elem>* curr;              // current link
public:
          iterator(Link<Elem>* p) :curr{p} { }

          iterator& operator++() {curr = curr->succ; return *this; }   // forward
          iterator& operator--() { curr = curr->prev; return *this; }   // backward
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

	p->succ = new Link<Elem>{v, p.self(), p->succ};		// nonsense to use p->succ->prev, maybe there is a better way, not sure in the context of the exercise.
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

	p->prev = p->succ;
	p->succ = p->prev;
	
	if (first == p.self()) first = p->succ;
	if (last == p.self()) last = p->prev;

	return p;
}

template<typename Elem>
void List<Elem>::push_back(const Elem& v) {
	if (first == nullptr) {
		first = new Link<Elem>{ v };
		last = first;
		return;
	}

	last = new Link<Elem>{ v, last, nullptr};
	last->prev->succ = last;
}

template<typename Elem>
void List<Elem>::push_front(const Elem& v) {
	if (first == nullptr) {
		first = new Link<Elem>{ v };
		last = first;
		return;
	}

	first = new Link<Elem>{ v, nullptr, first };
	first->succ->prev = first;
}

template<typename Elem>
void List<Elem>::pop_front() {
	if (first == nullptr) return;
	auto tmp = first;
	first = first->succ;
	delete tmp;
}

template<typename Elem>
void List<Elem>::pop_back() {
	if (first == nullptr) return;
	auto tmp = last;
	last = last->prev;
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



