#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "Sheet.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "ANN.h"

class Game;

/** Just holds RGBA*/
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

/**An entity is any icon on the map, including the walls and the characters.*/
struct Entity
{
	
	Entity(int _x, int _y)
	{
		m_col = Colour(150, 150, 150, 255); //Grey
		m_pos.x = _x;
		m_pos.y = _y;		
	}	
	Entity() {};

	/** \brief Initialises the action list with the appropriate values*/
	void initialiseActionList();

	/** \brief Refreshes the action list*/
	void refreshActionList();

	/** \brief Makes the character take a totally random action*/
	void doRandomAction();

	/** \brief Makes the character take a specific action*/
	void doAction(Action _a);

	/** \brief Disables an action slot in the action list*/
	void disable(CharacterSheet::ActionLength _slot);

	/** \brief Sets up the character's ANN*/
	void initialiseANN();

	/** \brief Happens once each turn. Re-establishes the inputs and gets the character to decide its turn*/
	void update();

	/** \brief Marks that this character's turn has started*/
	void startTurn();

	/** \brief Marks that this character's turn ended*/
	void endTurn();

	/** \brief Causes the character to make an Attack of Opportunity against its opponent */
	void takeAOO();

	/** \brief Used in converting player console input into recognised commands. Reads an input until it finds a delim value. */
	std::string readUntilVal(std::string & _string, int & _i, char _delim);

	/** \brief Make a melee attack */
	void meleeAttack(int _bonus);

	/** \brief Make a ranged attack*/
	void rangedAttack(int _bonus);

	/** \brief Generates a number between 1 and the _dice value (simulates dice roll)*/
	int roll(int _dice);

	/** \brief Checks if the character is adjacent to its enemy*/
	bool isAdjacent();

	/** \brief A Ray-Box intersect test taken from Andrew Woo, "Graphics Gems", Academic Press, 1990. It is not being submitted as original work to be marked.*/
	bool hitBoundingBox(float minB[], float maxB[], float origin[], float dir[], float coord[]);

	/** \brief Checks to see if a character has Line of Sight to its opponent.*/
	bool hasStraightLine();

	/** \brief Saves the movement path if a valid charge route it sound*/
	std::string m_chargePath;

	/** \brief Move from one position to another, following a route (represented by an array of directions in string form)*/
	void move(std::string _route);	

	/** \brief Tries to find a square within move distance that has LOS to its opponent*/
	glm::vec2 findLOS();
	glm::vec2 m_LOSsquare;

	/** \brief Checks to see if there is a square it can step to which would be outside of melee range*/
	bool can5ftBack();
	glm::vec2 m_fiveFtBackSquare;

	/** \brief An array of Actions. Every frame, the legality of the list is updated and each action taken is tracked.*/
	std::vector<Action> m_actionList;

	/** \brief Tracks if it is this character's turn or not*/
	bool m_isMyTurn = false;	

	/** \brief This is either 'A' or 'B'. Just makes it possible to tell the characters apart.*/
	char m_tag;
	int m_moveActionsTaken = 0;
	
	/** \brief The character's stat sheet*/
	CharacterSheet m_CS;	

	/** \brief A reference to the character's opponent*/
	Entity* m_opponent;

	/** \brief The input values that are updated and fed to the ANN when deciding how to take a turn*/
	Inputs m_inputs;

	/** \brief This character's ANN*/
	NeuralNetwork* m_ANN;

	glm::vec2 m_pos;
	Colour m_col;
	Game* m_game;
};



#endif