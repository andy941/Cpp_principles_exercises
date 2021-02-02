#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

// handy function to print a vector
void printvec(std::vector<std::string> x) {
    for (std::string i : x) {
        std::cout << i << "\n";
    }
}

class Day{
	public:
		Day();
		std::string day;
		double amount;

		Day(std::string d, double a)
		:day(d), amount(a) {}
};
			
int main() {

	std::string day;
	double amount;
	std::vector<Day> days = {};
	std::vector<std::string> Rejected = {};
	std::vector<std::string> Week = {"Mon","Tue","Wed","Thu", "Fri","Sat","Sun"};

	for (std::string x : Week) {
		days.push_back(Day(x,0));
	}
	

    std::cout << "Please enter a Day of the week and a value\n" <<
        "Accepted Days:\n";
    printvec(Week);
    std::cout << "Terminate with 'end' as a day name\n";

    while (std::cin >> day >> amount) {

		if (day == "end" & amount == 0) break;

		bool check = false;

		for (int i = 0; i < days.size(); i ++) {
			if (days[i].day == day) {
				days[i].amount += amount;
				check = true;
			}
		}

		if (!check) Rejected.push_back(day);

    }

    for (Day x : days) {
        std::cout << x.day << '\t' << x.amount << "\n";
    }

    std::cout << "Rejected " << Rejected.size() << " days: " << "\n";
    printvec(Rejected);

    return 0;
}



