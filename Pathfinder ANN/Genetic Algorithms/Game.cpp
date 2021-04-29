#include <iostream>
#include <random>
#include <ctime>
#include <glm.hpp>
#include <sstream>
#include "Game.h"
#include "MapLoader.h"
#include "Sheet.h"
#include "Entity.h"
#include <stdlib.h>
#include <Windows.h>
#include <direct.h>


#define WINDOW_WIDTH 980
#define WINDOW_HEIGHT 800
#define RED 255, 0, 0
#define BLUE 0, 0, 255
#define GREEN 0, 255, 0
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0


int main(int argc, char *argv[])
{		
	std::cout << "[LOADING]" << std::endl;
	//Game game(std::atoi(argv[1]), std::atoi(argv[2]));
	Game game(0, 0);
	game.start();
	return 0;
}

void Game::InitialiseEntities()
{
	player->m_Pos.x = 4.0f * boxSize;
	player->m_Pos.y = 1.0f * boxSize;


	if (!PlayerTesting)
	{
		player->CS.weapon = (CharacterSheet::Weapon)(rand() % 2);
		player->CS.HP = 40;
		player->CS.ACbonus = 0;
		player->CS.attackBonus = 0;
		player->CS.AC = 10 + rand() % 11;
		player->CS.DEX = rand() % 7;
		player->CS.STR = rand() % 7;
		player->CS.BAB = 6;
		player->CS.MoveSpeed = 30;
		

		npc->CS.weapon = (CharacterSheet::Weapon)(rand() % 2);
		npc->CS.BAB = 6;
		npc->CS.MoveSpeed = 30;
		npc->CS.HP = 40;
		npc->CS.ACbonus = 0;
		npc->CS.attackBonus = 0;
		npc->CS.AC = 10 + rand() % 11;
		npc->CS.DEX = rand() % 7;
		npc->CS.STR = rand() % 7;
	}
	else
	{
		player->CS.weapon = CharacterSheet::Longsword;
		player->CS.HP = 45;
		player->CS.BAB = 6;
		player->CS.MoveSpeed = 30;
		player->CS.ACbonus = 0;
		player->CS.attackBonus = 0;
		player->CS.AC = 10 + 8;
		player->CS.DEX = 4;
		player->CS.STR = 4;

		npc->CS.weapon = (CharacterSheet::Weapon)(rand() % 2);
		npc->CS.HP = 45;
		npc->CS.BAB = 6;
		npc->CS.MoveSpeed = 30;
		npc->CS.ACbonus = 0;
		npc->CS.attackBonus = 0;
		npc->CS.AC = 10 + 8;
		npc->CS.DEX = 4;
		npc->CS.STR = 4;
	}
}

Game::Game(int _layers, int _nodes)
{
	srand(time(NULL));
	window = initWindow();
	renderer = initRenderer(window);
	map = readFile("map.txt");	
	player = new Entity(4.0f * boxSize, 1.0f * boxSize);
	npc = new Entity(14.0f * boxSize, 14.0f * boxSize);

	layers = _layers;
	nodes = _nodes;
	player->tag = 'A';
	player->game = this;
	player->initialiseActionList();
	//player->InitialiseANN();
	player->ANN = new NeuralNetwork();
	player->m_col = Colour(0, 255, 0, 255);
	
	player->opponent = npc;
	player->ANN->player = true;

	npc->tag = 'B';
	npc->game = this;
	npc->initialiseActionList();
	npc->InitialiseANN();
	npc->opponent = player;
	npc->m_col = Colour(255, 0, 0, 255);
	

	InitialiseEntities();

	
	SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	victory = false;
	quit = false;

	input.game = this;
	player->ANN->game = this;
	npc->ANN->game = this;
}

