#ifndef _INPUT_H_
#define _INPUT_H_

#include <glm/glm.hpp>
#include <SDL2\SDL.h>
struct Game;

/**Very basic SDL input module. Only used to check for QUIT events. */
struct Input
{
	Input() {};	
	Game* game;
	void update();
};

#endif
