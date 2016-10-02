#pragma once
#include <string>
#include <memory>
#include "Building.h"
class MapSectorData{
public:
	MapSectorData(std::string jsonPath);
	~MapSectorData();

private:
	typedef std::vector<Building::BuildingPtr> BuildingList;
	typedef std::shared_ptr<std::vector<Building::BuildingPtr>> BuildingListPtr;
public:
	BuildingListPtr buildings;

public:
	BuildingListPtr buildingsInCoordinates(double latitude, double longitude);
};

