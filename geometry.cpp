#include "geometry.h"

Geometry::Geometry(PolyListPtr polyList){
	this->coordinates = polyList;
	this->numberOfVerticies = 0;
	for (auto currentPoly = this->coordinates->begin(); currentPoly != this->coordinates->end(); ++currentPoly) {
		polyPtr ptr = *currentPoly;
		for (auto currentRing = ptr->begin(); currentRing != ptr->end(); ++currentRing) {
			LinearRingPtr lineptr = *currentRing;
			for (auto currentPoint = lineptr->begin(); currentPoint != lineptr->end(); ++currentPoint) {
				//PointPtr pointptr = *currentPoint;
				this->numberOfVerticies++;
			}
		}
	}
}


Geometry::~Geometry()
{
}

bool Geometry::pointInBuilding(double latitude, double longitude) {
	bool c = false;
	int i = 0;
	int j = numberOfVerticies - 1;
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


