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
	Game();
	SDL_Window* initWindow();
	SDL_Renderer* initRenderer(SDL_Window* _window);
	void drawWalls(SDL_Renderer* _renderer, std::vector<Entity*> _wall);
	void drawGrid(SDL_Renderer* _renderer, int _x, int _y);
	void drawGridSquare(SDL_Renderer* _renderer, Entity _entity, bool _fill);
	void drawPlayerSquare(SDL_Renderer* _renderer, Entity* _entity, bool _fill);
	void move(Entity* e, glm::vec2 _pos);
	void start();
	void drawScene();
	
	float boxSize = 40.0f;
	Input input;
	SDL_Window *window; 
	SDL_Renderer* renderer;
	Map map; 	
	Entity* player;
	Entity* npc;
	Console console;

	bool victory; 
	bool quit; 
	NeuralNetwork ANN;
	std::vector<std::string> CombatLog;

	std::vector<Action> m_actionList;
};

#endif 