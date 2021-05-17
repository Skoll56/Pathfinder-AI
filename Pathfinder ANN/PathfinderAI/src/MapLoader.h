#ifndef _MAPLOADER_H_
#define _MAPLOADER_H_
#include <string>
#include <vector>

class Entity;

/** This is the map, represented as an X-Y grid and a list of walls */
struct BattleMap
{
	BattleMap(int _x, int _y)
	{
		m_xSize = _x;
		m_ySize = _y;
	}
	BattleMap() {};	

	int cutString(std::string &_str);
	BattleMap loadFromFile(std::string _path);

	
	int m_xSize, m_ySize;
	std::vector<Entity*> m_walls;
};


#endif