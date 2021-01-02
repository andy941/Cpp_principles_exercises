
#include "../std_lib_facilities.h"


//------------------------------------------------------------------------------

class Token{
public:
    char kind;        // what kind of token
    int value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, int val)     // make a Token from a char and a int
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
	public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
	private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case '=':    // for "print"
    case 'x':    // for "quit"
	case '!': case '~': case '&': case '^': case '|':
        return Token(ch);        // let each character represent itself
	
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': ////////////////////////////// THE '8' CASE !!!!

    {
        cin.putback(ch);         // put digit back into the input stream
        int val;
        cin >> val;              // read a floating-point number
        return Token('8', val);   // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

int Or();    // declaration so that And() can call Or()

//------------------------------------------------------------------------------
// deal with prefix unary operators ! and ~
int Prefix() {

	int result = 0;
	Token t = ts.get();        // get the next token from token stream

		switch (t.kind) {
			case '!':
				t = ts.get();        // get the next token from token stream
				result = !t.value;
			case '~':
				t = ts.get();        // get the next token from token stream
				result = ~t.value;
			case '8':
				result = t.value;
			default:
				cerr << "Error in prefix";
		}
	return result;
}

//------------------------------------------------------------------------------

// deal with numbers and parentheses
int And()
{
	int left = Prefix();
    Token t = ts.get();

	while (true) {
		switch (t.kind) {
			case '&': {
				left = (left & Prefix());
				t = ts.get();
			}
			default:
			ts.putback(t);     // put t back into the token stream
			return left;       
		}
	}	
}

//------------------------------------------------------------------------------

// deal with *, /, and %
int xOr()
{
    int left = And();
    Token t = ts.get();        // get the next token from token stream

	while (true) {
		switch (t.kind) {
			case '^': {
				left = (left ^ And());
			}
			default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}	
}

//------------------------------------------------------------------------------

// deal with + and -
int Or()
{
    int left = xOr();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream
	
    while (true) {
		switch (t.kind) {
			case '|': {
				left = (left | xOr());
			}
			default:
			ts.putback(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
    }
}


//------------------------------------------------------------------------------

int main() {

	cout  << "Welcome to our simple bitwise Or calculator. \nPlease enter bitwise expressions using integer numbers.\n"
		"to evaluate the expression terminate with  a '=' and to quit type 'q'\n";

	int val = 0;

	try
	{
		while (cin) {
			Token t = ts.get();

			if (t.kind == 'x') break; // 'q' for quit
			if (t.kind == '=')        // ';' for "print now"
				cout << "=" << val << '\n';
			else
				ts.putback(t);
			val = Or();
		}
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		return 2;
	}
}
//------------------------------------------------------------------------------

