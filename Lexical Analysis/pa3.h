#ifndef PA3_H
#define PA3_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
//Johncarlo Cerna
using namespace std;
using std::stack;
bool caselower(string toms) {
	for (int i = 0; i < (signed int)toms.size(); ++i) {
		if (toms[i] < 'a' || toms[i] > 'z')
			return false;
	}
	return true;
}

bool caseupper(string toms) {
	for (int i = 0; i < (signed int)toms.size(); ++i) {
		if (toms[i] < 'A' || toms[i] > 'Z')
			return false;
	}
	return true;
}

bool checkinteger(string toms) {
	return (toms.find_first_not_of("0123456789") == string::npos);
}
enum Place { //unscoped enumeration
	checkFLoop,
	checkCommas,
	checkLoopInt,
	checkOperIncre,
	checkCommaLPAR,
	checkLoopEnd,
	checkSemi,
	addOperands

};
class Data {
	vector<string> data; // stores all unique tokens of a specified category
public:
	int numData; // counts number of unique tokens acquired
	Data();
	void addNoDuplicate(string element); // add token only if it isn't already added
	string getData(int dex); // get token from index in vector
	bool isEmpty(); // is vector empty?
};
#endif
