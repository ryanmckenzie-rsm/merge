#include "../include/PlanetPopulationCapacityGroupDefinition.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>


bool openFile(std::string fileName, std::stack<char>& s);
// Reads contents of the file from destination "fileName" into character stack "s".


void findPlanetPopulationCapacityGroupIndexes(std::vector<int>& indexes, std::vector<std::string>& v);


void scrubComments(std::stack<char>& s);
// Removes xml comments (<!-- ... -->) from the character stack "s". Supports multi-line comments.
// Beginning of file MUST be on top of stack, call invertStack() if it is not.


void invertStack(std::stack<char>& s);
// Inverts the given character stack "s".


void convertStackToVector(std::stack<char>& source, std::vector<std::string>& target);
// Coverts the given character stack to a vector of strings. Delimits based on the endline character.
// Beginning of file MUST be on top of stack, call invertStack() if it is not.


void printVector(std::vector<std::string> v);
// Prints the given string vector "v" to the console.


void printStack(std::stack<char> s);
// Prints the given character stack "s" to the console.


int main()
{
	std::stack<char> vanillaStack;
	if (!openFile("../testsuite/Vanilla.xml", vanillaStack)) {
		return -1;
	}
	
	//
	invertStack(vanillaStack);
	std::vector <std::string> rawVector;
	convertStackToVector(vanillaStack, rawVector);
	printVector(rawVector);
	//
	
	#if 0
	invertStack(vanillaStack);
	scrubComments(vanillaStack);
	
	std::vector<std::string> vanillaVector;
	convertStackToVector(vanillaStack, vanillaVector);
	
	printVector(vanillaVector);
	#endif
	
	return 0;
}


bool openFile(std::string fileName, std::stack<char>& s)
{
	bool success = false;
	
	std::ifstream inputFile;
	inputFile.open(fileName.c_str());
	
	if (inputFile.is_open()) {
		char dummy;
		while (inputFile.get(dummy)) {
			s.push(dummy);
		}
		success = true;
	} else {
		success = false;
	}
	inputFile.close();
	
	return success;
}


void findPlanetPopulationCapacityGroupIndexes(std::vector<int>& indexes, std::vector<std::string>& v)
{
	PlanetPopulationCapacityGroupDefinition obj;
	int size = v.size();
	for (int i = 0; i < size; ++i) {
		if (obj.checkIfUnique(v[i])) {
			indexes.push_back(i + 1);
		}
	}
}


void scrubComments(std::stack<char>& s)
{
	// <!-- ... -->
	char dummy;
	bool commentBegin = false;  // signals the beginning of a comment has been found
	unsigned int count = 0;  // counts the characters between, and including, the comment markers
	unsigned int pos = 3;  // indicates the position in the buffer to insert the new character
	std::stack<char> tempStack;
	std::string buffer = "    ";
	// The buffer is used to focus in on the stack 3/4 characters at a time, so that we can easily identify the beginning
	// and end of a comment. Given the following character stack:
	// TOP{L, o, r, e, m,  , i, p, s, u, m,  , d, o, l, o, r,  , s, i, t,  , a, m, e, t}BOTTOM
	// and the following code, the buffer will progress as such:
	// (   L)
	// (  Lo)
	 // ( Lor)
	 // (Lore)
	 // (orem)
	 // (rem )
	 // and so forth
	while (!s.empty()) {
		dummy = s.top();
		s.pop();
		tempStack.push(dummy);
		
		std::rotate(buffer.begin(), (buffer.begin() + 1), buffer.end());
		buffer[pos] = dummy;
		if (!commentBegin && "<!--" == buffer) {
			commentBegin = true;
			buffer.resize(3);
			pos = 2;
			count = 4;
		} else if (commentBegin) {
			// keeps a running count of characters past, and including the comment begin marker, then pushes
			// characters off the stack once it reaches the end comment marker
			++count;
			if ("-->" == buffer) {
				while (count > 0) {
					tempStack.pop();
					--count;
				}
				commentBegin = false;
				buffer.resize(4, ' ');
				pos = 3;
				count = 0;
			}
		}
	}
	
	// once done, stack is inverted, so must be inverted again before s can return
	while (!tempStack.empty()) {
		s.push(tempStack.top());
		tempStack.pop();
	}
}


void invertStack(std::stack<char>& s)
{
	std::stack<char> temp;
	while (!s.empty()) {
		temp.push(s.top());
		s.pop();
	}
	
	s = temp;
}


void convertStackToVector(std::stack<char>& source, std::vector<std::string>& target)
{
	char dummy;
	std::string line = "";
	while (!source.empty()) {
		dummy = source.top();
		source.pop();
		line += dummy;
		
		if ('\n' == dummy) {
			target.push_back(line);
			line = "";
		// EOF doesn't have an end-line, so without this check, the converted vector won't contain the final line.
		} else if (source.empty()) {
			target.push_back(line);
		}
	}
}


void printVector(std::vector<std::string> v)
{
	int size = v.size();
	for (int i = 0; i < size; ++i) {
		std::cout << v[i];
	}
}


void printStack(std::stack<char> s)
{
	int size = s.size();
	for (int i = 0; i < size; ++i) {
		std::cout << s.top();
		s.pop();
	}
}