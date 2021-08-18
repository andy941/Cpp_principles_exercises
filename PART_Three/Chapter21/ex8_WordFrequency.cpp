#include "../std_lib_facilities.h"

int main() 
{
	map<string,int> words;         // keep (word,frequency) pairs
	for (string s; cin>>s; ) {
		if (s == "EOF") break;  
		++words[s];                   // note: words is subscripted by a string
	}

	cout << "Order by word: " << endl;
	for (const auto& p : words)
		cout << p.second << ": " << p.first << '\n';
	// easiest solution is to move everything into a multimap and invert value:key
	multimap<int, string> freq;
	for (const auto& p : words) {
		freq.insert(pair<int,string>{ p.second, p.first });
	}
	cout << "Order by word frequency: " << endl;
	for (const auto& p : freq)
		cout << p.first << ": " << p.second << '\n';
	
}




