#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "Sheet.h"
#include <vector>
#include <glm.hpp>
#include <string>
#include "ANN.h"

class Game;

struct Colour
{
	Colour() {};
	Colour(int _r, int _g, int _b, int _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	int r;
	int g;
	int b;
	int a;
};

struct Entity
{
	Entity() {};
	Entity(int _xPos, int _yPos)
	{
		m_Pos.x = _xPos;
		m_Pos.y = _yPos;
		m_col = Colour(150, 150, 150, 255);
	}	
	
	void initialiseActionList();
	void refreshActionList();
	void doRandomAction();
	void doAction(Action _a);
	void disable(CharacterSheet::ActionLength _slot);
	void initialiseANN();
	void update();
	void startTurn();
	void endTurn();
	void takeAOO();
	std::string readUntilVal(std::string & _string, int & _i, char _delim);
	void meleeAttack(int _bonus);
	void rangedAttack(int _bonus);
	int roll(int _dice);
	bool isAdjacent();
	bool hitBoundingBox(float minB[], float maxB[], float origin[], float dir[], float coord[]);
	bool hasStraightLine();
	void adjustPosition(std::string _route);	
	glm::vec2 findLOS();
	bool can5ftBack();

	std::vector<Action> m_actionList;
	glm::vec2 m_LOSsquare;
	bool m_isMyTurn = false;
	glm::vec2 m_Pos;
	glm::vec2 m_fiveFtBackSquare;
	Colour m_col;
	char m_tag;
	bool m_picked = false;
	int m_moveActionsTaken = 0;
	std::string m_chargePath;
	CharacterSheet m_CS;
	Game* m_game;
	Entity* m_opponent;
	Inputs m_inputs;
	NeuralNetwork* m_ANN;
};

struct Map
{
	Map(int _gridX, int _gridY)
	{
		m_gridX = _gridX;
		m_gridY = _gridY;
	}
	Map() {};

	std::vector<Entity*> m_walls;	
	int m_gridX, m_gridY;
	
};

#endif