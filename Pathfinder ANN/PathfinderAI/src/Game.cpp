#include <iostream>
#include <random>
#include <ctime>
#include <glm/glm.hpp>
#include <sstream>
#include "Game.h"
#include "MapLoader.h"
#include "Sheet.h"
#include "Entity.h"
#include <stdlib.h>
#include <Windows.h>
#include <direct.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define RED 255, 0, 0
#define BLUE 0, 0, 255
#define GREEN 0, 255, 0
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0

#undef main
int main(int argc, char *argv[])
{		
	std::cout << "[LOADING]" << std::endl;
	Game game;
	if (argc > 1)
	{
		game.m_layers = std::atoi(argv[1]);
		game.m_nodes = std::atoi(argv[2]);
		game.m_generateNew = true;
	}
	
	
	game.initialise();
	game.start();
	return 0;
}

void Game::initialiseEntities()
{
	m_player->m_Pos.x = 4.0f * m_boxSize;
	m_player->m_Pos.y = 1.0f * m_boxSize;


	if (!m_playerTesting)
	{
		m_player->m_CS.m_weapon = (CharacterSheet::Weapon)(rand() % 2);
		m_player->m_CS.m_HP = 40;
		m_player->m_CS.m_ACbonus = 0;
		m_player->m_CS.m_attackBonus = 0;
		m_player->m_CS.m_AC = 10 + rand() % 11;
		m_player->m_CS.m_DEX = rand() % 7;
		m_player->m_CS.m_STR = rand() % 7;
		m_player->m_CS.m_BAB = 6;
		m_player->m_CS.m_moveSpeed = 30;
		

		m_npc->m_CS.m_weapon = (CharacterSheet::Weapon)(rand() % 2);
		m_npc->m_CS.m_BAB = 6;
		m_npc->m_CS.m_moveSpeed = 30;
		m_npc->m_CS.m_HP = 40;
		m_npc->m_CS.m_ACbonus = 0;
		m_npc->m_CS.m_attackBonus = 0;
		m_npc->m_CS.m_AC = 10 + rand() % 11;
		m_npc->m_CS.m_DEX = rand() % 7;
		m_npc->m_CS.m_STR = rand() % 7;
	}
	else
	{
		m_player->m_CS.m_weapon = CharacterSheet::Longsword;
		m_player->m_CS.m_HP = 45;
		m_player->m_CS.m_BAB = 6;
		m_player->m_CS.m_moveSpeed = 30;
		m_player->m_CS.m_ACbonus = 0;
		m_player->m_CS.m_attackBonus = 0;
		m_player->m_CS.m_AC = 10 + 8;
		m_player->m_CS.m_DEX = 4;
		m_player->m_CS.m_STR = 4;

		m_npc->m_CS.m_weapon = (CharacterSheet::Weapon)(rand() % 2);
		m_npc->m_CS.m_HP = 45;
		m_npc->m_CS.m_BAB = 6;
		m_npc->m_CS.m_moveSpeed = 30;
		m_npc->m_CS.m_ACbonus = 0;
		m_npc->m_CS.m_attackBonus = 0;
		m_npc->m_CS.m_AC = 10 + 8;
		m_npc->m_CS.m_DEX = 4;
		m_npc->m_CS.m_STR = 4;
	}
}

Game::Game()
{
	
}

