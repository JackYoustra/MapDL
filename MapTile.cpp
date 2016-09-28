#include "MapTile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <vector>
#include "json.hpp"
#include "geometry.h"

using json = nlohmann::json;


// http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
std::string get_file_contents(const char *filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

MapTile::MapTile(std::string jsonPath) {
	std::string rawFileContents = get_file_contents(jsonPath.c_str());
	json fileJSON = json::parse(rawFileContents.c_str());
	json featuresJSON = fileJSON["features"];
	auto featuresList = featuresJSON.get<std::vector<json>>();
	BuildingListPtr buildingList(new BuildingList);
	for (auto it = featuresList.begin(); it != featuresList.end(); ++it){
		json pList = *it;

		json properties = pList["properties"];
		int id = static_cast<int>(properties["id"].get<float>()); // returns a float, get the int from it
		int osm_id = static_cast<int>(properties["osm_id"].get<float>());
		std::string name = ""; // null string if no name
		if (!properties["name"].is_null()) {
			name = properties["name"].get<std::string>();
		}

		json geometryJSON = pList["geometry"];
		std::string type = geometryJSON["type"].get<std::string>();
		Geometry::PolyListPtr polyLists(new Geometry::PolyList);
		if (type == "Polygon") {
			auto linearringarray = geometryJSON["coordinates"].get<std::vector<json>>();
			polyLists->push_back(Geometry::parsePolygon(linearringarray));
		}
		else if(type == "MultiPolygon") {
			// need to go through each polygon
			auto polyarray = geometryJSON["coordinates"].get<std::vector<json>>();
			for (auto currentPoly = polyarray.begin(); currentPoly != polyarray.end(); ++currentPoly) {
				auto linearringarray = currentPoly->get<std::vector<json>>();
				polyLists->push_back(Geometry::parsePolygon(linearringarray));
			}
		}
		else {
			throw("PARSE CASE NOT HANDLED");
		}
		Geometry::GeometryPtr geometry(new Geometry(polyLists));
		Building::BuildingPtr building(new Building(id, osm_id, name, type, geometry));
		buildingList->push_back(building);
	}
	this->buildings = buildingList;
}

MapTile::~MapTile()
{
}

MapTile::BuildingListPtr MapTile::buildingsInCoordinates(double latitude, double longitude){

	return BuildingListPtr();
}

//https://mapzen.com/data/metro-extracts/metro/san-francisco_california/
int main(int argc, char** argv) {
	MapTile* tile = new MapTile("san-francisco_california.imposm-geojson\\san-francisco_california_buildings.geojson");


	//MapTile("sf_buildings_sample.geojson");
}