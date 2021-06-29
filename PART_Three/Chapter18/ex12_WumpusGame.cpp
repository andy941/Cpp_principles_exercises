#include "../std_lib_facilities.h"

//___HELPERS_________________________________________________________________________

bool in(int n, vector<int> v)
{
	if (v.empty()) return false;
	for (int x : v) if (x == n) return true;
	return false;
}

bool in_connector(int n, int pos, vector<vector<int>> c)
{
	for (vector<int> v : c) {
		if (v[pos] == n) return true;
	}

	return false;
}

//___MAZE_________________________________________________________________________

class Maze 
{
	vector<vector<int>> rooms;
	int wumpus;
	int bat;
	int player;
	int pit;

	public: 
	Maze();
	bool game_state {false};		// true when you loose or win

	void print_all();
	int pos_wumpus() {return wumpus;}
	int pos_player() {return player;}
	int pos_bat() {return bat;}
	int pos_pit() {return pit;}
	void bat_flight();
	void move(int n);
	void status();
	void shoot_arrow();
	void get_input(char& ms, int& n);
	void turn();
};

Maze::Maze()
{
	// draw 3 vectors of ints from 1 to 20 (rooms) in random order
	// the vectors can't share the same room at the same position.
	// afterwards it's trivial to get 3 rooms vectors (tunnels) for each of the 
	// 20 rooms. Sometimes it doesn't work though, it's not optimal.
	// There are edge cases this doesn't account for. Maybe it's too trivial..
	// It's a graph problem, maybe a breadth first algorithm or something?
	int n = rand()%20;
	vector<int> v;
	vector<vector<int>> connector;

	for (int i =0; i < 3; i++) {
		for (int j =0; j < 20; j++) {
			while (in(n,v) || in_connector(n,j,connector)) {
				n = rand()%20;
			}
			v.push_back(n);
		}
		connector.push_back(v);
		v = {};
	}

	v = {};
	for (int i = 0; i < 20; i++) {
		for (vector<int> x : connector) {
			v.push_back(x[i]);
		}
		rooms.push_back(v);
		v = {};
	}


	v = {};
	for (int j =0; j < 4; j++) {
		while (in(n,v)) {
			n = rand()%20;
		}
		v.push_back(n);
	}

	wumpus = v[0];
	bat = v[1];
	player = v[2];
	pit = v[3];
}

void Maze::print_all()			// For DEBUG purposes
{
	cout << '\n';
	cout << "ROOMS TUNNELS" << endl;
	for (int j = 0; j < rooms.size(); j++) {
		cout << "Room" << j << ':' << '\t';
		for (int i = 0; i < rooms[j].size(); i++) {
			cout << rooms[j][i] << '\t';
		}
		cout << '\n';
	}
	cout << '\n';
	cout << "WUMPUS: " << wumpus << '\n';
	cout << "BAT: " << bat << '\n';
	cout << "PIT: " << pit << '\n';
	cout << "PLAYER: " << player << '\n';
	cout << '\n';
}
                                                        
void Maze::bat_flight()
{
	player = rand()%20;
	bat = rand()%20;
	 
	while (bat == player) {
		bat = rand()%20;
	}

	cout << "The bat brought you to room " << player << endl;
}

void Maze::move(int n)
{
	player = n;

	if (player == wumpus) {
		game_state = true;
		cout << "wumpus killed you! YOU LOOSE!" << endl;
	}

	if (player == pit) {
		game_state = true;
		cout << "you fell into a pit! YOU LOOSE!" << endl;
	}

	if (player == bat) {
		bat_flight();
	}
}

void Maze::status()
{
	if (in(wumpus, rooms[player])) cout << "Something smells bad ..." << '\n'; 
	if (in(pit, rooms[player])) cout << "I feel a breeze ..." << '\n'; 
	if (in(bat, rooms[player])) cout << "I hear a rattle ..." << '\n'; 
}

void Maze::shoot_arrow()
{
	if (in(wumpus, rooms[player])) {
		cout << "wumpus was in room " << wumpus << " you killed it!" << endl;
		game_state = true;
		return;
	}

	cout << "wumpus moves into an adjacent room ..." << endl;
	wumpus = rooms[wumpus][rand()%3];
	if (player == wumpus) {
		game_state = true;
		cout << "wumpus killed you! YOU LOOSE!" << endl;
	}
}

void Maze::get_input(char& ms, int& n)
{
	while (true) {

		cout << "\n-> insert character to move {m}, shoot an arrow {s} or quit {q}: ";
		cin >> ms;
		if (ms == 'q') return;
		if (ms == 'm') {
			cout << "\n-> Which room do you want to move to? [";
			for (int x : rooms[player]) cout << x << ' ';
			cout << "]: ";
			cin >> n;
			if (!in(n, rooms[player])) {
				ms = '#';
				cout << "\nNot a valid room!\n";
				return;
			}
			return;
		}
		if (ms == 's') {
			n = -1;
			return;
		}
		cout << "\nInput not recognized, try again" << endl;
	}
}
void Maze::turn()
{
	char ms {'#'};
	int n {-1};
	//print_all();
	status();
	get_input(ms,n);
	if (ms == 'm') move(n);
	if (ms == 's') shoot_arrow();
	if (ms == 'q') {
		cout << "SEE YOU SOON!" << endl;
		game_state = true;
	}
}

//___MAIN_________________________________________________________________________

int main() 
{
	// make the random number generator random at every game played
	srand(time(NULL));
	Maze m;
	int Turn = 1;

	cout << "\nWelcome to the dungeon, are you ready? "<< '\n' << endl;
	while (true) {

		cout << "\nROUND " << Turn << "	 ----------------------------------------"<< endl;
		m.turn();
		if (m.game_state) break;
		Turn++;
	}

	return 0;
}

