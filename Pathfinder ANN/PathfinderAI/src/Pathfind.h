#ifndef _PATHFIND_H_
#define _PATHFIND_H_

#include <string>
class BattleMap;
class Entity;

/**IMPORTANT: The Pathfinding in this project has NOT been uniquely created for this project, it should be treated as a 3rd party library. It was originally provided by Dr Prakoonwit, 2018, and has been used in previous work. It is NOT being submitted as new work to be marked.*/

	/** \brief Finds a path to the entity's opponent */
	std::string findPath(BattleMap &_map, Entity* entity);

	/** \brief Finds a path to a specific square*/
	std::string findPath(BattleMap &_map, Entity* entity, int _x, int _y);

	/** \brief The actual A* algorithm. Provided by Dr Prakoonwit, 2018, who adapted it from http://en.wikipedia.org/wiki/A* */
	std::string astar(const int & xStart, const int & yStart,
		const int & xFinish, const int & yFinish);
#endif