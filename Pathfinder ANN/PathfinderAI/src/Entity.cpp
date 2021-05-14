#include "Entity.h"
#include "Pathfind.h"
#include "Game.h"
#include <glm/glm.hpp>
#include <iostream>
//#include <stdlib.h>
#include <Windows.h>

void Entity::initialiseActionList()
{
	m_actionList.clear();
	m_actionList.resize(CharacterSheet::EndTurn + 1);
	m_actionList[CharacterSheet::MeleeAttack].m_name = CharacterSheet::MeleeAttack;	
	m_actionList[CharacterSheet::MeleeAttack].m_provokes = false;
	m_actionList[CharacterSheet::MeleeAttack].m_slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::MeleeAttack].m_stringName = "MeleeAttack";

	m_actionList[CharacterSheet::RangedAttack].m_name = CharacterSheet::RangedAttack;	
	m_actionList[CharacterSheet::RangedAttack].m_provokes = true;
	m_actionList[CharacterSheet::RangedAttack].m_slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::RangedAttack].m_stringName = "RangedAttack";

	m_actionList[CharacterSheet::FullMeleeAttack].m_name = CharacterSheet::FullMeleeAttack;	
	m_actionList[CharacterSheet::FullMeleeAttack].m_provokes = false;
	m_actionList[CharacterSheet::FullMeleeAttack].m_slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::FullMeleeAttack].m_stringName = "FullMeleeAttack";

	m_actionList[CharacterSheet::FullRangedAttack].m_name = CharacterSheet::FullRangedAttack;	
	m_actionList[CharacterSheet::FullRangedAttack].m_provokes = true;
	m_actionList[CharacterSheet::FullRangedAttack].m_slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::FullRangedAttack].m_stringName = "FullRangedAttack";

	m_actionList[CharacterSheet::FiveFtStepBack].m_name = CharacterSheet::FiveFtStepBack;
	m_actionList[CharacterSheet::FiveFtStepBack].m_provokes = false;
	m_actionList[CharacterSheet::FiveFtStepBack].m_slot = CharacterSheet::Step;
	m_actionList[CharacterSheet::FiveFtStepBack].m_stringName = "FiveFtStepBack";

	m_actionList[CharacterSheet::FiveFtStepFwd].m_name = CharacterSheet::FiveFtStepFwd;
	m_actionList[CharacterSheet::FiveFtStepFwd].m_provokes = false;
	m_actionList[CharacterSheet::FiveFtStepFwd].m_slot = CharacterSheet::Step;
	m_actionList[CharacterSheet::FiveFtStepFwd].m_stringName = "FiveFtStepFwd";

	m_actionList[CharacterSheet::AttackDefensively].m_name = CharacterSheet::AttackDefensively;
	m_actionList[CharacterSheet::AttackDefensively].m_provokes = false;
	m_actionList[CharacterSheet::AttackDefensively].m_slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::AttackDefensively].m_stringName = "AttackDefensively";

	m_actionList[CharacterSheet::FullAttackDefensively].m_name = CharacterSheet::FullAttackDefensively;
	m_actionList[CharacterSheet::FullAttackDefensively].m_provokes = false;
	m_actionList[CharacterSheet::FullAttackDefensively].m_slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::FullAttackDefensively].m_stringName = "FullAttackDefensively";

	m_actionList[CharacterSheet::TotalDefence].m_name = CharacterSheet::TotalDefence;
	m_actionList[CharacterSheet::TotalDefence].m_provokes = false;
	m_actionList[CharacterSheet::TotalDefence].m_slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::TotalDefence].m_stringName = "TotalDefence";

	m_actionList[CharacterSheet::MoveForMelee].m_name = CharacterSheet::MoveForMelee;
	m_actionList[CharacterSheet::MoveForMelee].m_provokes = true;
	m_actionList[CharacterSheet::MoveForMelee].m_slot = CharacterSheet::Move;
	m_actionList[CharacterSheet::MoveForMelee].m_stringName = "MeleeMovement";

	m_actionList[CharacterSheet::MoveForRanged].m_name = CharacterSheet::MoveForRanged;
	m_actionList[CharacterSheet::MoveForRanged].m_provokes = true;
	m_actionList[CharacterSheet::MoveForRanged].m_slot = CharacterSheet::Move;
	m_actionList[CharacterSheet::MoveForRanged].m_stringName = "RangedMovement";

	m_actionList[CharacterSheet::Draw].m_name = CharacterSheet::Draw;
	m_actionList[CharacterSheet::Draw].m_provokes = false;
	m_actionList[CharacterSheet::Draw].m_slot = CharacterSheet::Move;
	m_actionList[CharacterSheet::Draw].m_stringName = "Draw";

	m_actionList[CharacterSheet::Charge].m_name = CharacterSheet::Charge;
	m_actionList[CharacterSheet::Charge].m_provokes = false;
	m_actionList[CharacterSheet::Charge].m_slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::Charge].m_stringName = "Charge";

	m_actionList[CharacterSheet::AOO].m_name = CharacterSheet::AOO;
	m_actionList[CharacterSheet::AOO].m_provokes = false;
	m_actionList[CharacterSheet::AOO].m_slot = CharacterSheet::Immediate;
	m_actionList[CharacterSheet::AOO].m_stringName = "AOO";

	m_actionList[CharacterSheet::EndTurn].m_name = CharacterSheet::EndTurn;
	m_actionList[CharacterSheet::EndTurn].m_provokes = false;
	m_actionList[CharacterSheet::EndTurn].m_slot = CharacterSheet::Free;
	m_actionList[CharacterSheet::EndTurn].m_stringName = "EndTurn";


	refreshActionList();
}

