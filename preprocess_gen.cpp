#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

list<string> c;
int sz;
vector<int> vUID{0,2};

// Struct for the Oscars dataset
struct data {
	vector<string> data;
	int size;
	list<string> categories;
	string UID;
} ;

// Prints struct as a string
string print_data(data o) {
	string s = "";
	for (string t : o.data){
		s.append(t + ", ");
	}
	// cout << o.UID << endl;
	return o.UID + ": " + s.substr(0, s.size()-2);
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

// Function to turn a string into an data object
data new_data(string s){
	data o;
	vector<string> l = getList(s);

	if(l.size() > 0){
		o.data = l;
		o.categories = c;
		o.size = sz;
	}
	
	// set UID to values in vUID global vector
	string temp = "";
	for (int i : vUID){
		if (i < o.size){
			temp = temp + o.data[i] + ", ";
		}
	}
	o.UID = temp.substr(0, temp.size()-2);
	cout << o.UID << endl;

	return o;
}

// Function to convert CSV file into list of Oscar objects
list<data> getData(string file) {
	ifstream fin;
	fin.open(file);

	std::list<data> l = {};

	string line;

	// Initialize categories and size
	getline(fin, line);
	std::vector<string> v = getList(line);
	for (string s : v){
		c.push_back(s);
	}
	sz = c.size();

	// Iterate through file and create Data object
	while (!fin.eof()){
		getline(fin, line);
		if (line.length() > 0){
			l.push_back(new_data(line));
		}
	}

	fin.close();
	return l;
}

int main() {
	std::cout << "Begin Parsing\n" 
				<< "--------------------" << endl;
	// ofstream ofs;
	// ofs.open("out.txt");

	// string file = "data/test.csv";
	// string file = "data/fake.csv";
	string file = "data/oscar_small.csv";
	// string file = "data/oscar_large.csv";

	// Output list of data objects
	list<data> l = getData(file);
	// for (data o : l){
	// 	ofs << print_data(o) << endl;
	// }
	// ofs.close();

	return 0;
}