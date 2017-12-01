#include "Source/PlanetPopulationCapacityGroupDefinition.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


bool openFile(std::string, std::vector<std::string>&);


void findPlanetPopulationCapacityGroupIndexes(std::vector<int>&, std::vector<std::string>&);


int main()
{
	std::vector<std::string> vanilla;
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


void findPlanetPopulationCapacityGroupIndexes(std::vector<int>& indexes, std::vector<std::string>& v)
{
	PlanetPopulationCapacityGroupDefinition obj;
	for (int i = 0; i < v.size(); ++i) {
		if (obj.checkIfUnique(v[i])) {
			indexes.push_back(i + 1);
		}
	}
}