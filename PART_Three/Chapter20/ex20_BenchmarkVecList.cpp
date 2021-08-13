#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<cmath>
#include "chrono"
#include<stdio.h>

void test(long long int MAX)
{
	using size_type = long long int;
	size_type num = rand()%MAX;
	std::vector<size_type> vec {num};
	std::vector<size_type> vec_r {num};
	vec_r.reserve(MAX+1);
	std::list<size_type> lst {num};

    auto begin = std::chrono::high_resolution_clock::now();
    
	size_type limit = MAX;
	std::vector<size_type>::iterator target;
	while ( --limit ) {
		num = rand()%MAX;
		target = vec.end();
		for (std::vector<size_type>::iterator it = vec.begin(); it != vec.end(); it++) {
			if (num < *it) {
				target = it;
				vec.insert(it, num);
				break;
			}
		}
		if (target == vec.end()) vec.push_back(num);
	}

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Vector: \t\t\t\t%.10f seconds.\n", elapsed.count() * 1e-9);

    begin = std::chrono::high_resolution_clock::now();
    
	limit = MAX;
	std::list<size_type>::iterator target_l;
	while ( --limit ) {
		num = rand()%MAX;
		target_l = lst.end();
		for (std::list<size_type>::iterator it = lst.begin(); it != lst.end(); it++) {
			if (num < *it) {
				target_l = it;
				lst.insert(it, num);
				break;
			}
		}

		if (target_l == lst.end()) lst.push_back(num);
	}
    
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("List: \t\t\t\t\t%.10f seconds.\n", elapsed.count() * 1e-9);

    begin = std::chrono::high_resolution_clock::now();
    
	limit = MAX;
	std::vector<size_type>::iterator target_vr;
	while ( --limit ) {
		num = rand()%MAX;
		target_vr = vec_r.end();
		for (std::vector<size_type>::iterator it = vec_r.begin(); it != vec_r.end(); it++) {
			if (num < *it) {
				target_vr = it;
				vec_r.insert(it, num);
				break;
			}
		}

		if (target_vr == vec_r.end()) vec_r.push_back(num);
	}
    
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Vector res: \t\t\t\t%.10f seconds.\n", elapsed.count() * 1e-9);
}

int main() 
{
	using size_type = long long int;
	constexpr size_type MAX	{100000};
	constexpr size_type INCR	{MAX/5};

	for (size_type i = INCR; i < MAX; i+=INCR) {
		std::cout << "---------------"  << "Testing sample size: " << i << "---------------" << std::endl;
		test(i);
		std::cout << std::endl;
	}
}



