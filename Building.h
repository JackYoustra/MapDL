#pragma once
#include <string>
#include <memory>
#include "geometry.h"
class Building
{
public:
	Building(int id, int osm_id, std::string name, std::string type, Geometry::GeometryPtr geometry);
	~Building();
	bool pointInBuilding(double latitude, double longitude);
	std::string toString();
	typedef std::shared_ptr<Building> BuildingPtr;
private:
	// which ones need to be in shared pointers?
	int id;
	int osm_id;
	std::string name;
	std::string type;
	Geometry::GeometryPtr geometry;
};

