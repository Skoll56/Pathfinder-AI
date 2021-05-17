/**IMPORTANT: The Pathfinding in this project has NOT been uniquely created for this project, it should be treated as a 3rd party library. 
It was originally provided by Dr Prakoonwit, 2018, and has been used in previous work. It is NOT being submitted as new work to be marked.*/

// Astar.cpp
// http://en.wikipedia.org/wiki/A*
// Compiler: Dev-C++ 4.9.9.2
// FB - 201012256
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "Entity.h"
#include "Game.h"
#include "MapLoader.h"

using namespace std;
int n;  // horizontal size of the map
int m; // vertical size size of the map

static std::vector<std::vector<int>> map;
static std::vector<std::vector<int>> closed_nodes_map;
static std::vector<std::vector<int>> open_nodes_map;
static std::vector<std::vector<int>> dir_map;
//static int dir_map[n][m]; // map of directions

const int dir = 8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

class node
{
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority

public:
	node() {
		xPos = yPos = level = priority = -1;
	}
	node(int xp, int yp, int d, int p)
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int & xDest, const int & yDest)
	{
		priority = level + estimate(xDest, yDest) * 10; //A*
	}

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i) // i: direction
	{
		level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	}

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Euclidian Distance
		d = static_cast<int>(sqrt(xd*xd + yd * yd));

		// Manhattan distance
		//d=abs(xd)+abs(yd);

		// Chebyshev distance
		//d=max(abs(xd), abs(yd));

		return(d);
	}
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string astar(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish)
{
	priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	int pqi; // pq index
	node n0;
	node m0;
	int i, j, x, y, xdx, ydy;
	char c;
	pqi = 0;
	closed_nodes_map.clear();
	open_nodes_map.clear();
	dir_map.clear();

	// reset the node maps
	for (x = 0; x < n; x++)
	{
		std::vector<int> t;
		closed_nodes_map.push_back(t);
		open_nodes_map.push_back(t);
		dir_map.push_back(t);
		for (y = 0; y < m; y++)
		{
			dir_map[x].push_back(0);
			closed_nodes_map[x].push_back(0);
			open_nodes_map[x].push_back(0);
		}
	}

	// create the start node and push into list of open nodes
	n0 = node(xStart, yStart, 0, 0);
	n0.updatePriority(xFinish, yFinish);
	pq[pqi].push(n0);
	open_nodes_map[xStart][yStart] = n0.getPriority(); // mark it on the open nodes map

	// A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0.getxPos(); y = n0.getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i < dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = node(xdx, ydy, n0.getLevel(),
					n0.getPriority());
				m0.nextLevel(i);
				m0.updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0.getPriority();
					pq[pqi].push(m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy] > m0.getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0.getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

					// empty the larger size pq to the smaller one
					if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(m0); // add the better node instead
				}
			}
		}
	}

	return ""; // no route found
}

string findPath(BattleMap &_map, Entity* entity)
{	
	n = _map.m_xSize;
	m = _map.m_ySize;

	map.clear();
	// create empty map
	for (int x = 0; x < n; x++)
	{
		std::vector<int> t;
		map.push_back(t);
		for (int y = 0; y < m; y++)
		{
			map[x].push_back(0);
		}
	}
	// Fill the map matrix with 1's (empty space)
	for (int i = 0; i < _map.m_block.size(); i++)
	{
		map[_map.m_block[i]->m_pos.x][_map.m_block[i]->m_pos.y] = 1;
	}	

	int xA, yA, xB, yB;
	xA = entity->m_pos.x / entity->m_game->m_boxSize;
	yA = entity->m_pos.y / entity->m_game->m_boxSize;
	xB = entity->m_opponent->m_pos.x / entity->m_game->m_boxSize;
	yB = entity->m_opponent->m_pos.y / entity->m_game->m_boxSize;
	string route = "";	

	route = astar(xA, yA, xB, yB);
	if (route.length() > 0)
	{
		route.pop_back();
	}	

	// Convert the directions into a useful format
	if (route.length() > 0)
	{		
		for (int i = 0; i < route.length(); i++)
		{
			switch (route[i]) // Convert the A* direction into my directions
			{
				case '0': route[i] = '2'; break;
				case '1': route[i] = '7'; break;
				case '2': route[i] = '4'; break;
				case '3': route[i] = '6'; break;
				case '4': route[i] = '1'; break;
				case '5': route[i] = '5'; break;
				case '6': route[i] = '3'; break;
				case '7': route[i] = '8'; break;
			}
		}
	}
	return route;
}


string findPath(BattleMap &_map, Entity* entity, int _x, int _y)
{
	n = _map.m_xSize;
	m = _map.m_ySize;

	map.clear();
	// create empty map
	for (int x = 0; x < n; x++)
	{
		std::vector<int> t;
		map.push_back(t);
		for (int y = 0; y < m; y++)
		{
			map[x].push_back(0);
		}
	}
	// fillout the map matrix with a '+' pattern
	for (int i = 0; i < _map.m_block.size(); i++)
	{
		map[_map.m_block[i]->m_pos.x][_map.m_block[i]->m_pos.y] = 1;
	}

	int xA, yA, xB, yB;
	xA = entity->m_pos.x / entity->m_game->m_boxSize;
	yA = entity->m_pos.y / entity->m_game->m_boxSize;
	xB = _x;
	yB = _y;


	string route = astar(xA, yA, xB, yB);
	

	// Convert the directions into a useful format
	if (route.length() > 0)
	{
		for (int i = 0; i < route.length(); i++)
		{
			switch (route[i]) // Convert the A* direction into my directions
			{
			case '0': route[i] = '2'; break;
			case '1': route[i] = '7'; break;
			case '2': route[i] = '4'; break;
			case '3': route[i] = '6'; break;
			case '4': route[i] = '1'; break;
			case '5': route[i] = '5'; break;
			case '6': route[i] = '3'; break;
			case '7': route[i] = '8'; break;
			}
		}
	}
	return route;
}