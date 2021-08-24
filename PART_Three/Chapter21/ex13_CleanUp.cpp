//#include "../std_lib_facilities.h"
#include <algorithm>
#include <numeric>
#include <map>


void remove_punct(string& s)	// don't transform the apostrophe, eliminate the possessive 's and predicate 's unfortunately.
{
	s.erase(std::remove_if(s.begin(), s.end(), [&](char c) { return !isalpha(c) && c != '\''; }), s.end());
	if (s.size() < 2) return;
	if (s[s.size()-2] == '\'' && s[s.size()-1] == 's') s.erase(s.begin()+s.size()-2, s.begin()+s.size());
}

void to_lower(string& s)	// don't transform the apostrophe
{
	for (auto it = s.begin(); it != s.end(); ++it) { *it = std::tolower(*it); }
}

void remove_plurals(map<string,int>& m, string& s)
{
	if (*s.end() == 's') {
		s.pop_back();
		auto it = m.find(s);
		if (it != m.end()) ++it->second;
		else {
			s.push_back('s'); 
			m.insert(pair<string,int> {s,1});
		}
	}
}

void check_for_nots(map<string,int>& m, string& s)
{
	if (s.size() < 3) return;
	if (s[s.size()-2]=='\'' && s[s.size()-1]=='t' ) {
		s.erase(s.size()-2);
		++m["not"];
	}

}

map<string,int> cleanup(istream& is)
{
	map<string,int> m;
	map<string,int> result;

	string s;

	while (is >> s) {
		remove_punct(s);
		to_lower(s);
		remove_plurals(m, s);
		check_for_nots(result, s);		// Will add 1 to not word if found, in the resulting map dataset
		++result[s];
	}

	return result;
}


//----------------------------------------------------------------------------
//
//int main()
//{
//	string file;
//	ifstream ifs {"Document.txt"};
//	if (!ifs) error("cannot open file\n");
//	map<string,int> m = cleanup(ifs);
//	for (auto& x : m) cout << "# " << x.first << '\t' << x.second << endl;
//
//	ifs.close();
//}
