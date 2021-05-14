#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <vector>
#include "Entity.h"
#include "Input.h"
#include "Sheet.h"
#include "ANN.h"
#include "Console.h"

struct Game
{	
	Game(int _layers, int _nodes);
	void displayStats();
	void displayCommands();
	void displayInfo();
	void initialiseEntities();
	SDL_Window* initWindow();
	SDL_Renderer* initRenderer(SDL_Window* _window);
	void drawWalls(SDL_Renderer* _renderer, std::vector<Entity*> _wall);
	void drawGrid(SDL_Renderer* _renderer, int _x, int _y);
	void drawGridSquare(SDL_Renderer* _renderer, Entity _entity, bool _fill);
	void drawPlayerSquare(SDL_Renderer* _renderer, Entity* _entity, bool _fill);
	void move(Entity* e, glm::vec2 _pos);
	void start();
	void drawScene();

	bool m_playerTesting = false;
	float m_boxSize = 40.0f;
	Input m_input;
	SDL_Window *m_window; 
	SDL_Renderer* m_renderer;
	Map m_map; 	
	Entity* m_player;
	Entity* m_npc;
	Console m_console;
	int m_layers;
	int m_nodes;
	bool m_victory; 
	bool m_quit; 
};

#endif 