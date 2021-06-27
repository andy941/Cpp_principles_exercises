
#include "../std_lib_facilities.h"
#include "chrono"

/*
 * Useful informations --> https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/skiplists.pdf 
 * This code implements a basic sorted skip list, without random access (maybe that is a future development).
*/

class Link {
	public:
		int value;

		Link(const int& v, Link* b = nullptr, Link* s = nullptr)
			: value{v}, under{b}, succ{s} { }

		Link* below() const { return under; }
		Link* next() const { return succ; }
		void set_below(Link* l) { under = l; }
        void set_next(Link* l) { succ = l; }
		void add(Link*l);		// Insert after this link
		Link* find(int v);	// Find the Link: Link < val < Link.succ
		void erase();	// erase the Link after this one: Link < toerase < Link.succ
		void print_all();

	private:
		Link* under;
		Link* succ;
};

class SkipList
{
	public:
		explicit SkipList(int M_L = 8, double P = 0.5) 
			: MAX_LEVEL{M_L}, PROB{P} { };

		void insert(int val);     
		void erase(int val);      
		Link* find(int val); 
		void print_all();

		~SkipList() {
			Link* p { nullptr };
			for (Link* x : HEAD) {
				while (x) {
					p = x;
					delete[] p;
					x = x->next();
				}
			}
			cerr << "Destructor Called...." << endl;
		}

	private:
		int MAX_LEVEL;
		double PROB;
		vector<Link*> HEAD {};					// hold Pointers to first elements of each level (strictly < MAX_LEVEL)
};

// ________________________________________________________________________________

void Link::add(Link* l)
{
	l->set_next(succ);
	succ = l;
}

Link* Link::find(int v)
{
	if (value >= v) return nullptr;		// Should go before the HEAD

	Link* p = this;

	while (p->next()) {
		if (p->next()->value >= v) return p;
		p = p->next();
	}
	return p;
}

void Link::erase()
{
	Link* tmp { succ };
	succ = succ->next();
	delete tmp;		// Free the memory from the deleted link
}

void Link::print_all() 
{
	Link* p = this;
	while(p) {
		cout << p->value << '\t';
		p = p->next();
	}
	cout << '\n';
}

void SkipList::insert(int val)  
{
	// If it's the first element of the list just add it
	if (HEAD.empty()) {
		HEAD.push_back(new Link{ val, nullptr, nullptr });
		return;
	}

	// while traversing the list top down save the Links that will have to be changed to accomodate the
	// new link. Not all of them will have to be used.
	vector<Link*> prevs;
	Link* p = HEAD[HEAD.size()-1];		// Start from the top
	int lv = HEAD.size()-1;

	// First "find" where to put the Link
	while (lv >= 0) {	

		p = p->find(val);
		prevs.push_back(p);

		if (!p && lv > 0) p = HEAD[lv-1]; 
		else if (lv > 0) p = p->below();

		--lv;
	}

	// Find out in how many levels the Link will be inserted (from the bottom up), by flipping a coin (default probability)
	double coin; 

	Link* bottom {nullptr};

	for (int i = 0; i < MAX_LEVEL; i++) {

		coin = rand()%100/100.0;
		if (coin < PROB && i != 0) break;			// If outside the PROBability of jumping one level stop the loop.

		if (i < prevs.size()) {

			if (!prevs[prevs.size()-1-i]) {
				HEAD[i] = new Link { val, bottom, HEAD[i] }; 
				bottom = HEAD[i];
			} else {
				prevs[prevs.size()-1-i]->add(new Link{ val, bottom, nullptr });
				bottom = prevs[prevs.size()-1-i]->next();
			}

		} else {

			HEAD.push_back(new Link{ val, bottom, nullptr });
			bottom = HEAD[HEAD.size() -1];
		}
	}
}

void SkipList::erase(int val)
{
	vector<Link*> prevs;
	Link* p = HEAD[HEAD.size()-1];		// Start from the top
	int lv = HEAD.size()-1;

	// First "find" where to put the Link
	while (lv >= 0) {	

		p = p->find(val);

		if (!p) {

			if (HEAD[lv]->value == val) {
				Link* tmp {HEAD[lv]};
				HEAD[lv] = HEAD[lv]->next(); 
				delete tmp;		// Free memory for link erased
			}

			if (lv > 0) p = HEAD[lv-1];

		} else if (!p->next()) {

			p = p->below();

		} else if (p->next()->value == val) {

			p->erase();
			p = p->below();
		}

		--lv;
	}


	for (int i = 0; i < HEAD.size(); i++) {
		if (!HEAD[i]) {
			HEAD = {HEAD.begin(), HEAD.begin() + i};
			break;
		}
	}
}

Link* SkipList::find( int val)  
	// return nullptr for “not found”
{
	vector<Link*> prevs;
	Link* p = HEAD[HEAD.size()-1];		// Start from the top
	int lv = HEAD.size()-1;

	while (lv >= 0) {	

		p = p->find(val);

		if (!p) {

			if (HEAD[lv]->value == val) return HEAD[lv];
			if (lv > 0) p = HEAD[lv-1];

		} else if (!p->next()) {

			p = p->below();

		} else if (p->next()->value == val) {

			return p->next();

		}

		--lv;
	}

	return nullptr;
}

void SkipList::print_all()
{
	cout << "Levels: " << HEAD.size() << '\n';
	for (int i = 0; i < HEAD.size(); i++) {
			cout << HEAD.size() - i << ":\t";
			HEAD[HEAD.size()-1-i]->print_all();
	}
}

int main() 
{
	constexpr int SIZE	{10000000};
	constexpr int F		{5000000};

	SkipList sk;
	Link* li = new Link {0, nullptr, nullptr};

	for (int i = 0; i < SIZE; i++) {
		sk.insert(SIZE-i);
		li->add(new Link{SIZE-i, nullptr, nullptr});
	}

	//sk.print_all();
	//li->print_all();

	cout << "Starting search with skip list" << endl;

    auto begin = std::chrono::high_resolution_clock::now();
    
	Link* tmp = sk.find(F);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
	if (tmp) cout << "FOUND " <<  tmp->value << endl;
    
    printf("Time measured: %.10f seconds.\n", elapsed.count() * 1e-9);
	cout << "Starting search with regular ordered list" << endl;

    begin = std::chrono::high_resolution_clock::now();
    
	tmp = li->find(F);
    
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
	if (tmp) cout << "FOUND " <<  tmp->value+1 << endl;
    
    printf("Time measured: %.10f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}




