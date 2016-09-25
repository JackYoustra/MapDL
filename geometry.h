#pragma once
#include <string>
//#include <boost/multiprecision/float128.hpp>
class Geometry
{
public:
	Geometry();
	~Geometry();
private:
	std::string type;
	
	struct Point {
		/* multiprecision has 113 bit mantissa, gives 34 digits, doubles have 53 bit mantissa, which is only able to store 15 digits (52 bits mantissa)
			because the gojson coordinates have 19 digits (Example: -122.417473351053516), we use float128 (although this can be changed in the future depending on necessity with actual measurements).
			However, this can't be used b/c compiler issues (for now) so use 64 bits instead and eat some imprecision, but in the future perhaps compile elsewhere or see what's up with SIMD.
			But, it probably doesn't matter
		*/
		//boost::multiprecision::float128 latitude, longitude; 
		long double latitude, longitude;
	};
};
