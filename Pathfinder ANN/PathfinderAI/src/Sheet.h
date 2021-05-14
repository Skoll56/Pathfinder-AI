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
	int m_BAB;	
	int m_moveSpeed;
	int m_AC;
	int m_DEX;
	int m_STR;
	int m_HP;
	int m_INIT;

	//Modifiers
	int m_ACbonus;
	int m_attackBonus;
	Weapon m_weapon;	
};

struct Action
{
	CharacterSheet::ActionName m_name;
	CharacterSheet::ActionLength m_slot;
	bool m_provokes = false;	
	bool m_legal = true;
	std::string m_stringName;
};


