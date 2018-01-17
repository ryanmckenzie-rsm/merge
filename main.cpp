#include "Source/PlanetPopulationCapacityGroupDefinition.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>


bool openFile(std::string, std::stack<char>&);


void findPlanetPopulationCapacityGroupIndexes(std::vector<int>&, std::vector<std::string>&);


int main()
{
	std::stack<char> vanilla;
	if (!openFile("Test/Vanilla.xml", vanilla)) {
		return -1;
	}
	
	#if 0
	std::stringstream modded;
	if (!openFile("E:\Tools\Merge\Mod.xml", modded)) {
		return -1;
	}
	#endif
	
	std::vector<int> indexes;
	findPlanetPopulationCapacityGroupIndexes(indexes, vanilla);
	for (int i = 0; i < indexes.size(); ++i) {
		std::cout << indexes[i] <<std::endl;
	}
	
	return 0;
}


bool openfile(std::string fileName, std::stack<char>& s)
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
	
	return successl
}


#if 0
bool openFile(std::string fileName, std::vector<std::string>& v)
{
	bool success = false;
	
	std::ifstream inputFile;
	inputFile.open(fileName.c_str());
	
	if (inputFile.is_open()) {
		std::string line;
		while (std::getline(inputFile, line)) {
			if (v.empty()) {
				v.resize(v.size() * 2);
			}
			v.push_back(line);
		}
		v.shrink_to_fit();
		success = true;
	} else {
		success = false;
	}
	
	return success;
}
#endif


void findPlanetPopulationCapacityGroupIndexes(std::vector<int>& indexes, std::vector<std::string>& v)
{
	PlanetPopulationCapacityGroupDefinition obj;
	for (int i = 0; i < v.size(); ++i) {
		if (obj.checkIfUnique(v[i])) {
			indexes.push_back(i + 1);
		}
	}
}


void scrubComments(std::stack<char>& s)
{
	//invert stack
	std::stack<char> invertedStack;
	while (!s.empty()) {
		invertedStack.push(s.pop());
	}
	
	//scrub comments
	//<!-- ... -->
	char dummy;
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	bool flag4 = false;
	bool commentBegin = false;
	while (!invertedStack.empty()) {
		dummy = invertedStack.pop();
		
		switch (dummy) {
		case '<':
			flag1 = true;
			break;
		case '!':
			flag2 = true;
			break;
		case '-':
			if (flag3) {
				flag4 = true;
			} else {
				flag3 = true;
			}
			break;
		default:
			flag1 = false;
			flag2 = false;
			flag3 = false;
			flag4 = false;
		}
		
		if (flag1 && flag2 && flag3 && flag4) {
			commentBegin = true;
			flag1 = false;
			flag2 = false;
			flag3 = false;
			flag4 = false;
		}
		
		if (commentBegin
		
}