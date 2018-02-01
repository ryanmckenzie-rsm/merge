#ifndef PLANET_POPULATION_CAPACITY_GROUP_DEFINITION_H
#define PLANET_POPULATION_CAPACITY_GROUP_DEFINITION_H


#include <string>


class PlanetPopulationCapacityGroupDefinition {
	public:
		PlanetPopulationCapacityGroupDefinition();
		~PlanetPopulationCapacityGroupDefinition();
		
		bool checkIfUnique(std::string);
		// Pass a line extracted directly from PlanetPopulationCapacityGroupDefinition.xml ONLY
		// Checks if the given string contains an entity definition that must be merged, returns true if so
		int findPopulationCapacityGroupRank(std::string);
		// Returns the rank for the given PopulationCapacityGroup string, will return -1 if no rank is found
	private:
		void scrubPayLoad(std::string&);
		
		int _uniqueEntitySize;
		std::string* _pUniqueEntity;
		
		int _populationCapacityGroupRanksSize;
		int* _pPopulationCapacityGroupRanks;
};


#endif