void Entity::refreshActionList()
{

	m_actionList[CharacterSheet::MeleeAttack].m_legal = true;
	m_actionList[CharacterSheet::RangedAttack].m_legal = true;		
	m_actionList[CharacterSheet::FullMeleeAttack].m_legal = true;		
	m_actionList[CharacterSheet::FullRangedAttack].m_legal = true;	
	m_actionList[CharacterSheet::FiveFtStepBack].m_legal = true;
	m_actionList[CharacterSheet::FiveFtStepFwd].m_legal = true;
	m_actionList[CharacterSheet::AttackDefensively].m_legal = true;
	m_actionList[CharacterSheet::FullAttackDefensively].m_legal = true;
	m_actionList[CharacterSheet::TotalDefence].m_legal = true;
	m_actionList[CharacterSheet::MoveForMelee].m_legal = true;
	m_actionList[CharacterSheet::MoveForRanged].m_legal = true;
	m_actionList[CharacterSheet::Draw].m_legal = true;
	m_actionList[CharacterSheet::Charge].m_legal = true;
}

void Entity::doRandomAction()
{
	int selection = rand() % (CharacterSheet::EndTurn + 1);
	while (m_actionList[selection].m_legal == false)
	{
		selection = rand() % (CharacterSheet::EndTurn + 1);
	}
	doAction(m_actionList[selection]);	
}

