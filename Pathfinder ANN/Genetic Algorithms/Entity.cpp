#include "Entity.h"
#include "Pathfind.h"
#include "Game.h"
#include <glm.hpp>
#include <iostream>
//#include <stdlib.h>
#include <Windows.h>

void Entity::initialiseActionList()
{
	m_actionList.clear();
	m_actionList.resize(CharacterSheet::EndTurn + 1);
	m_actionList[CharacterSheet::MeleeAttack].name = CharacterSheet::MeleeAttack;	
	m_actionList[CharacterSheet::MeleeAttack].provokes = false;
	m_actionList[CharacterSheet::MeleeAttack].slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::MeleeAttack].stringName = "MeleeAttack";

	m_actionList[CharacterSheet::RangedAttack].name = CharacterSheet::RangedAttack;	
	m_actionList[CharacterSheet::RangedAttack].provokes = true;
	m_actionList[CharacterSheet::RangedAttack].slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::RangedAttack].stringName = "RangedAttack";

	m_actionList[CharacterSheet::FullMeleeAttack].name = CharacterSheet::FullMeleeAttack;	
	m_actionList[CharacterSheet::FullMeleeAttack].provokes = false;
	m_actionList[CharacterSheet::FullMeleeAttack].slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::FullMeleeAttack].stringName = "FullMeleeAttack";

	m_actionList[CharacterSheet::FullRangedAttack].name = CharacterSheet::FullRangedAttack;	
	m_actionList[CharacterSheet::FullRangedAttack].provokes = true;
	m_actionList[CharacterSheet::FullRangedAttack].slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::FullRangedAttack].stringName = "FullRangedAttack";

	m_actionList[CharacterSheet::FiveFtStepBack].name = CharacterSheet::FiveFtStepBack;
	m_actionList[CharacterSheet::FiveFtStepBack].provokes = false;
	m_actionList[CharacterSheet::FiveFtStepBack].slot = CharacterSheet::Step;
	m_actionList[CharacterSheet::FiveFtStepBack].stringName = "FiveFtStepBack";

	m_actionList[CharacterSheet::FiveFtStepFwd].name = CharacterSheet::FiveFtStepFwd;
	m_actionList[CharacterSheet::FiveFtStepFwd].provokes = false;
	m_actionList[CharacterSheet::FiveFtStepFwd].slot = CharacterSheet::Step;
	m_actionList[CharacterSheet::FiveFtStepFwd].stringName = "FiveFtStepFwd";

	m_actionList[CharacterSheet::AttackDefensively].name = CharacterSheet::AttackDefensively;
	m_actionList[CharacterSheet::AttackDefensively].provokes = false;
	m_actionList[CharacterSheet::AttackDefensively].slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::AttackDefensively].stringName = "AttackDefensively";

	m_actionList[CharacterSheet::FullAttackDefensively].name = CharacterSheet::FullAttackDefensively;
	m_actionList[CharacterSheet::FullAttackDefensively].provokes = false;
	m_actionList[CharacterSheet::FullAttackDefensively].slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::FullAttackDefensively].stringName = "FullAttackDefensively";

	m_actionList[CharacterSheet::TotalDefence].name = CharacterSheet::TotalDefence;
	m_actionList[CharacterSheet::TotalDefence].provokes = false;
	m_actionList[CharacterSheet::TotalDefence].slot = CharacterSheet::Standard;
	m_actionList[CharacterSheet::TotalDefence].stringName = "TotalDefence";

	m_actionList[CharacterSheet::MoveForMelee].name = CharacterSheet::MoveForMelee;
	m_actionList[CharacterSheet::MoveForMelee].provokes = true;
	m_actionList[CharacterSheet::MoveForMelee].slot = CharacterSheet::Move;
	m_actionList[CharacterSheet::MoveForMelee].stringName = "MeleeMovement";

	m_actionList[CharacterSheet::MoveForRanged].name = CharacterSheet::MoveForRanged;
	m_actionList[CharacterSheet::MoveForRanged].provokes = true;
	m_actionList[CharacterSheet::MoveForRanged].slot = CharacterSheet::Move;
	m_actionList[CharacterSheet::MoveForRanged].stringName = "RangedMovement";

	m_actionList[CharacterSheet::Draw].name = CharacterSheet::Draw;
	m_actionList[CharacterSheet::Draw].provokes = false;
	m_actionList[CharacterSheet::Draw].slot = CharacterSheet::Move;
	m_actionList[CharacterSheet::Draw].stringName = "Draw";

	m_actionList[CharacterSheet::Charge].name = CharacterSheet::Charge;
	m_actionList[CharacterSheet::Charge].provokes = false;
	m_actionList[CharacterSheet::Charge].slot = CharacterSheet::FullRound;
	m_actionList[CharacterSheet::Charge].stringName = "Charge";

	m_actionList[CharacterSheet::AOO].name = CharacterSheet::AOO;
	m_actionList[CharacterSheet::AOO].provokes = false;
	m_actionList[CharacterSheet::AOO].slot = CharacterSheet::Immediate;
	m_actionList[CharacterSheet::AOO].stringName = "AOO";

	m_actionList[CharacterSheet::EndTurn].name = CharacterSheet::EndTurn;
	m_actionList[CharacterSheet::EndTurn].provokes = false;
	m_actionList[CharacterSheet::EndTurn].slot = CharacterSheet::Free;
	m_actionList[CharacterSheet::EndTurn].stringName = "EndTurn";


	refreshActionList();
}

