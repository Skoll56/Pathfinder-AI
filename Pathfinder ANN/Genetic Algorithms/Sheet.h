#pragma once
#include <vector>
#include <string>

struct CharacterSheet
{
	enum Weapon
	{
		Longsword = 0,
		Longbow = 1
	};

	enum ActionLength
	{
		Standard,
		Move,
		FullRound,
		Free,
		Immediate,
		Step
	};

	enum ActionName
	{
		MeleeAttack,
		RangedAttack,
		FullMeleeAttack,
		FullRangedAttack,
		FiveFtStepBack,
		FiveFtStepFwd,
		AttackDefensively,
		FullAttackDefensively,
		TotalDefence,
		MoveForMelee,
		MoveForRanged,
		Draw,
		Charge,
		AOO,
		EndTurn
	};


	//Stats
	int BAB;	
	int MoveSpeed;
	int AC;
	int FFAC;
	int TAC;
	int DEX;
	int STR;
	int HP;
	int INIT;

	//Modifiers
	int ACbonus;
	int attackBonus;

	Weapon weapon;	
};

struct Action
{
	CharacterSheet::ActionName name;
	CharacterSheet::ActionLength slot;
	bool provokes = false;	
	bool legal = true;
	std::string stringName;
};


