#include<iostream>
#include<string>
#include<sstream>
//#include "emp/data/DataNode.hpp"

using std::cin; using std::cout; using std::endl; using std::string;
using std::getline;
int split(int argc, char **argv) {
	string line;
	while(getline(cin, line)) { 
		float time;
		uint16_t arbid;
		std::istringstream iss(line);
		iss >> time;
		iss >> std::hex >> arbid;
		cout << arbid << endl; 
	}

	// split trace by ids
	// record statistics about the 	

}
