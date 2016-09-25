#include "geometry.h"

Geometry::Geometry(PolyListPtr polyList){
	this->coordinates = polyList;
}


Geometry::~Geometry()
{
}

Geometry::polyPtr Geometry::parsePolygon(std::vector<json> input){
	Geometry::polyPtr polygon(new Geometry::polygon); // list of polygons (aka a single building entry)
	for (auto currentRing = input.begin(); currentRing != input.end(); ++currentRing) {
		auto pointArray = currentRing->get<std::vector<json>>();
		Geometry::LinearRingPtr points(new Geometry::linearring); // list of points for a polygon
		for (auto currentPoint = pointArray.begin(); currentPoint != pointArray.end(); ++currentPoint) {
			auto coordinatePair = currentPoint->get<std::vector<json>>();
			double latitude = currentPoint->at(0).get<double>();
			double longitude = currentPoint->at(1).get<double>();
			Geometry::PointPtr point(new Geometry::Point()); // lat and longitude struct
			latitude = point->latitude;
			longitude = point->longitude;
			points->push_back(point);
		}
		polygon->push_back(points);
	}
	return polygon;
}


