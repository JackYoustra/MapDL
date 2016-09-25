#include "MapTile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include "json.hpp"

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
	fileJSON
}

MapTile::~MapTile()
{
}


int main(int argc, char** argv) {
	MapTile("san-francisco_california.imposm-geojson\\san-francisco_california_buildings.geojson");
}