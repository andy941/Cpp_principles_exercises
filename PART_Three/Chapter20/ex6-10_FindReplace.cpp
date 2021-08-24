#include "../std_lib_facilities.h"
#include <iterator>
//#include "../Chapter19/ex9_VectorMain.cpp"

using Line = vector<char>;             // a line is a vector of characters

class Text_iterator 
{      // keep track of line and character position within a line
	list<Line>::iterator ln;
	Line::iterator pos;

	public:
	// https://stackoverflow.com/questions/41044165/the-c-stl-function-find-doesnt-accept-the-iterator-arguments-of-a-user-defi?rq=1
    typedef ptrdiff_t          difference_type;
    typedef char               value_type;
    typedef char*              pointer;
    typedef char&              reference;
    typedef input_iterator_tag iterator_category;

	// start the iterator at line ll’s character position pp:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		:ln{ll}, pos{pp} { }

	char& operator*() { return *pos; }
	Text_iterator& operator++();
	Text_iterator& operator--();

	bool operator==(const Text_iterator& other) const
	{ return ln==other.ln && pos==other.pos; }
	bool operator!=(const Text_iterator& other) const
	{ return !(*this==other); }

	void erase() { ln->erase(pos); }
	void insert(const string& s) { (*ln).insert(pos, s.begin(), s.end()); }
};

Text_iterator& Text_iterator::operator++()
{
	++pos;                                       // proceed to next character
	if (pos==(*ln).end()) {
		++ln;                                // proceed to next line
		pos = (*ln).begin();       // bad if ln==line.end(); so make sure it isn’t
	}
	return *this;
}

Text_iterator& Text_iterator::operator--()
{
	if (pos==(*ln).begin()) {
		--ln;                                // proceed to prev line
		pos = (*ln).end(); 
	}
	--pos;                                       // proceed to prev character
	return *this;
}

struct Document {
	list<Line> line;                        // a document is a list of lines
	Document() { line.push_back(Line{}); }

	Text_iterator begin()               // first character of first line
	{ return Text_iterator(line.begin(), (*line.begin()).begin()); }
	Text_iterator end()                 // one beyond the last character of the last line
	{
		auto last = line.end();
		--last;          // we know that the document is not empty
		return Text_iterator(last, (*last).end());
	}
};

istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch); ) {
		d.line.back().push_back(ch);         // add the character
		if (ch=='\n')
			d.line.push_back(Line{});     // add another line
	}
	if (d.line.back().size()) d.line.push_back(Line{});    // add final empty line
	return is;
}



void erase_line(Document& d, int n)
{
	if (n<0 || d.line.size()-1<=n) return;
	auto  p = d.line.begin();
	advance(p,n);
	d.line.erase(p);
}

template<typename Iter>     // requires Forward_iterator<Iter>
void advance(Iter& p, int n)
{
	while (0<n) { ++p; --n; }
}

void print(Document& d)
{
	for (auto p : d) cout << p;
}

//----------------------------------------------------------------------------
// Helper functions

bool match(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return false;

	for (auto it = s.begin(); it!=s.end(); ++it) 
	{
		if (*first != *it || first == last) return false;
		++first;
	}

	return true;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size()==0) return last;      // can’t find an empty string
	char first_char = s[0];
	while (true) {
		Text_iterator p = std::find(first,last,first_char);
		if (p==last || match(p,last,s)) return p;
		first = ++p;                     // look at the next character
	}
}

void erase_txt(Text_iterator first, Text_iterator last)
{
	if (first == last) return;
	auto it = first;

	while (first!=last) {
		it.erase();
		--last;
	}
}

string read_word(Text_iterator b, Text_iterator e)
{
	string s;
	while (!isspace(*b) && b != e) {
		s.push_back(*b);
		++b;
	}
	return s;
}
string read_word_alpha(Text_iterator b, Text_iterator e)
{
	string s;
	while (isalpha(*b) && b != e) {
		s.push_back(*b);
		++b;
	}
	return s;
}

