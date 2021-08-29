//#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <chrono>
using namespace std;

typedef vector<string>::const_iterator Line_iter;

class Message {   // a Message points to the first and the last lines of a message
	Line_iter first;
	Line_iter last;
	public:
	Message(Line_iter p1, Line_iter p2) :first{p1}, last{p2} { }
	Line_iter begin() const { return first; }
	Line_iter end() const { return last; }
	// . . .
};
using Mess_iter = vector<Message>::const_iterator;

struct Mail_file {                                  // a Mail_file holds all the lines from a file
	// and simplifies access to messages
	string name;                              // file name
	vector<string> lines;               // the lines in order
	vector<Message> m;              // Messages in order

	Mail_file(const string& n);     // read file n into lines

	Mess_iter begin() const { return m.begin(); }
	Mess_iter end() const { return m.end(); }
};

Mail_file::Mail_file(const string& n)
	// open file named n
	// read the lines from n into lines
	// find the messages in the lines and compose them in m
	// for simplicity assume every message is ended by a ---- line
{
	ifstream in {n};                               // open the file
	if (!in) {
		cerr << "no " << n << '\n';
		exit(1);                                   // terminate the program
	}

	for (string s; getline(in,s); )         // build the vector of lines
		lines.push_back(s);

	auto first = lines.begin();            // build the vector of Messages
	for (auto p = lines.begin(); p!=lines.end(); ++p) {
		if (*p == "---END OF MESSAGE---") {               // end of message
			m.push_back(Message(first,p));
			first = p+1;                 // ---END OF MESSAGE--- not part of message
		}
	}
}

bool find_from_addr(const Message* m, string& s)
{
	regex pat { R"(^(f|F)rom:.*<(.*)>)" };
	for (const auto& x : *m) {
		smatch matches;
		if (regex_search(x, matches, pat)) {
			s = matches[2];
			return true;
		}
	}
	return false;
}

string find_subject(const Message* m)
{
	regex pat { R"(^(s|S)ubject:\s(.*)\s*$)" };
	for (const auto& x : *m) {
		smatch matches;
		if (regex_search(x, matches, pat)) return matches[2];
	}
	return "";
}

int main() 
{
	Mail_file mfile {"200_eml/Total_massive.eml"};          // initialize mfile from a file


	cout << "Loading multimap" << endl;
	// first gather messages from each sender together in a multimap:
	multimap<string, const Message*> sender;

	for (const auto& m : mfile) {
		string s;
		if (find_from_addr(&m,s)) {
			sender.insert(make_pair(s,&m));
		}
	}

	cout << "Loading unordered multimap" << endl;
	// second gather messages from each sender together in a unordered_multimap:
	unordered_multimap<string, const Message*> u_sender;

	for (const auto& m : mfile) {
		string s;
		if (find_from_addr(&m,s)) {
			u_sender.insert(make_pair(s,&m));
		}
	}

	// benchmark with O2 optimization ----------------------------------------
	
	cout << "Starting multimap" << endl;
    auto begin = std::chrono::high_resolution_clock::now();
	// now iterate through the multimap
	// and extract the subjects
	auto pp = sender.equal_range("timc@2ubh.com");

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("multimap: \t\t\t\t%.10f seconds.\n", elapsed.count() * 1e-9);

	cout << "Starting unordered multimap" << endl;
    begin = std::chrono::high_resolution_clock::now();
	// now iterate through the multimap
	// and extract the subjects
	auto upp = u_sender.equal_range("timc@2ubh.com");

    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("unordered_multimap: \t\t\t\t%.10f seconds.\n", elapsed.count() * 1e-9);
}

