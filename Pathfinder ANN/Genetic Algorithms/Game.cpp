#include <iostream>
#include <random>
#include <ctime>
#include <glm.hpp>
#include <sstream>
#include "Game.h"
#include "MapLoader.h"
#include "Sheet.h"
#include "Entity.h"


#define WINDOW_WIDTH 980
#define WINDOW_HEIGHT 800
#define RED 255, 0, 0
#define BLUE 0, 0, 255
#define GREEN 0, 255, 0
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0


int main(int argc, char *argv[])
{
	Game game;
	game.start();
	return 0;
}

Game::Game()
{
	srand(time(NULL));
	window = initWindow();
	renderer = initRenderer(window);
	map = readFile("map.txt");	
	player = new Entity(4.0f * boxSize, 1.0f * boxSize);
	npc = new Entity(7.0f * boxSize, 10.0f * boxSize);

	player->game = this;
	player->m_col = Colour(0, 255, 0, 255);
	player->tag = 'A';		
	player->opponent = npc;
	player->initialiseActionList();
	player->InitialiseANN();
	player->ANN->player = true;
	player->CS.weapon = CharacterSheet::Longbow;
	player->CS.HP = 90;
	player->CS.AC = 14;
	player->CS.BAB = 6;
	player->CS.STR = 4;
	player->CS.DEX = 4;
	player->CS.MoveSpeed = 30;
	

	npc->game = this;
	npc->opponent = player;
	npc->m_col = Colour(255, 0, 0, 255);	
	npc->tag = 'B';
	npc->initialiseActionList();
	npc->InitialiseANN();
	npc->CS.weapon = CharacterSheet::Longsword;
	npc->CS.HP = 90;
	npc->CS.AC = 14;
	npc->CS.BAB = 6;
	npc->CS.STR = 4;
	npc->CS.DEX = 4;
	npc->CS.MoveSpeed = 30;

	
	SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	victory = false;
	quit = false;

	input.game = this;
}



void Game::start()
{
	int games = 0;
	while (!quit)
	{		
		while (!victory && !quit)
		{
			if (npc->CS.HP > 0 && player->CS.HP > 0)
			{
				npc->StartTurn();
				npc->Update();
			}

			if (player->CS.HP > 0 && npc->CS.HP > 0)
			{
				player->StartTurn();
				player->Update();
			}


			///Draw Code
			drawScene(); 
			/* Removed for efficiency while training */			
			input.Update();
		}

		victory = false;
		std::string tag = " ";
		if (npc->CS.HP <= 0) { tag[0] = player->tag; }
		else if (player->CS.HP <= 0) { tag[0] = npc->tag; }
		else { tag = "?"; }
		console.Log("--Player " + tag + " Wins--");
		games++;
		if (games == 75)
		{
			console.Save("D:/Users/Skoll/OneDrive - Bournemouth University/Work/Year 3/Final Year Project/ANN Files/");		
			games = 0;
		}
		console.Clear();



		//---Reset---
		player->CS.weapon = CharacterSheet::Longbow;
		player->CS.HP = 60;		
		player->CS.ACbonus = 0;
		player->CS.attackBonus = 0;
		player->CS.AC = 10 + rand() % 11;
		player->CS.DEX = rand() % 7;
		player->CS.STR = rand() % 7;

		npc->CS.weapon = (CharacterSheet::Weapon)(rand() %2);
		npc->CS.HP = 60;		
		npc->CS.ACbonus = 0;
		npc->CS.attackBonus = 0;
		npc->CS.AC = 10 + rand() % 11;
		npc->CS.DEX = rand() % 7;
		npc->CS.STR = rand() % 7;


		glm::vec2* player_pos = &player->m_Pos;
		player_pos->x = 4.0f * boxSize;
		player_pos->y = 1.0f * boxSize;

		glm::vec2* npc_pos = &npc->m_Pos;

		int x;
		int y;
		bool inwall = true;

		while (inwall)
		{
			inwall = false;
			x = rand() % 20;
			y = rand() % 20;
			for (int i = 0; i < map.m_walls.size(); i++)
			{
				if (map.m_walls[i]->m_Pos == glm::vec2(x, y))
				{
					inwall = true;
					break;
				}
			}
			if (x * boxSize == player_pos->x && y * boxSize == player_pos->y)
			{
				inwall = true;
			}
		}

		npc_pos->x = x * boxSize;
		npc_pos->y = y * boxSize;
	}

	system("PAUSE");
}

void Game::drawScene()
{
	SDL_SetRenderDrawColor(renderer, WHITE, 255);
	SDL_RenderClear(renderer);

	//Draw the map
	drawGrid(renderer, map.m_gridX, map.m_gridY);
	drawWalls(renderer, map.m_walls);

	//Draw the player square	
	drawPlayerSquare(renderer, player, true);
	drawPlayerSquare(renderer, npc, true);
	SDL_RenderPresent(renderer);
}




//Initialises the Window
SDL_Window* Game::initWindow() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Pathfinder AI",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (window == nullptr)
	{
		throw std::exception();
	}

	return window;
}
SDL_Renderer* Game::initRenderer(SDL_Window* _window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) { throw std::exception(); }
	return renderer;
}
void Game::drawGrid(SDL_Renderer* _renderer, int _x, int _y)
{	
	Entity t;
	t.m_col = Colour(80, 80, 80, 255);
	
	for (int x = 0; x < _x; x++)
	{
		t.m_Pos.x = x;
		for (int y = 0; y < _y; y++)
		{
			t.m_Pos.y = y;
			drawGridSquare(_renderer, t, false);
		}
	}
}
void Game::drawWalls(SDL_Renderer* _renderer, std::vector<Entity*> _wall)
{
	
	for (int i = 0; i < _wall.size(); i++)
	{
		drawGridSquare(_renderer, *_wall[i], true);
	}
}
void Game::drawGridSquare(SDL_Renderer* _renderer, Entity _entity, bool _fill)
{
	SDL_Rect square;	
	square.x = _entity.m_Pos.x * boxSize;
	square.y = _entity.m_Pos.y * boxSize;
	square.w = boxSize;
	square.h = boxSize;
	SDL_SetRenderDrawColor(_renderer, _entity.m_col.r, _entity.m_col.g, _entity.m_col.b, _entity.m_col.a);
	
	if (_fill)
	{
		SDL_RenderFillRect(_renderer, &square);
	}
	else
	{
		SDL_RenderDrawRect(_renderer, &square);
	}
}
void Game::drawPlayerSquare(SDL_Renderer* _renderer, Entity* _entity, bool _fill)
{
	SDL_Rect square;
	square.x = _entity->m_Pos.x;
	square.y = _entity->m_Pos.y;
	square.w = boxSize;
	square.h = boxSize;
	SDL_SetRenderDrawColor(_renderer, _entity->m_col.r, _entity->m_col.g, _entity->m_col.b, _entity->m_col.a);

	if (_fill)
	{
		SDL_RenderFillRect(_renderer, &square);
	}
	else
	{
		SDL_RenderDrawRect(_renderer, &square);
	}
}
