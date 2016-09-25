#pragma once
#include <string>
class Building
{
public:
	Building();
	~Building();
private:
	int id;
	int osm_id;
	std::string name;
	std::string type;
	
};