void Entity::doAction(Action _a)
{

	if (_a.m_slot == CharacterSheet::Standard)
	{
		disable(_a.m_slot);
		m_moveActionsTaken++;
		if (m_moveActionsTaken == 2)
		{
			disable(CharacterSheet::Move);
		}
		disable(CharacterSheet::FullRound);
	}
	else if (_a.m_slot == CharacterSheet::FullRound)
	{
		disable(_a.m_slot);
		disable(CharacterSheet::Standard);
		disable(CharacterSheet::Move);
		m_moveActionsTaken = 2;
	}
	else if (_a.m_slot == CharacterSheet::Move)
	{
		m_moveActionsTaken++;
		if (m_moveActionsTaken == 2)
		{
			disable(CharacterSheet::Standard);
			disable(CharacterSheet::Move);
		}
		disable(CharacterSheet::FullRound);
	}
	else if (_a.m_slot == CharacterSheet::Immediate)
	{
		disable(_a.m_slot);
	}
	else if (_a.m_slot == CharacterSheet::Step)
	{
		disable(_a.m_slot);
		m_actionList[CharacterSheet::Charge].m_legal = false;
		m_actionList[CharacterSheet::MoveForMelee].m_legal = false;		
		m_actionList[CharacterSheet::MoveForRanged].m_legal = false;		
	}
	
	if (_a.m_provokes)
	{
		m_opponent->takeAOO();
		if (m_CS.m_HP < 1)
		{
			m_isMyTurn = false;
			return;
		}
	}
	if (!m_game->m_playerTesting)
	{
		std::string tag = " ";
		tag[0] = this->m_tag;
		m_game->m_console.log("Player " + tag + ": " + _a.m_stringName);
	}
	else
	{
		if (this->m_tag == 'B')
		{
			system("CLS");
			Sleep(1000);
			m_game->m_console.log("Opponent takes action: " + _a.m_stringName);
			system("PAUSE");
		}		
	}
	
	if (_a.m_name == CharacterSheet::MeleeAttack)
	{
		meleeAttack(m_CS.m_BAB + m_CS.m_STR + m_CS.m_attackBonus);
	}
	else if (_a.m_name == CharacterSheet::FullMeleeAttack)
	{
		for (int i = 0; i < m_CS.m_BAB; i += 5)
		{
			meleeAttack(m_CS.m_BAB + m_CS.m_STR + m_CS.m_attackBonus - i);
		}
	}
	else if (_a.m_name == CharacterSheet::RangedAttack)
	{
		rangedAttack(m_CS.m_BAB + m_CS.m_DEX + m_CS.m_attackBonus);
	}
	else if (_a.m_name == CharacterSheet::FullRangedAttack)
	{
		for (int i = 0; i < m_CS.m_BAB; i += 5)
		{
			rangedAttack(m_CS.m_BAB + m_CS.m_DEX - i + m_CS.m_attackBonus);
		}
	}
	else if (_a.m_name == CharacterSheet::FiveFtStepBack)
	{
		m_Pos = m_fiveFtBackSquare;	
		m_actionList[CharacterSheet::MeleeAttack].m_legal = false;
		m_actionList[CharacterSheet::AttackDefensively].m_legal = false;		
		m_actionList[CharacterSheet::FullMeleeAttack].m_legal = false;
		m_actionList[CharacterSheet::FullAttackDefensively].m_legal = false;
	}
	else if (_a.m_name == CharacterSheet::FiveFtStepFwd)
	{
		std::string route = findPath(m_game->m_map, this, m_opponent->m_Pos.x / m_game->m_boxSize, m_opponent->m_Pos.y / m_game->m_boxSize);
		route.pop_back();

		while (route.size() > 1)
		{
			route.pop_back();
		}
		adjustPosition(route); 

		if (m_CS.m_weapon == CharacterSheet::Longsword && m_moveActionsTaken != 2)
		{
			if (isAdjacent())
			{
				m_actionList[CharacterSheet::MeleeAttack].m_legal = true;
				m_actionList[CharacterSheet::AttackDefensively].m_legal = true;

				if (m_moveActionsTaken == 0)
				{
					m_actionList[CharacterSheet::FullMeleeAttack].m_legal = true;
					m_actionList[CharacterSheet::FullAttackDefensively].m_legal = true;
				}
			}
		}
	}
	else if (_a.m_name == CharacterSheet::AttackDefensively)
	{
		m_CS.m_attackBonus -= 4;
		m_CS.m_ACbonus += 2;
		meleeAttack(m_CS.m_BAB + m_CS.m_STR - 4 + m_CS.m_attackBonus);
	}
	else if (_a.m_name == CharacterSheet::FullAttackDefensively)
	{
		m_CS.m_attackBonus -= 4;
		m_CS.m_ACbonus += 2;
		for (int i = 0; i < m_CS.m_BAB; i += 5)
		{
			meleeAttack(m_CS.m_BAB + m_CS.m_STR - i + m_CS.m_attackBonus);
		}
	}	
	else if (_a.m_name == CharacterSheet::TotalDefence)
	{		
		m_CS.m_ACbonus += 4;
	}
	else if (_a.m_name == CharacterSheet::MoveForMelee)
	{
		std::string route = findPath(m_game->m_map, this, m_opponent->m_Pos.x / m_game->m_boxSize, m_opponent->m_Pos.y / m_game->m_boxSize);
		route.pop_back();

		while (route.size() > 6)
		{
			route.pop_back();
		}
		adjustPosition(route); 
		if (m_CS.m_weapon == CharacterSheet::Longbow && m_moveActionsTaken != 2)
		{
			if (hasStraightLine())
			{
				m_actionList[CharacterSheet::RangedAttack].m_legal = true;
			}
		}
		else if (m_CS.m_weapon == CharacterSheet::Longsword && m_moveActionsTaken != 2)
		{
			if (isAdjacent())
			{
				m_actionList[CharacterSheet::MeleeAttack].m_legal = true;
				m_actionList[CharacterSheet::AttackDefensively].m_legal = true;
			}
		}

		m_actionList[CharacterSheet::FiveFtStepBack].m_legal = false;
		m_actionList[CharacterSheet::FiveFtStepFwd].m_legal = false;
	}
	else if (_a.m_name == CharacterSheet::MoveForRanged)
	{
		glm::vec2 LOS = findLOS();
		std::string route;
		if (LOS != glm::vec2(-1, -1))
		{
			m_LOSsquare = LOS;
			route = findPath(m_game->m_map, this, m_LOSsquare.x, m_LOSsquare.y);
		}
		else
		{
			route = findPath(m_game->m_map, this, m_opponent->m_Pos.x / m_game->m_boxSize, m_opponent->m_Pos.y / m_game->m_boxSize);
			route.pop_back();
		}
		
		while (route.size() > 6)
		{
			route.pop_back();
		}

		adjustPosition(route); 
		if (m_CS.m_weapon == CharacterSheet::Longbow && m_moveActionsTaken != 2)
		{
			if (hasStraightLine())
			{
				m_actionList[CharacterSheet::RangedAttack].m_legal = true;
			}
		}
		else if (m_CS.m_weapon == CharacterSheet::Longsword && m_moveActionsTaken != 2)
		{
			if (isAdjacent())
			{
				m_actionList[CharacterSheet::MeleeAttack].m_legal = true;
				m_actionList[CharacterSheet::AttackDefensively].m_legal = true;
			}
		}
		m_actionList[CharacterSheet::FiveFtStepBack].m_legal = false;
		m_actionList[CharacterSheet::FiveFtStepFwd].m_legal = false;
	}
	else if (_a.m_name == CharacterSheet::Draw)
	{
		if (m_CS.m_weapon == CharacterSheet::Longsword)
		{
			m_CS.m_weapon = CharacterSheet::Longbow;				
			if (hasStraightLine() && m_moveActionsTaken != 2)
			{
				m_actionList[CharacterSheet::RangedAttack].m_legal = true;
			}
			else
			{
				m_actionList[CharacterSheet::RangedAttack].m_legal = false;
			}


			m_actionList[CharacterSheet::MeleeAttack].m_legal = false;
			m_actionList[CharacterSheet::AttackDefensively].m_legal = false;
		}
		else
		{
			m_CS.m_weapon = CharacterSheet::Longsword;
			if (isAdjacent() && m_moveActionsTaken != 2)
			{
				m_actionList[CharacterSheet::MeleeAttack].m_legal = true;
				m_actionList[CharacterSheet::AttackDefensively].m_legal = true;
			}
			else
			{
				m_actionList[CharacterSheet::MeleeAttack].m_legal = false;
				m_actionList[CharacterSheet::AttackDefensively].m_legal = false;
			}
			m_actionList[CharacterSheet::RangedAttack].m_legal = false;
		}
	}
	else if (_a.m_name == CharacterSheet::Charge)
	{		
		m_CS.m_ACbonus -= 2;
		adjustPosition(m_chargePath);
		meleeAttack(m_CS.m_BAB + m_CS.m_STR + m_CS.m_attackBonus + 2);
		disable(CharacterSheet::Step);
	}
	else if (_a.m_name == CharacterSheet::AOO)
	{
		meleeAttack(m_CS.m_BAB + m_CS.m_STR + m_CS.m_attackBonus);
	}
	else if (_a.m_name == CharacterSheet::EndTurn)
	{
		endTurn();
	}
	if (m_opponent->m_CS.m_HP <= 0) { m_game->m_victory = true; }

	if (m_game->m_playerTesting)
	{
		m_game->drawScene();
	}
}