void Entity::refreshActionList()
{

	m_actionList[CharacterSheet::MeleeAttack].legal = true;
	m_actionList[CharacterSheet::RangedAttack].legal = true;		
	m_actionList[CharacterSheet::FullMeleeAttack].legal = true;		
	m_actionList[CharacterSheet::FullRangedAttack].legal = true;	
	m_actionList[CharacterSheet::FiveFtStepBack].legal = true;
	m_actionList[CharacterSheet::FiveFtStepFwd].legal = true;
	m_actionList[CharacterSheet::AttackDefensively].legal = true;
	m_actionList[CharacterSheet::FullAttackDefensively].legal = true;
	m_actionList[CharacterSheet::TotalDefence].legal = true;
	m_actionList[CharacterSheet::MoveForMelee].legal = true;
	m_actionList[CharacterSheet::MoveForRanged].legal = true;
	m_actionList[CharacterSheet::Draw].legal = true;
	m_actionList[CharacterSheet::Charge].legal = true;
}

void Entity::DoRandomAction()
{
	int selection = rand() % (CharacterSheet::EndTurn + 1);
	while (m_actionList[selection].legal == false)
	{
		selection = rand() % (CharacterSheet::EndTurn + 1);
	}
	DoAction(m_actionList[selection]);	
}

void Entity::DoAction(Action _a)
{

	if (_a.slot == CharacterSheet::Standard)
	{
		Disable(_a.slot);
		MoveActionsTaken++;
		if (MoveActionsTaken == 2)
		{
			Disable(CharacterSheet::Move);
		}
		Disable(CharacterSheet::FullRound);
	}
	else if (_a.slot == CharacterSheet::FullRound)
	{
		Disable(_a.slot);
		Disable(CharacterSheet::Standard);
		Disable(CharacterSheet::Move);
		MoveActionsTaken = 2;
	}
	else if (_a.slot == CharacterSheet::Move)
	{
		MoveActionsTaken++;
		if (MoveActionsTaken == 2)
		{
			Disable(CharacterSheet::Standard);
			Disable(CharacterSheet::Move);
		}
		Disable(CharacterSheet::FullRound);
	}
	else if (_a.slot == CharacterSheet::Immediate)
	{
		Disable(_a.slot);
	}
	else if (_a.slot == CharacterSheet::Step)
	{
		Disable(_a.slot);
		m_actionList[CharacterSheet::Charge].legal = false;
		m_actionList[CharacterSheet::MoveForMelee].legal = false;		
		m_actionList[CharacterSheet::MoveForRanged].legal = false;		
	}
	
	if (_a.provokes)
	{
		opponent->TakeAOO();
		if (CS.HP < 1)
		{
			isMyTurn = false;
			return;
		}
	}
	if (!game->PlayerTesting)
	{
		std::string tag = " ";
		tag[0] = this->tag;
		game->console.Log("Player " + tag + ": " + _a.stringName);
	}
	else
	{
		if (this->tag == 'B')
		{
			system("CLS");
			Sleep(1000);
			game->console.Log("Opponent takes action: " + _a.stringName);
			system("PAUSE");
		}		
	}
	
	if (_a.name == CharacterSheet::MeleeAttack)
	{
		MeleeAttack(CS.BAB + CS.STR + CS.attackBonus);
	}
	else if (_a.name == CharacterSheet::FullMeleeAttack)
	{
		for (int i = 0; i < CS.BAB; i += 5)
		{
			MeleeAttack(CS.BAB + CS.STR + CS.attackBonus - i);
		}
	}
	else if (_a.name == CharacterSheet::RangedAttack)
	{
		RangedAttack(CS.BAB + CS.DEX + CS.attackBonus);
	}
	else if (_a.name == CharacterSheet::FullRangedAttack)
	{
		for (int i = 0; i < CS.BAB; i += 5)
		{
			RangedAttack(CS.BAB + CS.DEX - i + CS.attackBonus);
		}
	}
	else if (_a.name == CharacterSheet::FiveFtStepBack)
	{
		m_Pos = fiveFtBackSquare;	
		m_actionList[CharacterSheet::MeleeAttack].legal = false;
		m_actionList[CharacterSheet::AttackDefensively].legal = false;		
		m_actionList[CharacterSheet::FullMeleeAttack].legal = false;
		m_actionList[CharacterSheet::FullAttackDefensively].legal = false;
	}
	else if (_a.name == CharacterSheet::FiveFtStepFwd)
	{
		std::string route = findPath(game->map, this, opponent->m_Pos.x / game->boxSize, opponent->m_Pos.y / game->boxSize);
		route.pop_back();

		while (route.size() > 1)
		{
			route.pop_back();
		}
		AdjustPosition(route); 

		if (CS.weapon == CharacterSheet::Longsword && MoveActionsTaken != 2)
		{
			if (isAdjacent())
			{
				m_actionList[CharacterSheet::MeleeAttack].legal = true;
				m_actionList[CharacterSheet::AttackDefensively].legal = true;

				if (MoveActionsTaken == 0)
				{
					m_actionList[CharacterSheet::FullMeleeAttack].legal = true;
					m_actionList[CharacterSheet::FullAttackDefensively].legal = true;
				}
			}
		}
	}
	else if (_a.name == CharacterSheet::AttackDefensively)
	{
		CS.attackBonus -= 4;
		CS.ACbonus += 2;
		MeleeAttack(CS.BAB + CS.STR - 4 + CS.attackBonus);
	}
	else if (_a.name == CharacterSheet::FullAttackDefensively)
	{
		CS.attackBonus -= 4;
		CS.ACbonus += 2;
		for (int i = 0; i < CS.BAB; i += 5)
		{
			MeleeAttack(CS.BAB + CS.STR - i + CS.attackBonus);
		}
	}	
	else if (_a.name == CharacterSheet::TotalDefence)
	{		
		CS.ACbonus += 4;
	}
	else if (_a.name == CharacterSheet::MoveForMelee)
	{
		std::string route = findPath(game->map, this, opponent->m_Pos.x / game->boxSize, opponent->m_Pos.y / game->boxSize);
		route.pop_back();

		while (route.size() > 6)
		{
			route.pop_back();
		}
		AdjustPosition(route); 
		if (CS.weapon == CharacterSheet::Longbow && MoveActionsTaken != 2)
		{
			if (HasStraightLine())
			{
				m_actionList[CharacterSheet::RangedAttack].legal = true;
			}
		}
		else if (CS.weapon == CharacterSheet::Longsword && MoveActionsTaken != 2)
		{
			if (isAdjacent())
			{
				m_actionList[CharacterSheet::MeleeAttack].legal = true;
				m_actionList[CharacterSheet::AttackDefensively].legal = true;
			}
		}

		m_actionList[CharacterSheet::FiveFtStepBack].legal = false;
		m_actionList[CharacterSheet::FiveFtStepFwd].legal = false;
	}
	else if (_a.name == CharacterSheet::MoveForRanged)
	{
		glm::vec2 LOS = findLOS();
		std::string route;
		if (LOS != glm::vec2(-1, -1))
		{
			LOSsquare = LOS;
			route = findPath(game->map, this, LOSsquare.x, LOSsquare.y);
		}
		else
		{
			route = findPath(game->map, this, opponent->m_Pos.x / game->boxSize, opponent->m_Pos.y / game->boxSize);
			route.pop_back();
		}
		
		while (route.size() > 6)
		{
			route.pop_back();
		}

		AdjustPosition(route); 
		if (CS.weapon == CharacterSheet::Longbow && MoveActionsTaken != 2)
		{
			if (HasStraightLine())
			{
				m_actionList[CharacterSheet::RangedAttack].legal = true;
			}
		}
		else if (CS.weapon == CharacterSheet::Longsword && MoveActionsTaken != 2)
		{
			if (isAdjacent())
			{
				m_actionList[CharacterSheet::MeleeAttack].legal = true;
				m_actionList[CharacterSheet::AttackDefensively].legal = true;
			}
		}
		m_actionList[CharacterSheet::FiveFtStepBack].legal = false;
		m_actionList[CharacterSheet::FiveFtStepFwd].legal = false;
	}
	else if (_a.name == CharacterSheet::Draw)
	{
		if (CS.weapon == CharacterSheet::Longsword)
		{
			CS.weapon = CharacterSheet::Longbow;				
			if (HasStraightLine() && MoveActionsTaken != 2)
			{
				m_actionList[CharacterSheet::RangedAttack].legal = true;
			}
			else
			{
				m_actionList[CharacterSheet::RangedAttack].legal = false;
			}


			m_actionList[CharacterSheet::MeleeAttack].legal = false;
			m_actionList[CharacterSheet::AttackDefensively].legal = false;
		}
		else
		{
			CS.weapon = CharacterSheet::Longsword;
			if (isAdjacent() && MoveActionsTaken != 2)
			{
				m_actionList[CharacterSheet::MeleeAttack].legal = true;
				m_actionList[CharacterSheet::AttackDefensively].legal = true;
			}
			else
			{
				m_actionList[CharacterSheet::MeleeAttack].legal = false;
				m_actionList[CharacterSheet::AttackDefensively].legal = false;
			}
			m_actionList[CharacterSheet::RangedAttack].legal = false;
		}
	}
	else if (_a.name == CharacterSheet::Charge)
	{		
		CS.ACbonus -= 2;
		AdjustPosition(chargePath);
		MeleeAttack(CS.BAB + CS.STR + CS.attackBonus + 2);
		Disable(CharacterSheet::Step);
	}
	else if (_a.name == CharacterSheet::AOO)
	{
		MeleeAttack(CS.BAB + CS.STR + CS.attackBonus);
	}
	else if (_a.name == CharacterSheet::EndTurn)
	{
		EndTurn();
	}
	if (opponent->CS.HP <= 0) { game->victory = true; }

	if (game->PlayerTesting)
	{
		game->drawScene();
	}
}

void Entity::Disable(CharacterSheet::ActionLength _slot)
{
	for (int i = 0; i < m_actionList.size(); i++)
	{
		if (m_actionList[i].slot == _slot)
		{
			m_actionList[i].legal = false;
		}
	}
}

void Entity::InitialiseANN()
{
	//Weights[0] <-- Layer Number
	//Weights[0][0] <-- Neuron number
	//Weights[0][0][0] <-- Input Connection number

	std::vector<std::vector<std::vector<float>>> weights;

	const int numLayers = game->layers;
	const int numNodes = game->nodes;
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
	//ANN = new NeuralNetwork(weights, 0.5f);


	ANN = new NeuralNetwork();	
	
	if (tag == 'A')
	{
		ANN->Load("Files/npc/2021-04-26--13-37-42.ann");
	}
	else if (tag == 'B')
	{
		ANN->Load("Files/npc/2021-04-26--13-37-42.ann");
	}
}

bool contains(int _i, std::vector<int> &_array)
{
	if (_array[_i] == 1) { return true; }
	return false;
}

void Entity::Update()
{

	inputs.AC = CS.AC;
	inputs.chargeLegal = (int)m_actionList[CharacterSheet::Charge].legal;
	inputs.distance = glm::distance(m_Pos, opponent->m_Pos) / game->boxSize;
	inputs.enemyAC = opponent->CS.AC;
	inputs.enemyMeleeAttBonus = opponent->CS.BAB + opponent->CS.STR;
	inputs.enemyRangedAttBonus = opponent->CS.BAB + opponent->CS.DEX;
	inputs.meleeAttBonus = CS.BAB + CS.STR;
	inputs.rangedAttBonus = CS.BAB + CS.DEX;
	inputs.rangedLegal = (int)m_actionList[CharacterSheet::RangedAttack].legal;
	inputs.weapon = (int)CS.weapon;
	inputs.fiveFtBkLegal = (int)m_actionList[CharacterSheet::FiveFtStepBack].legal;



	std::vector<int> selection = ANN->makeDecision(&inputs);

	if (opponent->CS.HP > 0 && CS.HP > 0 && !game->victory)
	{
		if (contains((int)CharacterSheet::Draw, selection))
		{
			DoAction(m_actionList[CharacterSheet::Draw]);
		}

		if (contains((int)CharacterSheet::MoveForMelee, selection))
		{
			DoAction(m_actionList[CharacterSheet::MoveForMelee]);
			if (!isAdjacent())
			{
				DoAction(m_actionList[CharacterSheet::MoveForMelee]);
			}
			else
			{
				if (contains((int)CharacterSheet::MeleeAttack, selection))
				{
					DoAction(m_actionList[CharacterSheet::MeleeAttack]);
				}
				else if (contains((int)CharacterSheet::AttackDefensively, selection))
				{
					DoAction(m_actionList[CharacterSheet::AttackDefensively]);
				}
			}
		}
		else if (contains((int)CharacterSheet::MoveForRanged, selection))
		{
			DoAction(m_actionList[CharacterSheet::MoveForRanged]);
			if (m_actionList[CharacterSheet::RangedAttack].legal)
			{
				DoAction(m_actionList[CharacterSheet::RangedAttack]);
			}
			else
			{
				DoAction(m_actionList[CharacterSheet::MoveForRanged]);
			}
		}
		else if (contains((int)CharacterSheet::FullMeleeAttack, selection))
		{
			if (!isAdjacent())
			{
				if (m_actionList[CharacterSheet::FiveFtStepFwd].legal)
				{
					DoAction(m_actionList[CharacterSheet::FiveFtStepFwd]);
					if (m_actionList[CharacterSheet::FullMeleeAttack].legal)
					{
						DoAction(m_actionList[CharacterSheet::FullMeleeAttack]);
					}
				}
			}
			else
			{
				if (m_actionList[CharacterSheet::FullMeleeAttack].legal)
				{
					DoAction(m_actionList[CharacterSheet::FullMeleeAttack]);
				}
			}
		}
		else if (contains((int)CharacterSheet::FullAttackDefensively, selection))
		{
			if (!isAdjacent())
			{
				if (m_actionList[CharacterSheet::FiveFtStepFwd].legal)
				{
					DoAction(m_actionList[CharacterSheet::FiveFtStepFwd]);
					if (m_actionList[CharacterSheet::FullAttackDefensively].legal)
					{
						DoAction(m_actionList[CharacterSheet::FullAttackDefensively]);
					}
				}
			}
			else
			{
				if (m_actionList[CharacterSheet::FullAttackDefensively].legal)
				{
					DoAction(m_actionList[CharacterSheet::FullAttackDefensively]);
				}
			}
		}
		else if (contains((int)CharacterSheet::FullRangedAttack, selection) && isAdjacent())
		{
			if (m_actionList[CharacterSheet::FiveFtStepBack].legal)
			{
				DoAction(m_actionList[CharacterSheet::FiveFtStepBack]);
				if (m_actionList[CharacterSheet::FullRangedAttack].legal)
				{
					DoAction(m_actionList[CharacterSheet::FullRangedAttack]);
				}
			}
		}
		else if (contains((int)CharacterSheet::FullRangedAttack, selection))
		{
			if (m_actionList[CharacterSheet::FullRangedAttack].legal)
			{
				DoAction(m_actionList[CharacterSheet::FullRangedAttack]);
			}
		}

		
		for (int i = 0; i < selection.size(); i++)
		{			
			if (selection[i] == 1 && i != 11)
			{
				if (m_actionList[i].legal)
				{
					DoAction(m_actionList[i]);
				}
			}			
		}

		DoAction(m_actionList[CharacterSheet::EndTurn]);		
	}
	else
	{
		DoAction(m_actionList[CharacterSheet::EndTurn]);
		game->victory = true;
	}
}

void Entity::StartTurn()
{
	isMyTurn = true;
	refreshActionList();
	MoveActionsTaken = 0;
	CS.ACbonus = 0;
	CS.attackBonus = 0;
	LOSsquare = glm::vec2(-1, -1);
	bool line = HasStraightLine();	

	m_actionList[CharacterSheet::AOO].legal = false;
	m_actionList[CharacterSheet::Charge].legal = false;
	m_actionList[CharacterSheet::FiveFtStepBack].legal = false;
	m_actionList[CharacterSheet::MoveForRanged].legal = true;

	m_actionList[CharacterSheet::RangedAttack].legal = false;
	m_actionList[CharacterSheet::FullRangedAttack].legal = false;

	if (CS.weapon == CharacterSheet::Longsword)
	{		
		if (line)
		{
			chargePath = findPath(game->map, this);
			if (chargePath.size() <= 12 && chargePath.size() > 1)
			{
				m_actionList[CharacterSheet::Charge].legal = true;
			}
		}
	}
	else
	{
		m_actionList[CharacterSheet::MeleeAttack].legal = false;
		m_actionList[CharacterSheet::FullMeleeAttack].legal = false;		
		m_actionList[CharacterSheet::FullAttackDefensively].legal = false;		
		m_actionList[CharacterSheet::AttackDefensively].legal = false;		
		if (line)
		{
			m_actionList[CharacterSheet::RangedAttack].legal = true;
			m_actionList[CharacterSheet::FullRangedAttack].legal = true;
		}
		
	}	

	if (isAdjacent())
	{
		m_actionList[CharacterSheet::MoveForMelee].legal = false;
		m_actionList[CharacterSheet::FiveFtStepFwd].legal = false;
		m_actionList[CharacterSheet::FiveFtStepBack].legal = can5ftBack();		
	}
	else
	{
		m_actionList[CharacterSheet::MeleeAttack].legal = false;
		m_actionList[CharacterSheet::FullMeleeAttack].legal = false;
		m_actionList[CharacterSheet::FullAttackDefensively].legal = false;
		m_actionList[CharacterSheet::AttackDefensively].legal = false;
		m_actionList[CharacterSheet::FiveFtStepBack].legal = false;
	}


}

void Entity::EndTurn()
{
	isMyTurn = false;
	m_actionList[CharacterSheet::AOO].legal = true;	
}

void Entity::TakeAOO()
{
	if (m_actionList[CharacterSheet::AOO].legal && isAdjacent())
	{
		if (CS.weapon == CharacterSheet::Longsword)
		{
			std::string tag = " ";
			tag[0] = opponent->tag;
			game->console.Log("Player " + tag + " triggered AOO!");
			if (game->PlayerTesting)
			{
				game->console.Log("Type 'Y' to take your attack, or 'N' to pass.");
				std::string input;
				std::cin >> input;
				if (input == "Y") { DoAction(m_actionList[CharacterSheet::AOO]); }
			}
			else
			{
				DoAction(m_actionList[CharacterSheet::AOO]);
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

void Entity::MeleeAttack(int _bonus)
{
	int D20 = Roll(20);
	int dmgMod = (int)floor(CS.STR * 1.5f);
	int dmgDice = 8;
	int damage = 0;

	if (game->PlayerTesting)
	{
		bool valid = false;
		while (!valid)
		{
			valid = true;
			system("CLS");
			if (this->tag == 'A')
			{
				game->DisplayStats();
				game->console.Log("Type !roll followed by the attack dice + modifier, followed by the damage dice + modifier.");
				game->console.Log("For example: !roll d20+10 d6+5");
				try
				{
					std::string input;
					std::getline(std::cin, input);
					
					while (input == "")
					{
						std::getline(std::cin, input);
					}
					game->console.SecretLog(input);

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
					D20 = Roll(std::stoi(d));
					_bonus = std::stoi(hm);
					dmgMod = std::stoi(dm);
					dmgDice = std::stoi(dd);
					system("CLS");
					game->console.Log("You rolled: " + std::to_string(D20));
				}
				catch(std::exception e)
				{
					valid = false;
					game->console.Log("Invalid Input");
					system("PAUSE");
				}
			}
		}
	}
	

	if (D20 >= 19)
	{
		int confirm = Roll(20);
		if (game->PlayerTesting && this->tag == 'A')
		{
			game->console.Log("Confirmation Roll: " + std::to_string(confirm));
		}

		if (confirm + _bonus >= opponent->CS.AC)
		{			
			damage = (Roll(dmgDice) + dmgMod) + (Roll(dmgDice) + dmgMod);
			opponent->CS.HP -= damage;			
			game->console.Log("(CRIT)");
		}
		else
		{
			damage = (Roll(dmgDice) + dmgMod);
			opponent->CS.HP -= damage;
			game->console.Log("(Hit)");
		}
	}
	else if (D20 + _bonus >= opponent->CS.AC)
	{
		damage = (Roll(dmgDice) + dmgMod);
		opponent->CS.HP -= damage;
		game->console.Log("(Hit)");
	}
	else
	{
		game->console.Log("(Miss)");
	}

	if (game->PlayerTesting)
	{
		if (this->tag == 'A')
		{
			game->console.Log("(You dealt: " + std::to_string(damage) + " damage!)");
		}
		else
		{
			game->console.Log("(You took: " + std::to_string(damage) + " damage!)");
		}
		system("PAUSE");
	}
}

void Entity::RangedAttack(int _bonus)
{
	int D20 = Roll(20);
	int dmgMod = 0;
	int dmgDice = 8;
	int damage = 0;
	
	if (game->PlayerTesting)
	{		
		bool valid = false;
		while (!valid)
		{
			valid = true;
			system("CLS");
			if (this->tag == 'A')
			{
				game->DisplayStats();
				game->console.Log("Type !roll followed by the attack dice + modifier, followed by the damage dice + modifier.");
				game->console.Log("For example: !roll d20+10 d6+5");

				try
				{
					std::string input;
					std::getline(std::cin, input);
					while (input == "")
					{
						std::getline(std::cin, input);
					}
					game->console.SecretLog(input);
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
					D20 = Roll(std::stoi(d));
					_bonus = std::stoi(hm);
					dmgMod = std::stoi(dm);
					dmgDice = std::stoi(dd);
					system("CLS");
					game->console.Log("You rolled: " + std::to_string(D20));
				}
				catch (std::exception e)
				{
					valid = false;
					game->console.Log("Invalid Input");
					system("PAUSE");
				}
			}
		}
	}


	if (D20 > 19)
	{
		int confirm = Roll(20);
		if (game->PlayerTesting && this->tag == 'A')
		{
			game->console.Log("Confirmation Roll: " + std::to_string(confirm));
		}

		if (confirm + _bonus >= opponent->CS.AC)
		{
			damage = (Roll(dmgDice) + dmgMod) + (Roll(dmgDice) + dmgMod) + (Roll(dmgDice) + dmgMod);
			opponent->CS.HP -= damage;
			game->console.Log("(CRIT)");
		}
		else
		{
			damage = (Roll(dmgDice) + dmgMod);
			opponent->CS.HP -= damage;
			game->console.Log("(Hit)");
		}
	}
	else if (D20 + _bonus >= opponent->CS.AC)
	{
		damage = (Roll(dmgDice) + dmgMod);
		opponent->CS.HP -= damage;
		game->console.Log("(Hit)");
	}
	else
	{
		game->console.Log("(Miss)");
	}

	if (game->PlayerTesting)
	{
		if (this->tag == 'A')
		{
			game->console.Log("(You dealt: " + std::to_string(damage) + " damage!)");
		}
		else
		{
			game->console.Log("(You took: " + std::to_string(damage) + " damage!)");
		}
		system("PAUSE");
	}
}

int Entity::Roll(int _dice)
{
	return (rand() % _dice) + 1;
}

bool Entity::isAdjacent()
{	
	if (opponent->m_Pos == m_Pos + glm::vec2(0, game->boxSize))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos + glm::vec2(0, -game->boxSize))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos + glm::vec2(game->boxSize, 0))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos + glm::vec2(-game->boxSize, 0))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos + glm::vec2(game->boxSize, game->boxSize))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos + glm::vec2(game->boxSize, -game->boxSize))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos + glm::vec2(-game->boxSize, -game->boxSize))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos + glm::vec2(-game->boxSize, game->boxSize))
	{
		return true;
	}
	else if (opponent->m_Pos == m_Pos)
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

bool Entity::HitBoundingBox(float minB[], float maxB[], float origin[],  float dir[], float coord[])

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

bool Entity::HasStraightLine()
{	
	for (int i = 0; i < game->map.m_walls.size(); i++)
	{
		if (game->map.m_walls[i]->m_Pos == m_Pos / game->boxSize)
		{
			return false;
		}

		if (game->map.m_walls[i]->m_Pos.x != 0.0f && game->map.m_walls[i]->m_Pos.x != game->map.m_gridX - 1 && game->map.m_walls[i]->m_Pos.y != game->map.m_gridX - 1 && game->map.m_walls[i]->m_Pos.y != 0.0f			)
		{
			float minB[2] = { game->map.m_walls[i]->m_Pos.x, game->map.m_walls[i]->m_Pos.y };
			float maxB[2] = { game->map.m_walls[i]->m_Pos.x + 1.0f, game->map.m_walls[i]->m_Pos.y + 1.0f };
			float origin[2] = { (m_Pos.x / game->boxSize) + 0.5f, (m_Pos.y / game->boxSize) + 0.5f };
			glm::vec2 dir = glm::normalize(m_Pos - opponent->m_Pos);
			float ray[2] = { -dir.x, -dir.y };
			float coord[2] = { 0.0f, 0.0f };
			if (HitBoundingBox(minB, maxB, origin, ray, coord))
			{
				glm::vec2 hitPos = glm::vec2(coord[0], coord[1]);
				if (glm::distance(m_Pos / game->boxSize, hitPos) < glm::distance(m_Pos / game->boxSize, opponent->m_Pos / game->boxSize))
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Entity::AdjustPosition(std::string _route)
{
	for (int i = 0; i < _route.size(); i++)
	{
		switch (_route[i])
		{
			case '1': //Left
				m_Pos.x-= game->boxSize;
				break;
			case '2': // Right
				m_Pos.x+= game->boxSize;
				break;
			case '3': // Up
				m_Pos.y-= game->boxSize;
				break;
			case '4': // Down
				m_Pos.y+= game->boxSize;
				break;



			case '5':
				m_Pos.y-= game->boxSize;
				m_Pos.x-= game->boxSize;
				break;
			case '6':
				m_Pos.y+= game->boxSize;
				m_Pos.x-= game->boxSize;
				break;

			case '7':
				m_Pos.y+= game->boxSize;
				m_Pos.x+= game->boxSize;
				break;

			case '8':
				m_Pos.y-= game->boxSize;
				m_Pos.x+= game->boxSize;
				break;
		}
	}
}

glm::vec2 Entity::findLOS()
{
	glm::ivec2 startPos = m_Pos;
	glm::ivec2 bestPos = glm::vec2(0, 0);

	for (int x = 1; x < game->map.m_gridX-1; x++)
	{
		for (int y = 1; y < game->map.m_gridY-1; y++)
		{
			m_Pos = glm::vec2(x * game->boxSize, y * game->boxSize);
			if (!isAdjacent())
			{
				if (HasStraightLine())
				{
					m_Pos = startPos;
					std::string route = findPath(game->map, this, x, y);
					if (route.size() > 0 && route.size() <= 6)
					{
						if (glm::distance(glm::vec2(x * game->boxSize, y * game->boxSize), opponent->m_Pos) >= glm::distance(m_Pos, opponent->m_Pos))
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

	m_Pos = glm::vec2(startPos.x + game->boxSize, startPos.y);
	if (!isAdjacent() && HasStraightLine()) 
	{ 
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true; 
	}

	m_Pos = glm::vec2(startPos.x - game->boxSize, startPos.y);
	if (!isAdjacent() && HasStraightLine()) {
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x, startPos.y - game->boxSize);
	if (!isAdjacent() && HasStraightLine()) {
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}
	m_Pos = glm::vec2(startPos.x, startPos.y + game->boxSize);
	if (!isAdjacent() && HasStraightLine()) {
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x - game->boxSize, startPos.y - game->boxSize);
	if (!isAdjacent() && HasStraightLine()) {
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x + game->boxSize, startPos.y - game->boxSize);
	if (!isAdjacent() && HasStraightLine()) {
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x + game->boxSize, startPos.y + game->boxSize);
	if (!isAdjacent() && HasStraightLine()) {
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = glm::vec2(startPos.x - game->boxSize, startPos.y + game->boxSize);
	if (!isAdjacent() && HasStraightLine()) {
		fiveFtBackSquare = m_Pos;
		m_Pos = startPos;
		return true;
	}

	m_Pos = startPos;
	return false;
}
