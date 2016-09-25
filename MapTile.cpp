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
		auto polygonArray = geometryJSON["coordinates"].get<std::vector<json>>();
		Geometry::PolyListPtr polygons(new Geometry::PolyList); // list of polygons (aka a single building entry)
		for (auto currentPoly = polygonArray.begin(); currentPoly != polygonArray.end(); ++currentPoly) {
			auto pointArray = currentPoly->get<std::vector<json>>();
			Geometry::PolygonPtr points(new Geometry::polygon); // list of points for a polygon
			for (auto currentPoint = pointArray.begin(); currentPoint != pointArray.end(); ++currentPoint) {
				auto coordinatePair = currentPoint->get<std::vector<json>>();
				double latitude = currentPoint->at(0).get<double>();
				double longitude = currentPoint->at(1).get<double>();
				Geometry::PointPtr point(new Geometry::Point()); // lat and longitude struct
				latitude = point->latitude;
				longitude = point->longitude;
				points->push_back(point);
			}
			polygons->push_back(points);
		}
		Geometry::GeometryPtr geometry(new Geometry(polygons));
		Building::BuildingPtr building(new Building(id, osm_id, name, type, geometry));
		buildingList->push_back(building);
	}
	this->buildings = buildingList;
}

MapTile::~MapTile()
{
}


int main(int argc, char** argv) {
	//MapTile("san-francisco_california.imposm-geojson\\san-francisco_california_buildings.geojson");
	MapTile("sf_buildings_sample.geojson");
}