void Entity::disable(CharacterSheet::ActionLength _slot)
{
	for (int i = 0; i < m_actionList.size(); i++)
	{
		if (m_actionList[i].m_slot == _slot)
		{
			m_actionList[i].m_legal = false;
		}
	}
}

void Entity::initialiseANN()
{
	//Weights[0] <-- Layer Number
	//Weights[0][0] <-- Neuron number
	//Weights[0][0][0] <-- Input Connection number

	std::vector<std::vector<std::vector<float>>> weights;

	const int numLayers = m_game->m_layers;
	const int numNodes = m_game->m_nodes;
	const int numOutputs = 13;
	const int numInputs = 11;
	const float weight = 0.05f;
	
	weights.resize(numLayers + 2); // The +2 is to include the input and output layer
	weights[0].resize(numInputs); //0 is the input layer, it has no inputs or weights of its own


	for (int i = 1; i < weights.size() - 1; i++) //This initialises all the middle layers
	{
		weights[i].resize(numNodes);
		for (int l = 0; l < weights[i].size(); l++)
		{
			weights[i][l].resize(weights[i - 1].size());
			for (int j = 0; j < weights[i][l].size(); j++)
			{
				weights[i][l][j] = weight + ((float)(rand() % 6) - 8.0f) / 100.0f;
			}
		}
	}

	int outLayer = weights.size() - 1;
	weights[outLayer].resize(numOutputs);
	for (int l = 0; l < weights[outLayer].size(); l++)
	{
		weights[outLayer][l].resize(numNodes);
		for (int j = 0; j < weights[outLayer][l].size(); j++)
		{
			weights[outLayer][l][j] = weight + ((float)(rand() % 6) - 8.0f) / 100.0f;
		}
	}

	//Makes a new neural network
	if (m_game->m_generateNew)
	{
		m_ANN = new NeuralNetwork(weights, 0.5f);
	}
	else //Loads on from file
	{
		m_ANN = new NeuralNetwork();
		if (m_tag == 'A')
		{
			m_ANN->load("Files/npc/2021-04-26--13-37-42.ann");
		}
		else if (m_tag == 'B')
		{
			m_ANN->load("Files/npc/2021-04-26--13-37-42.ann");
		}
	}
}

bool contains(int _i, std::vector<int> &_array)
{
	if (_array[_i] == 1) { return true; }
	return false;
}

void Entity::update()
{

	m_inputs.m_AC = m_CS.m_AC;
	m_inputs.m_chargeLegal = (int)m_actionList[CharacterSheet::Charge].m_legal;
	m_inputs.m_distance = glm::distance(m_Pos, m_opponent->m_Pos) / m_game->m_boxSize;
	m_inputs.m_enemyAC = m_opponent->m_CS.m_AC;
	m_inputs.m_enemyMeleeAttBonus = m_opponent->m_CS.m_BAB + m_opponent->m_CS.m_STR;
	m_inputs.m_enemyRangedAttBonus = m_opponent->m_CS.m_BAB + m_opponent->m_CS.m_DEX;
	m_inputs.m_meleeAttBonus = m_CS.m_BAB + m_CS.m_STR;
	m_inputs.m_rangedAttBonus = m_CS.m_BAB + m_CS.m_DEX;
	m_inputs.m_rangedLegal = (int)m_actionList[CharacterSheet::RangedAttack].m_legal;
	m_inputs.m_weapon = (int)m_CS.m_weapon;
	m_inputs.m_fiveFtBkLegal = (int)m_actionList[CharacterSheet::FiveFtStepBack].m_legal;



	std::vector<int> selection = m_ANN->makeDecision(&m_inputs);

	if (m_opponent->m_CS.m_HP > 0 && m_CS.m_HP > 0 && !m_game->m_victory)
	{
		if (contains((int)CharacterSheet::Draw, selection))
		{
			doAction(m_actionList[CharacterSheet::Draw]);
		}

		if (contains((int)CharacterSheet::MoveForMelee, selection))
		{
			doAction(m_actionList[CharacterSheet::MoveForMelee]);
			if (!isAdjacent())
			{
				doAction(m_actionList[CharacterSheet::MoveForMelee]);
			}
			else
			{
				if (contains((int)CharacterSheet::MeleeAttack, selection))
				{
					doAction(m_actionList[CharacterSheet::MeleeAttack]);
				}
				else if (contains((int)CharacterSheet::AttackDefensively, selection))
				{
					doAction(m_actionList[CharacterSheet::AttackDefensively]);
				}
			}
		}
		else if (contains((int)CharacterSheet::MoveForRanged, selection))
		{
			doAction(m_actionList[CharacterSheet::MoveForRanged]);
			if (m_actionList[CharacterSheet::RangedAttack].m_legal)
			{
				doAction(m_actionList[CharacterSheet::RangedAttack]);
			}
			else
			{
				doAction(m_actionList[CharacterSheet::MoveForRanged]);
			}
		}
		else if (contains((int)CharacterSheet::FullMeleeAttack, selection))
		{
			if (!isAdjacent())
			{
				if (m_actionList[CharacterSheet::FiveFtStepFwd].m_legal)
				{
					doAction(m_actionList[CharacterSheet::FiveFtStepFwd]);
					if (m_actionList[CharacterSheet::FullMeleeAttack].m_legal)
					{
						doAction(m_actionList[CharacterSheet::FullMeleeAttack]);
					}
				}
			}
			else
			{
				if (m_actionList[CharacterSheet::FullMeleeAttack].m_legal)
				{
					doAction(m_actionList[CharacterSheet::FullMeleeAttack]);
				}
			}
		}
		else if (contains((int)CharacterSheet::FullAttackDefensively, selection))
		{
			if (!isAdjacent())
			{
				if (m_actionList[CharacterSheet::FiveFtStepFwd].m_legal)
				{
					doAction(m_actionList[CharacterSheet::FiveFtStepFwd]);
					if (m_actionList[CharacterSheet::FullAttackDefensively].m_legal)
					{
						doAction(m_actionList[CharacterSheet::FullAttackDefensively]);
					}
				}
			}
			else
			{
				if (m_actionList[CharacterSheet::FullAttackDefensively].m_legal)
				{
					doAction(m_actionList[CharacterSheet::FullAttackDefensively]);
				}
			}
		}
		else if (contains((int)CharacterSheet::FullRangedAttack, selection) && isAdjacent())
		{
			if (m_actionList[CharacterSheet::FiveFtStepBack].m_legal)
			{
				doAction(m_actionList[CharacterSheet::FiveFtStepBack]);
				if (m_actionList[CharacterSheet::FullRangedAttack].m_legal)
				{
					doAction(m_actionList[CharacterSheet::FullRangedAttack]);
				}
			}
		}
		else if (contains((int)CharacterSheet::FullRangedAttack, selection))
		{
			if (m_actionList[CharacterSheet::FullRangedAttack].m_legal)
			{
				doAction(m_actionList[CharacterSheet::FullRangedAttack]);
			}
		}

		
		for (int i = 0; i < selection.size(); i++)
		{			
			if (selection[i] == 1 && i != 11)
			{
				if (m_actionList[i].m_legal)
				{
					doAction(m_actionList[i]);
				}
			}			
		}

		doAction(m_actionList[CharacterSheet::EndTurn]);		
	}
	else
	{
		doAction(m_actionList[CharacterSheet::EndTurn]);
		m_game->m_victory = true;
	}
}

void Entity::startTurn()
{
	m_isMyTurn = true;
	refreshActionList();
	m_moveActionsTaken = 0;
	m_CS.m_ACbonus = 0;
	m_CS.m_attackBonus = 0;
	m_LOSsquare = glm::vec2(-1, -1);
	bool line = hasStraightLine();	

	m_actionList[CharacterSheet::AOO].m_legal = false;
	m_actionList[CharacterSheet::Charge].m_legal = false;
	m_actionList[CharacterSheet::FiveFtStepBack].m_legal = false;
	m_actionList[CharacterSheet::MoveForRanged].m_legal = true;

	m_actionList[CharacterSheet::RangedAttack].m_legal = false;
	m_actionList[CharacterSheet::FullRangedAttack].m_legal = false;

	if (m_CS.m_weapon == CharacterSheet::Longsword)
	{		
		if (line)
		{
			m_chargePath = findPath(m_game->m_map, this);
			if (m_chargePath.size() <= 12 && m_chargePath.size() > 1)
			{
				m_actionList[CharacterSheet::Charge].m_legal = true;
			}
		}
	}
	else
	{
		m_actionList[CharacterSheet::MeleeAttack].m_legal = false;
		m_actionList[CharacterSheet::FullMeleeAttack].m_legal = false;		
		m_actionList[CharacterSheet::FullAttackDefensively].m_legal = false;		
		m_actionList[CharacterSheet::AttackDefensively].m_legal = false;		
		if (line)
		{
			m_actionList[CharacterSheet::RangedAttack].m_legal = true;
			m_actionList[CharacterSheet::FullRangedAttack].m_legal = true;
		}
		
	}	

	if (isAdjacent())
	{
		m_actionList[CharacterSheet::MoveForMelee].m_legal = false;
		m_actionList[CharacterSheet::FiveFtStepFwd].m_legal = false;
		m_actionList[CharacterSheet::FiveFtStepBack].m_legal = can5ftBack();		
	}
	else
	{
		m_actionList[CharacterSheet::MeleeAttack].m_legal = false;
		m_actionList[CharacterSheet::FullMeleeAttack].m_legal = false;
		m_actionList[CharacterSheet::FullAttackDefensively].m_legal = false;
		m_actionList[CharacterSheet::AttackDefensively].m_legal = false;
		m_actionList[CharacterSheet::FiveFtStepBack].m_legal = false;
	}


}

void Entity::endTurn()
{
	m_isMyTurn = false;
	m_actionList[CharacterSheet::AOO].m_legal = true;	
}

void Entity::takeAOO()
{
	if (m_actionList[CharacterSheet::AOO].m_legal && isAdjacent())
	{
		if (m_CS.m_weapon == CharacterSheet::Longsword)
		{
			std::string tag = " ";
			tag[0] = m_opponent->m_tag;
			m_game->m_console.log("Player " + tag + " triggered AOO!");
			if (m_game->m_playerTesting)
			{
				m_game->m_console.log("Type 'Y' to take your attack, or 'N' to pass.");
				std::string input;
				std::cin >> input;
				if (input == "Y") { doAction(m_actionList[CharacterSheet::AOO]); }
			}
			else
			{
				doAction(m_actionList[CharacterSheet::AOO]);
			}
		}
	}
}

std::string Entity::readUntilVal(std::string& _string, int &_i, char _delim)
{
	std::string out = "";
	while (_string[_i] != _delim)
	{
		out += _string[_i];
		_i++;
	}
	_i++;
	return out;
}

void Entity::meleeAttack(int _bonus)
{
	int D20 = roll(20);
	int dmgMod = (int)floor(m_CS.m_STR * 1.5f);
	int dmgDice = 8;
	int damage = 0;

	if (m_game->m_playerTesting)
	{
		bool valid = false;
		while (!valid)
		{
			valid = true;
			system("CLS");
			if (this->m_tag == 'A')
			{
				m_game->displayStats();
				m_game->m_console.log("Type !roll followed by the attack dice + modifier, followed by the damage dice + modifier.");
				m_game->m_console.log("For example: !roll d20+10 d6+5");
				try
				{
					std::string input;
					std::getline(std::cin, input);
					
					while (input == "")
					{
						std::getline(std::cin, input);
					}
					m_game->m_console.secretLog(input);

					int it = 7;
					std::string d = readUntilVal(input, it, '+');
					std::string hm = readUntilVal(input, it, ' ');
					it++;
					std::string dd = readUntilVal(input, it, '+');
					std::string dm = "";
					dm += input[it];
					if (input.length() > it + 1)
					{
						dm += input[it + 1];
					}
					D20 = roll(std::stoi(d));
					_bonus = std::stoi(hm);
					dmgMod = std::stoi(dm);
					dmgDice = std::stoi(dd);
					system("CLS");
					m_game->m_console.log("You rolled: " + std::to_string(D20));
				}
				catch(std::exception e)
				{
					valid = false;
					m_game->m_console.log("Invalid Input");
					system("PAUSE");
				}
			}
		}
	}
	

	if (D20 >= 19)
	{
		int confirm = roll(20);
		if (m_game->m_playerTesting && this->m_tag == 'A')
		{
			m_game->m_console.log("Confirmation Roll: " + std::to_string(confirm));
		}

		if (confirm + _bonus >= m_opponent->m_CS.m_AC)
		{			
			damage = (roll(dmgDice) + dmgMod) + (roll(dmgDice) + dmgMod);
			m_opponent->m_CS.m_HP -= damage;			
			m_game->m_console.log("(CRIT)");
		}
		else
		{
			damage = (roll(dmgDice) + dmgMod);
			m_opponent->m_CS.m_HP -= damage;
			m_game->m_console.log("(Hit)");
		}
	}
	else if (D20 + _bonus >= m_opponent->m_CS.m_AC)
	{
		damage = (roll(dmgDice) + dmgMod);
		m_opponent->m_CS.m_HP -= damage;
		m_game->m_console.log("(Hit)");
	}
	else
	{
		m_game->m_console.log("(Miss)");
	}

	if (m_game->m_playerTesting)
	{
		if (this->m_tag == 'A')
		{
			m_game->m_console.log("(You dealt: " + std::to_string(damage) + " damage!)");
		}
		else
		{
			m_game->m_console.log("(You took: " + std::to_string(damage) + " damage!)");
		}
		system("PAUSE");
	}
}

void Entity::rangedAttack(int _bonus)
{
	int D20 = roll(20);
	int dmgMod = 0;
	int dmgDice = 8;
	int damage = 0;
	
	if (m_game->m_playerTesting)
	{		
		bool valid = false;
		while (!valid)
		{
			valid = true;
			system("CLS");
			if (this->m_tag == 'A')
			{
				m_game->displayStats();
				m_game->m_console.log("Type !roll followed by the attack dice + modifier, followed by the damage dice + modifier.");
				m_game->m_console.log("For example: !roll d20+10 d6+5");

				try
				{
					std::string input;
					std::getline(std::cin, input);
					while (input == "")
					{
						std::getline(std::cin, input);
					}
					m_game->m_console.secretLog(input);
					int it = 7;
					std::string d = readUntilVal(input, it, '+');
					std::string hm = readUntilVal(input, it, ' ');
					it++;
					std::string dd = readUntilVal(input, it, '+');
					std::string dm = "";
					dm += input[it];
					if (input.length() > it + 1)
					{
						dm += input[it + 1];
					}
					D20 = roll(std::stoi(d));
					_bonus = std::stoi(hm);
					dmgMod = std::stoi(dm);
					dmgDice = std::stoi(dd);
					system("CLS");
					m_game->m_console.log("You rolled: " + std::to_string(D20));
				}
				catch (std::exception e)
				{
					valid = false;
					m_game->m_console.log("Invalid Input");
					system("PAUSE");
				}
			}
		}
	}


	if (D20 > 19)
	{
		int confirm = roll(20);
		if (m_game->m_playerTesting && this->m_tag == 'A')
		{
			m_game->m_console.log("Confirmation Roll: " + std::to_string(confirm));
		}

		if (confirm + _bonus >= m_opponent->m_CS.m_AC)
		{
			damage = (roll(dmgDice) + dmgMod) + (roll(dmgDice) + dmgMod) + (roll(dmgDice) + dmgMod);
			m_opponent->m_CS.m_HP -= damage;
			m_game->m_console.log("(CRIT)");
		}
		else
		{
			damage = (roll(dmgDice) + dmgMod);
			m_opponent->m_CS.m_HP -= damage;
			m_game->m_console.log("(Hit)");
		}
	}
	else if (D20 + _bonus >= m_opponent->m_CS.m_AC)
	{
		damage = (roll(dmgDice) + dmgMod);
		m_opponent->m_CS.m_HP -= damage;
		m_game->m_console.log("(Hit)");
	}
	else
	{
		m_game->m_console.log("(Miss)");
	}

	if (m_game->m_playerTesting)
	{
		if (this->m_tag == 'A')
		{
			m_game->m_console.log("(You dealt: " + std::to_string(damage) + " damage!)");
		}
		else
		{
			m_game->m_console.log("(You took: " + std::to_string(damage) + " damage!)");
		}
		system("PAUSE");
	}
}

int Entity::roll(int _dice)
{
	return (rand() % _dice) + 1;
}

bool Entity::isAdjacent()
{	
	if (m_opponent->m_Pos == m_Pos + glm::vec2(0, m_game->m_boxSize))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos + glm::vec2(0, -m_game->m_boxSize))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos + glm::vec2(m_game->m_boxSize, 0))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos + glm::vec2(-m_game->m_boxSize, 0))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos + glm::vec2(m_game->m_boxSize, m_game->m_boxSize))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos + glm::vec2(m_game->m_boxSize, -m_game->m_boxSize))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos + glm::vec2(-m_game->m_boxSize, -m_game->m_boxSize))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos + glm::vec2(-m_game->m_boxSize, m_game->m_boxSize))
	{
		return true;
	}
	else if (m_opponent->m_Pos == m_Pos)
	{
		return true;
	}

	return false;
}

/*
Fast Ray-Box Intersection
by Andrew Woo
from "Graphics Gems", Academic Press, 1990
*/
#define NUMDIM	2
#define RIGHT	0
#define LEFT	1
#define MIDDLE	2

bool Entity::hitBoundingBox(float minB[], float maxB[], float origin[],  float dir[], float coord[])

{
	bool inside = true;
	char quadrant[NUMDIM];
	register int i;
	int whichPlane;
	double maxT[NUMDIM];
	double candidatePlane[NUMDIM];

	/* Find candidate planes; this loop can be avoided if
	rays cast all from the eye(assume perpsective view) */
	for (i = 0; i < NUMDIM; i++)
		if (origin[i] < minB[i]) {
			quadrant[i] = LEFT;
			candidatePlane[i] = minB[i];
			inside = false;
		}
		else if (origin[i] > maxB[i]) {
			quadrant[i] = RIGHT;
			candidatePlane[i] = maxB[i];
			inside = false;
		}
		else {
			quadrant[i] = MIDDLE;
		}

	/* Ray origin inside bounding box */
	if (inside) {
		coord = origin;
		return (true);
	}


	/* Calculate T distances to candidate planes */
	for (i = 0; i < NUMDIM; i++)
		if (quadrant[i] != MIDDLE && dir[i] != 0.)
			maxT[i] = (candidatePlane[i] - origin[i]) / dir[i];
		else
			maxT[i] = -1.;

	/* Get largest of the maxT's for final choice of intersection */
	whichPlane = 0;
	for (i = 1; i < NUMDIM; i++)
		if (maxT[whichPlane] < maxT[i])
			whichPlane = i;

	/* Check final candidate actually inside box */
	if (maxT[whichPlane] < 0.) return (false);
	for (i = 0; i < NUMDIM; i++)
		if (whichPlane != i) {
			coord[i] = origin[i] + maxT[whichPlane] * dir[i];
			if (coord[i] < minB[i] || coord[i] > maxB[i])
				return (false);
		}
		else {
			coord[i] = candidatePlane[i];
		}
	return (true);				/* ray hits box */
}

bool Entity::hasStraightLine()
{	
	for (int i = 0; i < m_game->m_map.m_walls.size(); i++)
	{
		if (m_game->m_map.m_walls[i]->m_Pos == m_Pos / m_game->m_boxSize)
		{
			return false;
		}

		if (m_game->m_map.m_walls[i]->m_Pos.x != 0.0f && m_game->m_map.m_walls[i]->m_Pos.x != m_game->m_map.m_gridX - 1 && m_game->m_map.m_walls[i]->m_Pos.y != m_game->m_map.m_gridX - 1 && m_game->m_map.m_walls[i]->m_Pos.y != 0.0f			)
		{
			float minB[2] = { m_game->m_map.m_walls[i]->m_Pos.x, m_game->m_map.m_walls[i]->m_Pos.y };
			float maxB[2] = { m_game->m_map.m_walls[i]->m_Pos.x + 1.0f, m_game->m_map.m_walls[i]->m_Pos.y + 1.0f };
			float origin[2] = { (m_Pos.x / m_game->m_boxSize) + 0.5f, (m_Pos.y / m_game->m_boxSize) + 0.5f };
			glm::vec2 dir = glm::normalize(m_Pos - m_opponent->m_Pos);
			float ray[2] = { -dir.x, -dir.y };
			float coord[2] = { 0.0f, 0.0f };
			if (hitBoundingBox(minB, maxB, origin, ray, coord))
			{
				glm::vec2 hitPos = glm::vec2(coord[0], coord[1]);
				if (glm::distance(m_Pos / m_game->m_boxSize, hitPos) < glm::distance(m_Pos / m_game->m_boxSize, m_opponent->m_Pos / m_game->m_boxSize))
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Entity::adjustPosition(std::string _route)
{
	for (int i = 0; i < _route.size(); i++)
	{
		switch (_route[i])
		{
			case '1': //Left
				m_Pos.x-= m_game->m_boxSize;
				break;
			case '2': // Right
				m_Pos.x+= m_game->m_boxSize;
				break;
			case '3': // Up
				m_Pos.y-= m_game->m_boxSize;
				break;
			case '4': // Down
				m_Pos.y+= m_game->m_boxSize;
				break;



			case '5':
				m_Pos.y-= m_game->m_boxSize;
				m_Pos.x-= m_game->m_boxSize;
				break;
			case '6':
				m_Pos.y+= m_game->m_boxSize;
				m_Pos.x-= m_game->m_boxSize;
				break;

			case '7':
				m_Pos.y+= m_game->m_boxSize;
				m_Pos.x+= m_game->m_boxSize;
				break;

			case '8':
				m_Pos.y-= m_game->m_boxSize;
				m_Pos.x+= m_game->m_boxSize;
				break;
		}
	}
}

glm::vec2 Entity::findLOS()
{
	glm::ivec2 startPos = m_Pos;
	glm::ivec2 bestPos = glm::vec2(0, 0);

	for (int x = 1; x < m_game->m_map.m_gridX-1; x++)
	{
		for (int y = 1; y < m_game->m_map.m_gridY-1; y++)
		{
			m_Pos = glm::vec2(x * m_game->m_boxSize, y * m_game->m_boxSize);
			if (!isAdjacent())
			{
				if (hasStraightLine())
				{
					m_Pos = startPos;
					std::string route = findPath(m_game->m_map, this, x, y);
					if (route.size() > 0 && route.size() <= 6)
					{
						if (glm::distance(glm::vec2(x * m_game->m_boxSize, y * m_game->m_boxSize), m_opponent->m_Pos) >= glm::distance(m_Pos, m_opponent->m_Pos))
						{							
							return glm::vec2(x, y);	
						}
					}
				}
				m_Pos = startPos;
			}
			m_Pos = startPos;
		}
	}

	if (bestPos == glm::ivec2(0, 0))
	{
		return glm::ivec2(-1, -1);
	}
	else
	{
		return bestPos;
	}
}

bool Entity::can5ftBack()
{
	if (!isAdjacent()) { return false; }
	glm::vec2 startPos = m_Pos;

	m_Pos = glm::vec2(startPos.x + m_game->m_boxSize, startPos.y);
	if (!isAdjacent() && hasStraightLine()) 
	{ 
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true; 
	}

	m_Pos = glm::vec2(startPos.x - m_game->m_boxSize, startPos.y);
	if (!isAdjacent() && hasStraightLine()) {
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x, startPos.y - m_game->m_boxSize);
	if (!isAdjacent() && hasStraightLine()) {
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}
	m_Pos = glm::vec2(startPos.x, startPos.y + m_game->m_boxSize);
	if (!isAdjacent() && hasStraightLine()) {
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x - m_game->m_boxSize, startPos.y - m_game->m_boxSize);
	if (!isAdjacent() && hasStraightLine()) {
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x + m_game->m_boxSize, startPos.y - m_game->m_boxSize);
	if (!isAdjacent() && hasStraightLine()) {
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x + m_game->m_boxSize, startPos.y + m_game->m_boxSize);
	if (!isAdjacent() && hasStraightLine()) {
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x - m_game->m_boxSize, startPos.y + m_game->m_boxSize);
	if (!isAdjacent() && hasStraightLine()) {
		m_fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = startPos;
	return false;
}
