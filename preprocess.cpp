#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

// Struct for the Oscars dataset
struct oscars {
	string category;
	string name;
	string film;
	string winner;
} ;

// Prints struct as a string
string print_oscars(oscars o) {
	string s = "";
	s.append(o.category + ", ");
	s.append(o.name + ", ");
	s.append(o.film + ", ");
	s.append(o.winner);
	return s;
}

// Helper function splitting string by ','
vector<string> getList(string s){
	vector<string> l = {};

	size_t pos = 0;
	std:string token;
	while ((pos = s.find(", ")) != std::string::npos) {
		token = s.substr(0, pos);
		l.push_back(token);
		s.erase(0, pos + 2);
	}
	if (s.length() > 0)
		l.push_back(s);
	return l;
}

// Function to turn a string into an Oscars object
oscars new_oscars(string s){
	oscars o;
	vector<string> l = getList(s);

	if(l.size() >= 4){
		o.category = l[0];
		o.name = l[1];
		o.film = l[2];
		o.winner = l[3];
	}

	return o;
}

// Function to convert CSV file into list of Oscar objects
list<oscars> getOscars(string file) {
	ifstream fin;
	fin.open(file);

	std::list<oscars> l = {};

	string line, temp;
	while (!fin.eof()){
		getline(fin, line);
		if (line.length() > 0)
			l.push_back(new_oscars(line));
	}

	fin.close();
	return l;
}

int main() {
	std::cout << "Begin Parsing\n" 
				<< "--------------------" << endl;

	string file = "data/test.csv";
	// string file = "data/oscar_small.csv";
	// string file = "data/oscar_large.csv";

	// Output list of oscars objects
	list<oscars> l = getOscars(file);
	cout << l.size() << endl;
	for (oscars o : l){
		cout << print_oscars(o) << endl;
	}

	return 0;
}