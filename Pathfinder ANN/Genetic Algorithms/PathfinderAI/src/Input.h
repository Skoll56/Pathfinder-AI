#ifndef _INPUT_H_
#define _INPUT_H_

#include <glm/glm.hpp>
#include <SDL2\SDL.h>
struct Game;


struct Input
{
	Input() {};	
	Game* game;
	void update();
};

#endif
