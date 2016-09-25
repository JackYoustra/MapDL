#include "geometry.h"



Geometry::Geometry(PolyListPtr polyList){
	this->coordinates = polyList;
}


Geometry::~Geometry()
{
}

polygon Geometry::parsePolygon(json input){
	return polygon();
}


