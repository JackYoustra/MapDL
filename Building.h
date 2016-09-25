#pragma once
#include <string>
#include <memory>
#include "geometry.h"
class Building
{
public:
	Building(int id, int osm_id, std::string name, std::string type, Geometry::GeometryPtr geometry);
	~Building();
	typedef std::shared_ptr<Building> BuildingPtr;
private:
	// which ones need to be in shared pointers?
	int id;
	int osm_id;
	std::string name;
	std::string type;
	Geometry::GeometryPtr geometry;
};

