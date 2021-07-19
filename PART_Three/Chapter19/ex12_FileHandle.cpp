#include "../std_lib_facilities.h"

class File_handle 
{
	fstream file;

	public:
	File_handle(string s)
		:file{s}
	{
		if (!file) error("File not found!");
		cerr << "Constructed File_handle" << endl;
	}

	File_handle(const File_handle&) = delete;
	File_handle& operator=(const File_handle&) = delete;

	~File_handle()
	{
		cerr << "Destroyed File_handle" << endl;
		if (file.is_open()) file.close();
		return;
	}

	
	fstream& attach() { return file; };
	fstream* attach_p() { return &file; };

	void print(ostream& os) 
	{
		while (file) {
			char c = file.get();
			cout << c;
		}
	}
};



int main() 
{

	File_handle stream {"Drill.cpp"};
	fstream& f = stream.attach();
	fstream* fp = stream.attach_p();

	char c = fp->get();
	cout << c;

	while (*fp) {
		char c = fp->get();
		cout << c;
	}

	while (f) {
		char c = f.get();
		cout << c;
	}

	stream.print(cout);
	
	cerr << endl;
}
