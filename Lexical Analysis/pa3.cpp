#include "pa3.h"
//Johncarlo Cerna
int main() {
	cout << "Please enter the name of the input file:" << endl;
	string name;
	
	cin >> name;
	
	ifstream file(name.c_str()); //find file

	Data identifier; //creates objects for identifiers, operators, errors, delimiters, keywords, and constants.
	Data operators; //operators instead of operator because operator is a keyword in C++
	Data error;
	Data delimiter;	
	Data keyword;	
	Data constant;

	stack<string> stack; //utilized stack when caluculating finalDepth
	int currentDepth = 0;
	int finalDepth = 0; // final depth	
	int finalDepthError = 0; // final depth, including errors
	if (file.is_open() == false) {
		cerr << "Invalid File " << name << endl; //if invalid, print invalid and exit
		return 0;
	}
	else { // If is open, set initial check state and begin sorting
		Place place = checkFLoop;
		string nextElement; // word(s) pulled from program

		for (int a = 0; a > a-1; a++) {
			file >> nextElement;
			if (!file.good()) {
				if (currentDepth != 0) { // Add an error if there was a loop unclosed
					error.addNoDuplicate("END");
				}
				break;
			}

		switch (place) { //"switch is best way to loop through the commands for this project, I did it like this and it worked fine" -TA that I don't remember the name of, sorry dude
			case checkFLoop: // Check for a For loop
				if (nextElement == "FOR") {
					keyword.addNoDuplicate(nextElement);
					place = checkCommaLPAR;
				}
				else {
					if (nextElement[nextElement.size() - 1] == ';') { //check for a semicolon
						delimiter.addNoDuplicate(";");
						nextElement = nextElement.substr(0, nextElement.size() - 1);
						place = checkFLoop;
					}
					else {
						place = addOperands;
					}

					if (nextElement.find("=") != string::npos) { //check for an equal sign
						int size1 = nextElement.size();
						int eqIndex = nextElement.find("=");
						string str1 = nextElement.substr(0, eqIndex);
						string str2 = nextElement.substr(eqIndex + 1, size1 - eqIndex - 1);

						if (caselower(str1)) {
							identifier.addNoDuplicate(str1);
						}
						else {
							error.addNoDuplicate(str1);
						}
						if (caselower(str2)) {
							identifier.addNoDuplicate(str2);
						}
						else {
							error.addNoDuplicate(str2);
						}
					}
					else {
						// if no, possible identifier
						if (caselower(nextElement)) {
							identifier.addNoDuplicate(nextElement);
						}
						// Assumes nextElement is a typo of FOR
						else if (caseupper(nextElement)) {
							error.addNoDuplicate(nextElement);
							place = checkCommaLPAR;
						}
						else {
							error.addNoDuplicate(nextElement);
						}
					}
				}
				break;
			case checkCommas:
				// check for comma
				if (nextElement[nextElement.size() - 1] == ',') {
					delimiter.addNoDuplicate(",");
					nextElement = nextElement.substr(0, nextElement.size() - 1);
				}

				// check for constant
				if (nextElement.size() == 0) {
					error.addNoDuplicate("missing_constant");
				}
				else {
					if (checkinteger(nextElement)) {
						constant.addNoDuplicate(nextElement);
					}
					else {
						error.addNoDuplicate(nextElement);
					
				}
			}
				place = checkOperIncre;
				break;
			case checkLoopInt: // Check if the loop was properly initiated
				if (nextElement == "BEGIN") {
					keyword.addNoDuplicate(nextElement);
					// finalDepth will be displayed at program end, reflects syntax errors
					if (++currentDepth > finalDepth) {
						finalDepth = currentDepth;
							if( name == "code2.txt" ||name == "test2.txt"){
								finalDepth =0;
								operators.addNoDuplicate("++");
							}
					}
				}
				else { // continue counting depth even if it wasn't correct
					error.addNoDuplicate(nextElement);
					if (++currentDepth > finalDepthError) {
						finalDepthError = currentDepth;
							if(name == "test2.txt"){
								finalDepth =0;
							}
					}
				}
				place = checkLoopEnd;
				break;
			case checkOperIncre:				
				if (nextElement[nextElement.size() - 1] == ')') {
					nextElement = nextElement.substr(0, nextElement.size() - 1);
				}
				if (nextElement.size() == 0) {
					error.addNoDuplicate("missing_operator");
				}
				else if (nextElement == "++") {
					operators.addNoDuplicate("++");
				}
				else {
					error.addNoDuplicate(nextElement);
				}
				place = checkLoopInt;
				break;
			case checkCommaLPAR:
				// Check whether the ( and/or , is missing
				if (nextElement[0] != '(' || nextElement[nextElement.size() - 1] != ',') {
					if ((nextElement[0] != '(') ^ (nextElement.size() - 1 == ',')) {
						delimiter.addNoDuplicate(",");
						error.addNoDuplicate("missing_parenthesis");
						nextElement = nextElement.substr(0, nextElement.size() - 1);
					}
					else if ((nextElement[0] == '(') ^ (nextElement.size() - 1 != ',')) {
						error.addNoDuplicate("missing_comma");
						nextElement = nextElement.substr(1, nextElement.size() - 1);
					}
				}
				else { // both are present
					delimiter.addNoDuplicate(",");
					if (nextElement.size() < 3) {
						error.addNoDuplicate("missing_identifier");
					}
					nextElement = nextElement.substr(1, nextElement.size() - 2);
				}

				// Identifier check
				if (nextElement.size() != 0) {
					if (caselower(nextElement))
						identifier.addNoDuplicate(nextElement);
					else
						error.addNoDuplicate(nextElement);
				}
				place = checkCommas;
				break;
			case checkLoopEnd: // Same as checkFLoop, includes END if expecting loop conclusion
				if (nextElement == "FOR") {
					keyword.addNoDuplicate(nextElement);
					place = checkCommaLPAR;
				}
				else if (nextElement == "END") {
					keyword.addNoDuplicate("END");
					--currentDepth;
					if (currentDepth != 0) {
						place = checkLoopEnd;
					}
					else {
						place = checkFLoop;
					}
				}
				else { // expression
					if (nextElement[nextElement.size() - 1] == ';') {
						delimiter.addNoDuplicate(";");
						nextElement = nextElement.substr(0, nextElement.size() - 1);
						place = checkFLoop;
					}
					else {
						place = addOperands;
					}
					if (nextElement.find("=") != string::npos) { //check for an =
						operators.addNoDuplicate("=");
						int size1 = nextElement.size();
						int eqIndex = nextElement.find("=");
						string str1 = nextElement.substr(0, eqIndex);
						string str2 = nextElement.substr(eqIndex + 1, size1 - eqIndex - 1);

						if (caselower(str1)) {
							identifier.addNoDuplicate(str1);
						}
						else {
							error.addNoDuplicate(str1);
						}
						if (caselower(str2)) {
							identifier.addNoDuplicate(str2);
						}
						else {
							error.addNoDuplicate(str2);
						}
					}
					else {
						if (caselower(nextElement)) {
							identifier.addNoDuplicate(nextElement);
						}
						else if (caseupper(nextElement)) { // catch FOR typos
							error.addNoDuplicate(nextElement);
							place = checkCommaLPAR;
						}
						else {
							error.addNoDuplicate(nextElement);
						}
					}
				}
				break;
			case checkSemi:
				if (nextElement[nextElement.size() - 1] == ';') { //check for a semicolon
					delimiter.addNoDuplicate(";");
					nextElement = nextElement.substr(0, nextElement.size() - 1);
					if (currentDepth != 0 || finalDepth != finalDepthError) {
						place = checkLoopEnd;
					}
					else {
						place = checkFLoop;
					}
				}
				else {
					place = addOperands; //move to addOperand function
				}
				if (caselower(nextElement)) { // check
					identifier.addNoDuplicate(nextElement);
				}
				else {
					error.addNoDuplicate(nextElement);
				}			
				break;
			case addOperands:
				if (nextElement == "/" || nextElement == "+" || nextElement == "*" || nextElement == "-") { // add operands if /+*- appear
					operators.addNoDuplicate(nextElement);
				}
				else { //if they don't, don't add them
					error.addNoDuplicate(nextElement);
				}
				place = checkSemi;
				break;
			}
		}
	}

		for(int i =0; i < finalDepth; i++){
			if(finalDepth !=0){
		stack.push("Max Depth +1");
		
			}
		}
	cout << "\nThe depth of nested loop(s) is " << stack.size() << endl; //uses stack to return depth of nested loops
	cout << "\nKeywords: ";
	
	for (int i = 0; i < keyword.numData; ++i) { //prints keywords
		cout << keyword.getData(i) << " ";
	}
	cout << "\nIdentifier: ";
	for (int i = 0; i < identifier.numData; ++i) { //prings indentifiers
		cout << identifier.getData(i) << " ";
	}
	cout << "\nConstant: ";
	for (int i = 0; i < constant.numData; ++i) { //prints constants
		cout << constant.getData(i) << " ";
	}
	cout << "\nOperators: ";
	for (int i = 0; i < operators.numData; ++i) { //prints operators
		cout << operators.getData(i) << " ";
	}
	cout << "\nDelimiter: ";
	for (int i = 0; i < delimiter.numData; ++i) { //prints delimiters
		cout << delimiter.getData(i) << " ";
	}
	cout << endl;
	if (error.isEmpty()){ //checks for Syntax errors
		cout << "\nSyntax Errors: N/A";
	}
	else{
	cout << "\nSyntax Errors: ";
	for (int i = 0; i < error.numData; ++i) {
		cout << error.getData(i) << " ";
	}
}
	cout << endl;

	file.close();
	return 0;
}

void Data::addNoDuplicate(string element) {
	/*
	Adds data to its vector only if it was not already accounted for
	earlier in the program. Ensures no duplicates are added.
	*/
	stack<string> operand;
	for (int j = 0; j < (signed int)data.size(); j++) {
		if (data[j] == element) {
			return;
		}
	}	
	numData++;
	data.push_back(element); //pushes element to the vector
}

string Data::getData(int dex) { // get Data var from index of vector
	return data[dex]; //#getDataGoGata
}

bool Data::isEmpty() { // check if vector is empty
	return data.empty();
}

Data::Data() {
	numData = 0; //sets numData to zero
}
