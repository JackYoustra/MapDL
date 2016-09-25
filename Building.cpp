#include "Building.h"

Building::Building(int id, int osm_id, std::string name, std::string type, Geometry::GeometryPtr geometry){
	this->id = id;
	this->osm_id = osm_id;
	this->name = name;
	this->type = type;
	this->geometry = geometry;
}

Building::~Building()
{
}
