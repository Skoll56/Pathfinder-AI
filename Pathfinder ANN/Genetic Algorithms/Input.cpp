#include "Input.h"
#include "Game.h"
#include "Entity.h"

void Input::Update()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	glm::vec2 newPos = glm::vec2(x, y);
	mouse.m_dPos = newPos - mouse.m_Pos;
	mouse.m_Pos = newPos;

	SDL_Event event = { 0 };
	bool quit = false;
	

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				mouse.clicking = true;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				mouse.clicking = false;
				if (game->player->picked)
				{
					game->player->picked = false;
					game->player->m_Pos.x = (int)((game->player->m_Pos.x + (game->boxSize /2)) / game->boxSize) * game->boxSize;
					game->player->m_Pos.y = (int)((game->player->m_Pos.y + (game->boxSize /2)) / game->boxSize) * game->boxSize;
				}
			}
		}
		else if (event.type == SDL_QUIT)
		{
			game->quit = true;
		}
	}

	if (mouse.clicking)
	{
		if (mouse.m_Pos.x > game->player->m_Pos.x && mouse.m_Pos.y > game->player->m_Pos.y)
		{
			if (mouse.m_Pos.x < game->player->m_Pos.x + game->boxSize && mouse.m_Pos.y < game->player->m_Pos.y + game->boxSize)
			{
				game->player->picked = true;
			}			
		}		
	}
	if (game->player->picked)
	{
		game->player->m_Pos.x += mouse.m_dPos.x;
		game->player->m_Pos.y += mouse.m_dPos.y;
	}

}
