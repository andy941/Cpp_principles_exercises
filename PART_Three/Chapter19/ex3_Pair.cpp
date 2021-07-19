
#include "../std_lib_facilities.h"

/*
 * this is a rewriting of my Symbol_table from chapter 7, exercise 4 on calculator_buggy08.cpp
 * I called Pair Variable and I had a bool to know if it was a constant. I left the bool there.
*/

template <typename T,typename U>
struct Variable
{
	T name {};
	U value {};
	bool constant {false};
	Variable() = default;
	Variable(T n, U v, bool constant) :name(n), value(v), constant(constant) { }
};

template <typename T,typename U>
class Symbol_table 
{    
	vector<Variable<T,U>> var_table {};

	public:
	Symbol_table() = default;

	U get_value(T);
	void set_value(T, U);
	bool is_declared(T);
	void declare(T, U, bool);
};

template <typename T,typename U>
U Symbol_table<T,U>::get_value(T s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;

	error("get: undefined name ", s);
}

template <typename T,typename U>
void Symbol_table<T,U>::set_value(T s, U d)
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

template <typename T,typename U>
bool Symbol_table<T,U>::is_declared(T s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

template <typename T, typename U>
void Symbol_table<T,U>::declare(T name, U value, bool is_const) 
{
	var_table.push_back(Variable<T,U>(name, value, is_const));
}

int main() 
{
	Symbol_table<string, double> s;
	s.declare("const", 78.90, true);
	s.declare("nonconst", 80, false);
	s.set_value("nonconst", 50);
	cout << s.get_value("const") << '\t' << s.get_value("nonconst") << endl;

}
