#include "Input.h"
#include "Game.h"
#include "Entity.h"

void Input::update()
{	
	bool quit = false;	
	SDL_Event event = { 0 };
	while (SDL_PollEvent(&event))
	{		
		if (event.type == SDL_QUIT)
		{
			game->m_player->m_ANN->save();
			game->m_npc->m_ANN->save();
			game->m_quit = true;
		}
	}
}
