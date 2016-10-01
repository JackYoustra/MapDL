#pragma once
#include <string>
#include <vector>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;

//#include <boost/multiprecision/float128.hpp>
class Geometry
{
public:
	struct Point {
		/* multiprecision has 113 bit mantissa, gives 34 digits, doubles have 53 bit mantissa, which is only able to store 15 digits (52 bits mantissa)
		because the gojson coordinates have 19 digits (Example: -122.417473351053516), we use float128 (although this can be changed in the future depending on necessity with actual measurements).
		However, this can't be used b/c compiler issues (for now) so use 64 bits instead and eat some imprecision, but in the future perhaps compile elsewhere or see what's up with SIMD.
		But, it probably doesn't matter with the actual units unless we need something like millimeter precision. Further analysis needed to find exact error.
		*/
		//boost::multiprecision::float128 latitude, longitude; 
		double latitude, longitude;
	};

	// computing of point inside building
	bool pointInBuilding(double latitude, double longitude);

	typedef std::shared_ptr<Point> PointPtr;
	typedef std::vector<PointPtr> linearring;
	typedef std::shared_ptr<linearring> LinearRingPtr;
	typedef std::vector<LinearRingPtr> polygon;
	typedef std::shared_ptr<polygon> polyPtr;
	typedef std::vector<polyPtr> PolyList;
	typedef std::shared_ptr<PolyList> PolyListPtr;
	typedef std::shared_ptr<Geometry> GeometryPtr;

	Geometry(PolyListPtr);
	~Geometry();

	static Geometry::polyPtr parsePolygon(std::vector<json> input);

	typedef std::shared_ptr<std::vector<PointPtr>> VertexList;

private:
	std::string type;
	PolyListPtr coordinates;
	
	VertexList verticies;
};