void Game::DisplayStats()
{
	console.Log("Your Stats:");
	console.Log("===============================================================================");
	std::string stats = "";
	stats += "HP: " + std::to_string(player->CS.HP) + " | ";
	stats += "AC: " + std::to_string(player->CS.AC) + " | ";
	stats += "STR: " + std::to_string(player->CS.STR) + " | ";
	stats += "DEX: " + std::to_string(player->CS.DEX) + " | ";
	stats += "BAB: " + std::to_string(player->CS.BAB) + " | ";
	stats += "Speed: " + std::to_string(player->CS.MoveSpeed) + " | ";
	if (player->CS.weapon == CharacterSheet::Longsword)
	{
		stats += "Weapon: Longsword | ";
	}
	else
	{
		stats += "Weapon: Longbow | ";
	}
	console.Log(stats);
	console.Log("===============================================================================\n");
}

void Game::DisplayCommands()
{
	console.Log("Command List:");
	console.Log("===============================================================================");
	std::string commands = "";
	for (int i = 0; i < player->m_actionList.size(); i++)
	{
		commands += "!" + player->m_actionList[i].stringName + " | ";
	}
	console.Log(commands);
	console.Log("===============================================================================\n");
}

void Game::DisplayInfo()
{	
	DisplayCommands();
	DisplayStats();
}

bool contains(std::string _i, std::vector<Action> &_array)
{
	for (int i = 0; i < _array.size(); i++)
	{
		if ("!" + _array[i].stringName == _i) { return true; }
	}
	return false;
}

int getIndex(std::string _i, std::vector<Action> &_array)
{
	for (int i = 0; i < _array.size(); i++)
	{
		if ("!" + _array[i].stringName == _i) { return i; }
	}
	return false;
}

void Game::start()
{
	int games = 49;
	while (!quit)
	{		
		if (!PlayerTesting)
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
		}
		else
		{
			console.Log("Welcome.");
			system("PAUSE");
			system("CLS");

			console.Log("Connecting to Opponent...");
			Sleep(2000);
			console.Log("Connected!");
			system("PAUSE");
			system("CLS");


			console.Log("Rolling initiative...");
			Sleep(1000);
			
			console.Log("\nYou go first!");
			system("PAUSE");
			

			while (!victory && !quit)
			{
				drawScene();
				player->StartTurn();
				while (player->isMyTurn && !victory)
				{
					drawScene();
					bool legal = false;
					std::string input;
					while (!legal && !victory)
					{
						bool valid = false;
						while (!valid && !victory)
						{
							system("CLS");
							console.Log("[Your Turn]\n");
							DisplayInfo();
							input = "";
							std::cin >> input;
							console.SecretLog(input);
							valid = contains(input, player->m_actionList);
							if (!valid)
							{
								console.Log("Invalid Command");
								system("PAUSE");
							}
						}

						int index = getIndex(input, player->m_actionList);
						legal = player->m_actionList[index].legal;
						if (!legal)
						{
							valid = false;
							console.Log("That action is not legal.");
							system("PAUSE");
						}
						else
						{
							player->DoAction(player->m_actionList[index]);							
						}
					}
				}
				system("CLS");
				console.Log("[Opponent's Turn]\n");
				console.Log("Waiting...");
				int time = rand() % 50000;
				Sleep(5000 + time);
				system("CLS");

				if (npc->CS.HP > 0 && player->CS.HP > 0)
				{
					npc->StartTurn();
					npc->Update();
				}
				else
				{
					victory = true;
				}
				//system("PAUSE");
			}
			system("CLS");
		}




		victory = false;
		std::string tag = " ";
		if (npc->CS.HP <= 0) { tag[0] = player->tag; }
		else if (player->CS.HP <= 0) { tag[0] = npc->tag; }
		else { tag = "?"; }
		console.Log("--Player " + tag + " Wins--");
		if (!PlayerTesting)
		{
			games++;
			if (games >= 25)
			{
				console.Save("Files/");
				games = 0;
			}
		}
		else
		{
			console.Save("Files/");
			system("PAUSE");
			quit = true;
		}

		console.Clear();		
		InitialiseEntities();

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

