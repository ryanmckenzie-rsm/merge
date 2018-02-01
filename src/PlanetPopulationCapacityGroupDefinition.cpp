#include "../include/PlanetPopulationCapacityGroupDefinition.h"
#include <string>
#include <sstream>


PlanetPopulationCapacityGroupDefinition::PlanetPopulationCapacityGroupDefinition() :
	_pUniqueEntity(0),
	_pPopulationCapacityGroupRanks(0)
{
	_uniqueEntitySize = 1;
	_pUniqueEntity = new std::string[_uniqueEntitySize];
	_pUniqueEntity[0] = "PopulationCapacityGroup";
	
	_populationCapacityGroupRanksSize = 5;
	_pPopulationCapacityGroupRanks = new int[_populationCapacityGroupRanksSize];
	_pPopulationCapacityGroupRanks[0] = 1;
	_pPopulationCapacityGroupRanks[1] = 2;
	_pPopulationCapacityGroupRanks[2] = 3;
	_pPopulationCapacityGroupRanks[3] = 4;
	_pPopulationCapacityGroupRanks[4] = 5;
}


PlanetPopulationCapacityGroupDefinition::~PlanetPopulationCapacityGroupDefinition()
{
	if (_pUniqueEntity) {
		delete [] _pUniqueEntity;
	}
	
	if (_pPopulationCapacityGroupRanks) {
		delete [] _pPopulationCapacityGroupRanks;
	}
}


bool PlanetPopulationCapacityGroupDefinition::checkIfUnique(std::string payLoad)
{
	scrubPayLoad(payLoad);
	
	std::stringstream delimitedPayload(payLoad);
	std::string dummy;
	while (delimitedPayload >> dummy) {
		for (int i = 0; i < _uniqueEntitySize; ++i) {
			if (_pUniqueEntity[i] == dummy) {
				return true;
			}
		}
	}
	
	return false;
}


int PlanetPopulationCapacityGroupDefinition::findPopulationCapacityGroupRank(std::string payLoad)
{
	scrubPayLoad(payLoad);
	
	int rank = -1;
	std::stringstream delimitedPayload(payLoad);
	delimitedPayload >> rank;
	
	return rank;
}


void PlanetPopulationCapacityGroupDefinition::scrubPayLoad(std::string& payLoad)
{
	int pos = 0;
	while ((pos = payLoad.find_first_of('<')) > -1) {
		payLoad.replace(pos, 1, " ");
	}
	while ((pos = payLoad.find_first_of('>')) > -1) {
		payLoad.replace(pos, 1, " ");
	}
	while ((pos = payLoad.find_first_of('=')) > -1) {
		payLoad.replace(pos, 1, " ");
	}
	while ((pos = payLoad.find_first_of('"')) > -1) {
		payLoad.replace(pos, 1, " ");
	}
	while ((pos = payLoad.find_first_of('/')) > -1) {
		payLoad.replace(pos, 1, " ");
	}
}