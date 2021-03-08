#ifndef _INPUT_H_
#define _INPUT_H_

#include <glm.hpp>
#include <SDL2\SDL.h>
struct Game;

struct Mouse
{
	glm::vec2 m_Pos;	
	glm::vec2 m_dPos;

	bool clicking = false;
};

struct Input
{
	Input() {};
	Mouse mouse;
	Game* game;

	void Update();
};

#endif
