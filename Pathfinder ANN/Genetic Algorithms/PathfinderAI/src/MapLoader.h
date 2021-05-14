#ifndef _MAPLOADER_H_
#define _MAPLOADER_H_
#include <string>

class Map;

Map readFile(std::string _location);

int cutSpace(std::string &_str);

#endif