/*
 * The only way to make this work is to clone this repository:
 *		https://github.com/cortical-iv/hello_fltk.git
 *	And follow the instructions, essentially the most reliable
 *	course of action is to have all the files in the work directory
 *	and then compile each time with this:
 *
 *	g++ -w -Wall -std=c++11 <file.cpp> Graph.cpp Window.cpp GUI.cpp Simple_window.cpp `fltk-config --ldflags --use-images` -o <file.o>
 *
*/

#include "../hello_fltk/Window.h"  
#include "../hello_fltk/GUI.h"  
#include "../hello_fltk/Graph.h"

using namespace Graph_lib;


//----------------------------------------------------------------------------------------------------------------
//The calculator script modified to take an input string stream and save to an output stringstream
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
	istream& is;

public:
	Token_stream(istream& i) :full(0), buffer(0), is{i} { }

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
	is.get(ch);

	// for ex05: changed is with is.get() to read every character and the following
	// is used to read through whitespaces and return print when newline is found
	while (isspace(ch)) {
		if (ch == '\n') return Token(print);
		is.get(ch);
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
	{	is.unget();
	double dval;
	is >> dval;
	int val = static_cast<int>(dval);
	return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch; while (is.get(ch) && (isalpha(ch) || isdigit(ch)) || ch == '_') s += ch; //////////// Was s = ch goddammit Bjarne!  //////////// Ex7 Add the '_' in the variable name
			is.unget();
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
	while (is >> ch)
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

Symbol_table st;

double expression(Token_stream& ts);

double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression(ts);
	t = ts.get();
	if (t.kind != ')') error("'(' expected");
	return d;        ////// This line was missing
	}
	case '-':
		return -primary(ts);
	case '+':  ///////// Careful his one was added because seen in the chapter (handle + in front of the equation).
			   ///////// Could break it break something? Seems to work fine.
		return primary(ts);
	case number:
		return t.value;
	case name:
		return st.get_value(t.name);
	default:
		error("primary expected");
	}
}


double reassign(Token_stream& ts)         // Exercise ex02
{
	Token t = ts.get();
	if (t.kind == name) {
		if (st.is_declared(t.name)) {
			Token t2 = ts.get();
			if (t2.kind == '=') {
				double d = expression(ts);
				st.set_value(t.name, d);
				return d;
			} 
			else { ts.unget(t2); return st.get_value(t.name); 
			}
		} else error("Variable not yet declared. Please declare it first with:\nlet [var] = [value];\n");
	} 
	ts.unget(t);
	return primary(ts);
}

double log(Token_stream& ts)         // Drill ex07: add  sqrt() function to the calculator
{
	Token t = ts.get();
	if (t.name == "log") {

		t = ts.get();
		if (t.kind != '(') error("'(' missing. Did you mean to define a pow(x,y) operation?");
		double d = expression(ts);

		if (d <= 0) error("log() not defined for numbers <= 0");

		double res = std::log(d);

		t = ts.get();
		if (t.kind != ')') error("')' missing. Did you mean to define a pow(x,y) operation?");

		return res;
	}
	else ts.unget(t);
	return reassign(ts);
}

double pow(Token_stream& ts)         // Drill ex07: add  sqrt() function to the calculator
{
	Token t = ts.get();
	if (t.name == "pow") {

		t = ts.get();
		if (t.kind != '(') error("'(' missing. Did you mean to define a pow(x,y) operation?");
		double d = expression(ts);

		t = ts.get();
		if (t.kind != ',') error("',' missing. Did you mean to define a pow(x,y) operation?");

		t = ts.get();
		
		int exponent = static_cast<int>(t.value);
		double res = std::pow(d,exponent);

		t = ts.get();
		if (t.kind != ')') error("')' missing. Did you mean to define a pow(x,y) operation?");

		return res;
	}
	else ts.unget(t);
	return log(ts);
}

double Sqrt(Token_stream& ts)         // Drill ex07: add  sqrt() function to the calculator
{
	Token t = ts.get();
	if (t.name == "sqrt") {
		double d = pow(ts);
		if (d < 0) error("the sqrt() is not defined for negative numbers");
		return sqrt(d);
	}
	else ts.unget(t);
	return pow(ts);
}

double term(Token_stream& ts)
{
	double left = Sqrt(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= Sqrt(ts);
			break;
		case '/':
		{	double d = Sqrt(ts);
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

double expression(Token_stream& ts)
{
	double left = term(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term(ts);
			break;
		case '-':
			left -= term(ts);
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration(Token_stream& ts)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression(ts);
	st.declare(name, d, false);
	return d;
}

double constant_set(Token_stream& ts)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression(ts);
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

double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(ts);
	case constant:
		return constant_set(ts);
	case help:
		return Help();
	default:
		ts.unget(t);
		return expression(ts);
	}
}

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate(Token_stream& ts, ostream& os)
{
	try {
		//cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		os << result << statement(ts) << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess(ts);
	}
}


//--------------------------------------------------------------------------------------------------
//GUI implementation, two boxes for IO and one button to "Calculate"

struct Calculator_window : Graph_lib::Window {

	Calculator_window(Point xy, int w, int h, const string& title);

	private:
	Button Calculate_button;          // add (Expression,Calculate_y) to lines
	Button quit_button;
	In_box Expression;
	Out_box Result;

	void Calculate();
	void quit() { hide(); };
};

Calculator_window::Calculator_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	Calculate_button{Point{x_max()-150,0}, 70, 20, "Calculate",
		[](Address, Address pw) {reference_to<Calculator_window>(pw).Calculate();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Calculator_window>(pw).quit();}},
	Expression{Point{x_max()-310,0}, 50, 20, "Expression:"},
	Result{Point{100,0}, 100, 20, "Result:"}

{
	attach(Calculate_button);
	attach(quit_button);
	attach(Expression);
	attach(Result);
}
		
void Calculator_window::Calculate()
{
	// this is a silly little hack to not have to refactor the calculator code
	string s = Expression.get_string() + ';';

	istringstream iss {s};
	Token_stream input {iss};
	ostringstream output;

	calculate(input,output);

	string result = output.str();

	// Strip a weird ^J that appears at the end, I suspect is something like the "Return" key or similar
	string result_stripped {result.begin(), result.end()-1};
	Result.put(result_stripped);

	redraw();
}


int main()
{
	try {
		Calculator_window win {Point{100,100},600,400,"Calculator"};
		return gui_main();
	}
	catch(exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
}





