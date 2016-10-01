#include"geometry.h"

Geometry::Geometry(PolyListPtr polyList){
	this->coordinates = polyList;
	this->verticies = std::make_shared<std::vector<PointPtr>>();
	for (auto currentPoly = this->coordinates->begin(); currentPoly != this->coordinates->end(); ++currentPoly) {
		polyPtr ptr = *currentPoly;
		for (auto currentRing = ptr->begin(); currentRing != ptr->end(); ++currentRing) {
			LinearRingPtr lineptr = *currentRing;
			for (auto currentPoint = lineptr->begin(); currentPoint != lineptr->end(); ++currentPoint) {
				PointPtr point = *currentPoint;
				verticies->push_back(point);
			}
		}
	}
}


Geometry::~Geometry()
{
}

// https://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
bool Geometry::pointInBuilding(double latitude, double longitude) {
	const int nvert = verticies->size();
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		auto currentPoint = this->verticies->at(i); //x
		const double pointLatitude = currentPoint->latitude;
		const double pointLongitude = currentPoint->longitude;
		auto lastPoint = this->verticies->at(j);
		const double lastLatitude = lastPoint->latitude;
		const double lastLongitude = lastPoint->longitude;
		if (((pointLongitude>longitude) != (lastLongitude>longitude)) &&
			(latitude < (lastLatitude - pointLatitude) * (longitude - pointLatitude) / (lastLongitude - pointLongitude) + pointLatitude))
			c = !c;
	}
	if (c % 2 == 1) return true;
	return false;
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
			point->latitude = latitude;
			point->longitude = longitude;
			points->push_back(point);
		}
		polygon->push_back(points);
	}
	return polygon;
}


