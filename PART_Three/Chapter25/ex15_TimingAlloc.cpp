
#include <boost/pool/poolfwd.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<cmath>
#include "chrono"
#include<stdio.h>
#include<boost/pool/pool.hpp>
#include <random>

using namespace std;


struct default_user_allocator_new_delete; // see User Allocators
struct default_user_allocator_malloc_free; // see User Allocators

class Timer
{
    
	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
	public:
	Timer() = default;
	~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		printf("Time: \t\t\t\t%.10f seconds.\n", elapsed.count() * 1e-9);
	}
};

int main() 
{
	constexpr int MAX { 10000 };
	constexpr int SIZE { 1024/8 };

	std::vector<char*> s;
	std::vector<int> ind(10000);
	s.reserve(10010);
	for (int i = 0; i < MAX; i++) ind[i] = i;
	shuffle(ind.begin(), ind.end(), default_random_engine(33));

	cout << sizeof(boost::default_user_allocator_malloc_free::size_type) << endl;	// unsigned long 8 bytes
	boost::pool pl { 100, MAX+10 };													// 8*100 800 bytes chunks

	char* st { static_cast<char*>(malloc(100000)) };
	
	std::cout << "-- 10000 objects of random size using new --" << std::endl;
	{
		Timer t;
		for (int i = 0; i < MAX; i++) s.emplace_back(new char[rand()%SIZE]);
		for (int i = 0; i < MAX; i++) delete[] s[i];
	}
	std::cout << std::endl;

	s = std::vector<char*>();
	s.reserve(10010);
	std::cout << "-- 10000 objects of random size using new deallocation at random --" << std::endl;
	{
		Timer t;
		for (int i = 0; i < MAX; i++) s.emplace_back(new char[rand()%SIZE+1]);
		for (int i = 0; i < MAX; i++) delete[] s[ind[i]];
	}
	std::cout << std::endl;

	s = std::vector<char*>();
	s.reserve(10010);
	std::cout << "-- 10000 objects of random size using new deallocation in reverse order --" << std::endl;
	{
		Timer t;
		for (int i = 0; i < MAX; i++) s.emplace_back(new char[rand()%SIZE+1]);
		for (int i = 0; i < MAX; i++) delete[] s[MAX-i];
	}
	std::cout << std::endl;

	s = std::vector<char*>();
	s.reserve(10010);
	std::cout << "-- 10000 objects of 800 Bytes from a pool --" << std::endl;
	{
		Timer t;
		for (int i = 0; i < MAX; i++) s.emplace_back(static_cast<char*>(pl.malloc()));
		for (int i = 0; i < MAX; i++) pl.free(s[i]);
	}
	std::cout << std::endl;

	s = std::vector<char*>();
	s.reserve(10010);
	std::cout << "-- 10000 objects of random size on a stack --" << std::endl;
	{	// Pseudo stack, allocated memory is filled bottom up and freed in reverse order.
		Timer t;
		char* revert = st;
		int n = rand()%SIZE+1;
		for (int i = 0; i < MAX; i++) {
			s[i] = new (st + sizeof(char)*n) char[n];
		}

		for (int i = 0; i < MAX; i++) {		// the stack memory is contiguous and is sufficient to move the pointer to peek the next element
			//delete[] st;			// doesn't work, not sure why. probably I am messing up the allocation/deallocation
			st = s[MAX - i];
		}
		free(revert);				// free the stack
		st = nullptr;
	}
	std::cout << std::endl;
}



