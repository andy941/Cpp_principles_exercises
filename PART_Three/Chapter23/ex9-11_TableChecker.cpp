#include "../std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

struct bad_from_string : std::bad_cast {  // class for reporting string cast errors
	const char* what() const noexcept override
	{
		return "bad cast from string";
	}
};

template<typename T> T from_string(const string& s)
{
	istringstream is {s};
	T t;
	if (!(is >> t)) throw bad_from_string{};
	return t;
}

struct Class
{
	int boys { 0 };
	int girls { 0 };
	int total { 0 };

	Class() = default;
};

int main()
{
	map<int,Class> m;

	ifstream in {"table_students.txt"};              // input file
	if (!in) error("no input file");
	ofstream out {"table_students_summary.txt"};

	string line;                                      // input buffer
	int lineno = 0;

	regex header {R"(^[\w ]+(           [\w ]+)*$)"};                   // header line
	regex row {R"(^([\d,\w,\s]+)\t(\d+)\t(\d+)\t(\d+)$)"};      // data line
	regex year {R"(^\d+)"};

	if (getline(in,line)) {                      // check header line
		cerr << line << endl;
		smatch matches;
		if (regex_match(line, matches, header)) {
			error("no header");
		}
	}

	// column totals:
	int boys = 0;
	int girls = 0;

	while (getline(in,line)) {
		++lineno;
		if (line == "") continue;

		smatch matches;
		if (!regex_match(line, matches, row))
			cerr << "bad line: " <<  lineno << '\n';

		for (size_t i = 1; i<matches.size(); i++) cerr << matches[i] << ',';
		cerr << endl;

		if (in.eof()) cout << "at eof\n";

		// check row:
		int curr_boy = from_string<int>(matches[2]);
		int curr_girl = from_string<int>(matches[3]);
		int curr_total = from_string<int>(matches[4]);
		if (curr_boy+curr_girl != curr_total)  error("bad row sum \n");

		//if (matches[1]=="Alle klasser") {           // Simplify this
		if ((in>>ws).eof()) {
			if (curr_boy != boys) error("boys don't add up\n");
			if (curr_girl != girls) error("girls don't add up\n");
			//if (!(in>>ws).eof()) error("characters after total line");	// Don't need this anymore
			int tot { 0 };
			for (auto& x : m) {
				out << x.first << '\t' 
					<< x.second.boys << '\t' 
					<< x.second.girls<< '\t' 
					<< x.second.total << '\t';
				if (tot == 0) out << "First Year" << '\n'; 
				else if (tot < x.second.total) out << "Increase" << '\n'; 
				else if (tot > x.second.total) out << "Decrease" << '\n'; 
				else if (tot == x.second.total) out << "Stationary" << '\n'; 
				tot = x.second.total;
			}
			cerr << "Reached end" << endl;
			return 0;
		}

		// update totals:
		boys += curr_boy;
		girls += curr_girl;

		smatch match_year;
		string s = matches[1];
		cerr << s << endl;
		if (regex_search(s, match_year, year)) {
			cerr << "REACH" << endl;
			int y = from_string<int>(match_year[0]);
			m[y].boys += curr_boy;
			m[y].girls += curr_girl;
			m[y].total += curr_total;
		}
	}

	error("didn't find total line");
}