void Game::initialise()
{
	srand(time(NULL));
	m_window = initWindow();
	m_renderer = initRenderer(m_window);
	m_map = readFile("map.txt");
	m_player = new Entity(4.0f * m_boxSize, 1.0f * m_boxSize);
	m_npc = new Entity(14.0f * m_boxSize, 14.0f * m_boxSize);

	m_player->m_tag = 'A';
	m_player->m_game = this;
	m_player->initialiseActionList();
	m_player->initialiseANN();
	m_player->m_col = Colour(0, 255, 0, 255);

	m_player->m_opponent = m_npc;
	m_player->m_ANN->m_player = true;

	m_npc->m_tag = 'B';
	m_npc->m_game = this;
	m_npc->initialiseActionList();
	m_npc->initialiseANN();
	m_npc->m_opponent = m_player;
	m_npc->m_col = Colour(255, 0, 0, 255);


	initialiseEntities();


	SDL_RenderSetLogicalSize(m_renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_victory = false;
	m_quit = false;

	m_input.game = this;
	m_player->m_ANN->m_game = this;
	m_npc->m_ANN->m_game = this;
}

void Game::displayStats()
{
	m_console.log("Your Stats:");
	m_console.log("===============================================================================");
	std::string stats = "";
	stats += "HP: " + std::to_string(m_player->m_CS.m_HP) + " | ";
	stats += "AC: " + std::to_string(m_player->m_CS.m_AC) + " | ";
	stats += "STR: " + std::to_string(m_player->m_CS.m_STR) + " | ";
	stats += "DEX: " + std::to_string(m_player->m_CS.m_DEX) + " | ";
	stats += "BAB: " + std::to_string(m_player->m_CS.m_BAB) + " | ";
	stats += "Speed: " + std::to_string(m_player->m_CS.m_moveSpeed) + " | ";
	if (m_player->m_CS.m_weapon == CharacterSheet::Longsword)
	{
		stats += "Weapon: Longsword | ";
	}
	else
	{
		stats += "Weapon: Longbow | ";
	}
	m_console.log(stats);
	m_console.log("===============================================================================\n");
}

void Game::displayCommands()
{
	m_console.log("Command List:");
	m_console.log("===============================================================================");
	std::string commands = "";
	for (int i = 0; i < m_player->m_actionList.size(); i++)
	{
		commands += "!" + m_player->m_actionList[i].m_stringName + " | ";
	}
	m_console.log(commands);
	m_console.log("===============================================================================\n");
}

void Game::displayInfo()
{	
	displayCommands();
	displayStats();
}

bool contains(std::string _i, std::vector<Action> &_array)
{
	for (int i = 0; i < _array.size(); i++)
	{
		if ("!" + _array[i].m_stringName == _i) { return true; }
	}
	return false;
}

int getIndex(std::string _i, std::vector<Action> &_array)
{
	for (int i = 0; i < _array.size(); i++)
	{
		if ("!" + _array[i].m_stringName == _i) { return i; }
	}
	return false;
}

void Game::start()
{
	int games = 49;
	while (!m_quit)
	{		
		if (!m_playerTesting)
		{
			while (!m_victory && !m_quit)
			{
				if (m_npc->m_CS.m_HP > 0 && m_player->m_CS.m_HP > 0)
				{
					m_npc->startTurn();
					m_npc->update();
				}

				if (m_player->m_CS.m_HP > 0 && m_npc->m_CS.m_HP > 0)
				{
					m_player->startTurn();
					m_player->update();
				}

				///Draw Code
				drawScene();
				/* Removed for efficiency while training */
				m_input.update();
			}
		}
		else
		{
			m_console.log("Welcome.");
			system("PAUSE");
			system("CLS");

			m_console.log("Connecting to Opponent...");
			Sleep(2000);
			m_console.log("Connected!");
			system("PAUSE");
			system("CLS");


			m_console.log("Rolling initiative...");
			Sleep(1000);
			
			m_console.log("\nYou go first!");
			system("PAUSE");
			

			while (!m_victory && !m_quit)
			{
				drawScene();
				m_player->startTurn();
				while (m_player->m_isMyTurn && !m_victory)
				{
					drawScene();
					bool legal = false;
					std::string input;
					while (!legal && !m_victory)
					{
						bool valid = false;
						while (!valid && !m_victory)
						{
							system("CLS");
							m_console.log("[Your Turn]\n");
							displayInfo();
							input = "";
							std::cin >> input;
							m_console.secretLog(input);
							valid = contains(input, m_player->m_actionList);
							if (!valid)
							{
								m_console.log("Invalid Command");
								system("PAUSE");
							}
						}

						int index = getIndex(input, m_player->m_actionList);
						legal = m_player->m_actionList[index].m_legal;
						if (!legal)
						{
							valid = false;
							m_console.log("That action is not legal.");
							system("PAUSE");
						}
						else
						{
							m_player->doAction(m_player->m_actionList[index]);							
						}
					}
				}
				system("CLS");
				m_console.log("[Opponent's Turn]\n");
				m_console.log("Waiting...");
				int time = rand() % 50000;
				Sleep(5000 + time);
				system("CLS");

				if (m_npc->m_CS.m_HP > 0 && m_player->m_CS.m_HP > 0)
				{
					m_npc->startTurn();
					m_npc->update();
				}
				else
				{
					m_victory = true;
				}
				//system("PAUSE");
			}
			system("CLS");
		}




		m_victory = false;
		std::string tag = " ";
		if (m_npc->m_CS.m_HP <= 0) { tag[0] = m_player->m_tag; }
		else if (m_player->m_CS.m_HP <= 0) { tag[0] = m_npc->m_tag; }
		else { tag = "?"; }
		m_console.log("--Player " + tag + " Wins--");
		if (!m_playerTesting)
		{
			games++;
			if (games >= 25)
			{
				m_console.save("Files/");
				games = 0;
			}
		}
		else
		{
			m_console.save("Files/");
			system("PAUSE");
			m_quit = true;
		}

		m_console.clear();		
		initialiseEntities();

		glm::vec2* player_pos = &m_player->m_Pos;
		player_pos->x = 4.0f * m_boxSize;
		player_pos->y = 1.0f * m_boxSize;

		glm::vec2* npc_pos = &m_npc->m_Pos;
		int x;
		int y;
		bool inwall = true;

		while (inwall)
		{
			inwall = false;
			x = rand() % 20;
			y = rand() % 20;
			for (int i = 0; i < m_map.m_walls.size(); i++)
			{
				if (m_map.m_walls[i]->m_Pos == glm::vec2(x, y))
				{
					inwall = true;
					break;
				}
			}
			if (x * m_boxSize == player_pos->x && y * m_boxSize == player_pos->y)
			{
				inwall = true;
			}
		}

		npc_pos->x = x * m_boxSize;
		npc_pos->y = y * m_boxSize;
	}	
}

void Game::drawScene()
{
	SDL_Event event = { 0 };
	while (SDL_PollEvent(&event))
	{
		
	}

	SDL_SetRenderDrawColor(m_renderer, WHITE, 255);
	SDL_RenderClear(m_renderer);

	//Draw the map
	drawGrid(m_renderer, m_map.m_gridX, m_map.m_gridY);
	drawWalls(m_renderer, m_map.m_walls);



	//Draw the player square	
	drawPlayerSquare(m_renderer, m_player, true);
	drawPlayerSquare(m_renderer, m_npc, true);
	SDL_RenderPresent(m_renderer);
	//SDL_Delay(500);
}




//Initialises the Window
SDL_Window* Game::initWindow() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("The Intelligent NPC",
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
	square.x = _entity.m_Pos.x * m_boxSize;
	square.y = _entity.m_Pos.y * m_boxSize;
	square.w = m_boxSize;
	square.h = m_boxSize;
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
	square.w = m_boxSize;
	square.h = m_boxSize;
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

