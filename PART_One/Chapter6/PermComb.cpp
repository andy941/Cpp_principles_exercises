#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

double Fact(int x) {
	double result = 1;

	if (x==0) return 1;

	for (int i = 1; i <= x; i++) {
		result *= i;
	}

	return result;
}

double Perm(int x, int y) {
	double result = Fact(x) / Fact(x-y);
	return result;
}

double Comb(int x, int y) {
	double result = Perm(x,y) / Fact(y);
	return result;
}

int main() {

	char Type;
	int x;
	int y;

	while (true) {
		std::cout << "Please insert the type of analysis with\n"
			"'C' for combination and 'P' for permutation, 'Q' for quit.\n";
		std::cin >> Type;

		if (Type == 'Q') break;

		std::cout << "Please insert the number of the elements in the set: ";
		std::cin >> x;

		std::cout << "Please insert the number of the elements in the subset: ";
		std::cin >> y;

		switch (Type) {
			case 'C':
				std::cout << "The number of possible combinations is: " << Comb(x,y) << "\n";
				break;
			case 'P':
				std::cout << "The number of possible permutations is: " << Perm(x,y) << "\n";
				break;
			default:
				std::cout << "I can't recognize the type of analysis ... " << "\n";
		}
	}
	std::cout << "\nBYE!\n";
	return 0;
}
