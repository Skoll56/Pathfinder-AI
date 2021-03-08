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
	glm::vec2 m_Pos;

	glm::vec2 fiveFtBackSquare;
	Colour m_col;

	char tag;
	bool picked = false;
	std::vector<Action> m_actionList;
	void initialiseActionList();
	void refreshActionList();
	void DoRandomAction();
	void DoAction(Action _a);
	void Disable(CharacterSheet::ActionLength _slot);
	void InitialiseANN();
	void Update();
	void StartTurn();
	void EndTurn();
	void TakeAOO();
	void MeleeAttack(int _bonus);
	void RangedAttack(int _bonus);
	int Roll(int _dice);
	bool isAdjacent();
	bool HitBoundingBox(float minB[], float maxB[], float origin[], float dir[], float coord[]);
	bool HasStraightLine();
	void AdjustPosition(std::string _route);
	bool isMyTurn = false;
	glm::vec2 LOSsquare;
	glm::vec2 findLOS();
	bool can5ftBack();

	int MoveActionsTaken = 0;
	std::string chargePath;
	CharacterSheet CS;
	Game* game;
	Entity* opponent;
	Inputs inputs;
	NeuralNetwork* ANN;
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