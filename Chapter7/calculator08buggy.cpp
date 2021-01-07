
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "../std_lib_facilities.h"

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), name(n) { } /////////////////// Drill: Added this to handle variables
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case ',':			///// Added for Drill ex09 pow()
		return Token(ch);
	case '#':			///// Drill ex10
		return Token(let);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();
	double val;
	cin >> val;
	return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_') s += ch; //////////// Was s = ch goddammit Bjarne!
			cin.unget();
			//if (s == "let") return Token(let);   /////// Drill ex10
			//if (s == "quit") return Token(quit); /////// changed name -> quit (which is const char 'Q') to close properly
			if (s == "exit") return Token(quit);   ////// Drill ex11 change "quit" in "exit"
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("'(' expected");
	return d;        ////// This line was missing
	}
	case '-':
		return -primary();
	case '+':  ///////// Careful his one was added because seen in the chapter (handle + in front of the equation).
			   ///////// Could break it break something? Seems to work fine.
		return primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double pow()         // Drill ex07: add  sqrt() function to the calculator
{
	Token t = ts.get();
	if (t.name == "pow") {

		t = ts.get();
		if (t.kind != '(') error("'(' missing. Did you mean to define a pow(x,y) operation?");
		double d = expression();

		t = ts.get();
		if (t.kind != ',') error("',' missing. Did you mean to define a pow(x,y) operation?");

		t = ts.get();
		
		int exponent = narrow_cast<int>(t.value);
		double res = std::pow(d,exponent);

		t = ts.get();
		if (t.kind != ')') error("')' missing. Did you mean to define a pow(x,y) operation?");

		return res;
	}
	else ts.unget(t);
	return primary();
}

double Sqrt()         // Drill ex07: add  sqrt() function to the calculator
{
	Token t = ts.get();
	if (t.name == "sqrt") {
		double d = pow();
		if (d < 0) error("the sqrt() is not defined for negative numbers");
		return sqrt(d);
	}
	else ts.unget(t);
	return pow();
}

double term()
{
	double left = Sqrt();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= Sqrt();
			break;
		case '/':
		{	double d = Sqrt();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {

	names.push_back(Variable("k", 1000)); ///////// Drill .06: add k = 1000 definition.

	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}
