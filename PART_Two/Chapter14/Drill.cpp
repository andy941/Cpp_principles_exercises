
#include "std_lib_facilities.h"           // if we want that “Next” button

using namespace std;

class B1 
{
	public:
	virtual void vf() {cout << "B1::vf()\n";}
	void f() {cout << "B1::f()\n";}
	//virtual void pvf() =0;
};

class B2 
{
	public:
	virtual void pvf() =0;
};

class D1 : public B1 
{
	public:
	void  vf() override {cout << "D1::vf()\n";}
	void f() {cout << "D1::f()\n";} 
};

class D2 : public D1 
{
	public:
	void  pvf() override {cout << "D2::pvf()\n";}
};

class D21 : public B2 
{
	string word = "D21";

	public:
	void  pvf() override {cout << word << "\n";}
};

class D22 : public B2 
{
	int num = 22;

	public:
	void  pvf() override {cout << num << "\n";}
};

void f(B2& arg)
{
	arg.pvf();
}

int main()
{
	//B1 b1 {};

	//b1.vf();
	//b1.f();

	//D1 d1 {};

	//d1.vf();
	//d1.f();
	//
	//B1& b1e {d1};

	//b1e.vf();
	//b1e.f();

	//D2 trial_d2 {};

	//trial_d2.vf();
	//trial_d2.f();
	//trial_d2.pvf();

	//D21 trial;
	//D22 trial2;
    //
	//f(trial);
	//f(trial2);
	
	return 0;
}