bool find_char(string& s, char& c)
{
	for (char x : s) {
		if (x == c) return true;
	}
	return false;
}

string read_word_sep(Text_iterator b, Text_iterator e, string sep)
{
	string s;
	while ( b != e && !find_char(sep,*b)) {
		s.push_back(*b);
		++b;
	}
	return s;
}

//----------------------------------------------------------------------------
// ex6 --> Implement a simple Find and Replace function
Text_iterator find_replace(Document& d, const string& s, const string& ins)
{
	if (s.size() == 0) return d.end();

	Text_iterator first = find_txt(d.begin(), d.end(), s);
	Text_iterator last = first;

	while (first != d.end()) {
		last = first;
		advance(last, s.size());
		erase_txt(first,last);
		first.insert(ins);
		advance(first,ins.size());		// Handles substitutions with same word or beginning the same (like Jack --> Jack the reaper), avoid infinite loops.
		first = find_txt(first, d.end(), s);
	}

	return first;
}

//----------------------------------------------------------------------------
// ex7 --> Find the lexicographically last string
string find_last( Text_iterator b, Text_iterator e)
{
	string last = read_word(b,e);
	string tmp = last;

	while (b != e) {
		tmp = read_word_alpha(b,e);
		if ( tmp < last && !tmp.empty()) {
			last = tmp;
		}
		if (!tmp.empty()) advance(b,tmp.size());
		else ++b;
	}
	return last;
}

//----------------------------------------------------------------------------
// ex8 --> Count number of characters in the document
int count_chars( Text_iterator b, Text_iterator e) 
{
	int count = 0;
	while (b != e) {
		++count;
		++b;
	}
	return count;
}

//----------------------------------------------------------------------------
// ex9-10 --> Count number of words in the document
int count_words( Text_iterator b, Text_iterator e)
{
	int count = 0;
	string s;

	while (b != e) {
		s = read_word(b,e);
		if (!s.empty()) {
			advance(b,s.size());
			count++;
		}
		else ++b;
	}
	return count;
}
 
int count_words_alpha( Text_iterator b, Text_iterator e)
{
	int count = 0;
	string s;

	while (b != e) {
		s = read_word_alpha(b,e);
		if (!s.empty()) {
			advance(b,s.size());
			count++;
		}
		else ++b;
	}
	return count;
}

int count_words_sep( Text_iterator b, Text_iterator e, string sep)
{
	int count = 0;
	string s;

	while (b != e) {
		s = read_word_sep(b,e,sep);
		if (!s.empty()) {
			advance(b,s.size());
			count++;
		}
		else ++b;
	}
	return count;
}

//----------------------------------------------------------------------------
//
int main()
{
	Document doc;
	ifstream ifs {"Document.txt"};
	if (!ifs) error("cannot open file\n");
	ifs >> doc;
	print(doc);
	Text_iterator it = find_replace(doc, "better.", "AAAA");
	Text_iterator it2 = find_replace(doc, "Jack", "Jack the Reaper");
	Text_iterator it3 = find_replace(doc, "every", "Every");
	print(doc);

	cout << "\n------------------------------------------------------------------------------------------\n" << endl;

	cout << endl;
	print(doc);
	string s = find_last(doc.begin(), doc.end());
	int n = count_chars(doc.begin(), doc.end());
	int nw1 = count_words(doc.begin(), doc.end());
	int nw2 = count_words_alpha(doc.begin(), doc.end());
	string sep {" \n"};
	int nw3 = count_words_sep(doc.begin(), doc.end(), sep);
	cout  << "Last word lexycographycally: " << s << endl;
	cout  << "Number of characters in the document: " << n << endl;
	cout  << "Number of words (white spaced) in the document: " << nw1 << endl;
	cout  << "Number of words in the document: " << nw2 << endl;
	cout  << "Number of words (spaced with = ' " << sep << " ') in the document: " << nw3 << endl;

	cout << "\n------------------------------------------------------------------------------------------\n" << endl;

}
