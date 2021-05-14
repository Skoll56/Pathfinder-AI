#pragma once
#include <string>
class Map;
class Entity;

std::string findPath(Map &_map, Entity* entity);
std::string findPath(Map &_map, Entity* entity, int _x, int _y);

std::string astar(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish);