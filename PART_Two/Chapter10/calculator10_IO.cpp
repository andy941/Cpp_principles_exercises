





/*
   Couldn't do it properly, we are not supposed to use things like pointers
   and I don't know how to seemlessly switch the token_stream get() function
   from reding to cin to ifstream.
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
	istream& stream;

public:
	Token_stream() :full(0), buffer(0), stream(cin) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char constant = 'C';
const char help = 'H';

Token Token_stream::get()
{ 
	if (full) { full = false; return buffer; }
	char ch;
	stream.get(ch);

	// for ex05: changed cin with cin.get() to read every character and the following
	// is used to read through whitespaces and return print when newline is found
	while (isspace(ch)) {
		if (ch == '\n') return Token(print);
		stream.get(ch);
	}

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
	{	stream.unget();
	double dval;
	stream >> dval;
	int val = narrow_cast<int>(dval);
	return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch; while (stream.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_') s += ch; //////////// Was s = ch goddammit Bjarne!  //////////// Ex7 Add the '_' in the variable name
			stream.unget();
			//if (s == "let") return Token(let);   /////// Drill ex10
			//if (s == "quit") return Token(quit); /////// changed name -> quit (which is const char 'Q') to close properly
			if (s == "quit") return Token(quit);   ////// Drill ex11 change "quit" in "exit"
													////// ex08: quit
			if (s == "const") return Token(constant);   ////// Drill ex11 change "quit" in "exit"
			if (s == "help") return Token(help);   ////// Drill ex11 change "quit" in "exit"
													////// ex08: quit
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
	while (stream >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	bool constant;
	Variable(string n, double v, bool constant) :name(n), value(v), constant(constant) { }
};

class Symbol_table {      ////// build a class to encompass var_table and all the operation related to it

	vector<Variable> var_table {};

	public:
	double get_value(string);
	void set_value(string, double);
	bool is_declared(string);
	void declare(string, double, bool);
};

double Symbol_table::get_value(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);
}

void Symbol_table::set_value(string s, double d)
{
	for (int i = 0; i <= var_table.size(); ++i) {
		if (var_table[i].name == s & !var_table[i].constant) {
			var_table[i].value = d;
			return;
		} 
		if (var_table[i].name == s & var_table[i].constant) {
			error("Can't change a constant!");
		}
	}

	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

void Symbol_table::declare(string name, double value, bool is_const) {
	var_table.push_back(Variable(name, value, is_const));
}

//ifstream ifs {"IO_test"};
//Token_stream ts {ifs};
Token_stream ts;
Symbol_table st;

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
		return st.get_value(t.name);
	default:
		error("primary expected");
	}
}


double reassign()         // Exercise ex02
{
	Token t = ts.get();
	if (t.kind == name) {
		if (st.is_declared(t.name)) {
			Token t2 = ts.get();
			if (t2.kind == '=') {
				double d = expression();
				st.set_value(t.name, d);
				return d;
			} 
			else { ts.unget(t2); return st.get_value(t.name); 
			}
		} else error("Variable not yet declared. Please declare it first with:\nlet [var] = [value];\n");
	} 
	ts.unget(t);
	return primary();
}

double log()         // Drill ex07: add  sqrt() function to the calculator
{
	Token t = ts.get();
	if (t.name == "log") {

		t = ts.get();
		if (t.kind != '(') error("'(' missing. Did you mean to define a pow(x,y) operation?");
		double d = expression();

		if (d <= 0) error("log() not defined for numbers <= 0");

		double res = std::log(d);

		t = ts.get();
		if (t.kind != ')') error("')' missing. Did you mean to define a pow(x,y) operation?");

		return res;
	}
	else ts.unget(t);
	return reassign();
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
	return log();
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
	if (st.is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	st.declare(name, d, false);
	return d;
}

double constant_set()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	st.declare(name, d, true);
	return d;
}

double Help()      ///////// ex07
{
	string message =  "\nThis is a help message.\n"
		"\n"
		"Unfortunately I am too lazy to write it\n"
		"properly.\n"
		"Sorry.\n"
		"\n";
	cout << message;
	return 0;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	case constant:
		return constant_set();
	case help:
		return Help();
	default:
		ts.unget(t);
		return expression();
	}
}

// ex10
double FileIN()
{
	Token t = ts.get();

	if (t.name == "from") {
		t = ts.get();
		ifstream ifs {t.name};
		if (!ifs) error("Can't open file\n");
		ts.FileStream(ifs);
		return 0;
	}

	ts.unget(t);
	return statement();
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

		if (t.name == "from") {
			t = ts.get();
			ifstream ifs {t.name};
			if (!ifs) error("Can't open file\n");
			ts.FileStream(ifs);
			continue;
		}

		ts.unget(t);

		cout << result << FileIN() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {

	st.declare("k", 1000, true); ///////// Drill .06: add k = 1000 definition.
	st.declare("quit", 0, true); ///////// ex07: need this for help message
	st.declare("help", 0, true); ///////// ex07: need this for help message

	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != print);
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != print);
	return 2;
}
