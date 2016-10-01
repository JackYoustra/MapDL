#pragma once
#include <string>
#include <memory>
#include "Building.h"
class MapTile{
public:
	MapTile(std::string jsonPath);
	~MapTile();

private:
	typedef std::vector<Building::BuildingPtr> BuildingList;
	typedef std::shared_ptr<std::vector<Building::BuildingPtr>> BuildingListPtr;
public:
	BuildingListPtr buildings;

public:
	BuildingListPtr buildingsInCoordinates(double latitude, double longitude);
};

