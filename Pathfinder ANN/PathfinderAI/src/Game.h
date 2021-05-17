#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <vector>
#include "Entity.h"
#include "Input.h"
#include "Sheet.h"
#include "ANN.h"
#include "Console.h"
#include "MapLoader.h"

/**A general manager for the gameflow/scene */
struct Game
{	
	Game();
	void initialise();

	/** \brief Prints the player's character sheet to console during testing*/
	void displayStats();
	/** \brief Prints the valid commands to console during testing*/
	void displayCommands();

	/** \brief Calls both displayStats and displayCommands*/
	void displayInfo();

	/** \brief Initialises both characters*/
	void initialiseEntities();

	SDL_Window* initWindow();
	SDL_Renderer* initRenderer(SDL_Window* _window);

	/** \brief Draws the map and all entities*/
	void drawScene();

	/** \brief Draws all of the walls to the screen*/
	void drawWalls(SDL_Renderer* _renderer, std::vector<Entity*> _wall);

	/** \brief Draws the 2D grid to screen*/
	void drawGrid(SDL_Renderer* _renderer, int _x, int _y);

	/** \brief Draws a single square to the screen*/
	void drawGridSquare(SDL_Renderer* _renderer, Entity _entity, bool _fill);

	/** \brief Draws a character to the screen*/
	void drawPlayerSquare(SDL_Renderer* _renderer, Entity* _entity, bool _fill);

	/** \brief Starts the Game*/
	void start();

	
	/** \brief Marks whether the game should start in training mode or playing mode*/
	bool m_playerTesting = false;

	/** \brief Marks the size of the map grid */
	float m_boxSize = 40.0f;

	/** \brief Reference to the basic SDL input system */
	Input m_input;

	SDL_Window *m_window; 
	SDL_Renderer* m_renderer;

	/** \brief Reference to the map */
	BattleMap m_map; 	

	/** \brief Reference to Player 'A'. In playing mode, this is the real player. In training mode, this is just an NPC */
	Entity* m_player;

	/** \brief Reference to Player 'B'. Always an NPC. */
	Entity* m_npc;

	/** \brief The console which logs all output messages from the game */
	Console m_console;

	/** \brief The number of layers in the current ANN (used when generating a new one from command line args) */	
	int m_layers = 0;

	/** \brief The number of nodes in the current ANN (used when generating a new one from command line args) */
	int m_nodes = 0;

	/** \brief True if one of the characters won the fight*/
	bool m_victory; 

	/** \brief Marks if the user is trying to quit the game */
	bool m_quit; 

	/** \brief Marks if the game should load an ANN or make a new one. Determined by command-line args. */
	bool m_generateNew = false;
};

#endif 