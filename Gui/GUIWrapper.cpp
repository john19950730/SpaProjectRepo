#include "GUIWrapper.h"

#include <iostream>
#include <vector>

// a default constructor
GUIWrapper::GUIWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void GUIWrapper::parse(std::string filename) {
	// call your parser to do the parsing
	std::cout << "parsed " << filename << std::endl;
  // ...rest of your code...
}
//from code editor
void GUIWrapper::parseFromCode(std::string code) {
	// call your parser to do the parsing
	std::cout << "parsed from code editor " << code;
	// ...rest of your code...
	//std::cout << "line num1 " << code[0];
	int start = 0;
	int lineCount = 0;
	std::vector<std::string> line;
	for (int i = 0; i < code.length(); i++) {
		if (code[i] == '\n') {
			int length = i + 1;
			std::string subString = code.substr(start, length-start);
			line.push_back(subString);
			std::cout << lineCount+1 << " line is: " << line.at(lineCount);
			lineCount++;
			start = length;
		}
	}
}

// method to evaluating a query
void GUIWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

	std::cout << "query=  " << query << std::endl;
	results.push_back(query + "\nQuery result: hello ...");
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
