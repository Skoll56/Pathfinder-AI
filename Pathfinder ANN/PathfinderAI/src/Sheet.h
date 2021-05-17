#ifndef _SHEET_H_
#define _SHEET_H_

#include <vector>
#include <string>

/** This struct represents the character sheet*/
struct CharacterSheet
{
	enum Weapon
	{
		Longsword = 0,
		Longbow = 1
	};

	/** \brief Every action has a length, AKA, an action slot that it consumes. Represented in Enum form here.*/
	enum ActionLength
	{
		Standard,
		Move,
		FullRound,
		Free,
		Immediate,
		Step
	};

	/** \brief Every action in the game represented in enum form.*/
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
	/** \brief Base Attack Bonus*/
	int m_BAB;	
	/** \brief Movement Speed*/
	int m_moveSpeed;
	/** \brief Armour Class*/
	int m_AC;
	/** \brief Dexterity*/
	int m_DEX;
	/** \brief Strength*/
	int m_STR;
	/** \brief Hit Points*/
	int m_HP;
	/** \brief Initiative Modifier*/
	int m_INIT;

	//Modifiers
	/** \brief Any temporary AC bonuses (or penalties, such as from charging)*/
	int m_ACbonus;
	/** \brief Any temporary attack bonuses (such as from charging) or penalties*/
	int m_attackBonus;

	/** \brief Which weapon is being held*/
	Weapon m_weapon;	
};

/**A struct that holds every property of an action*/
struct Action
{
	/** \brief The name of the action*/
	CharacterSheet::ActionName m_name;

	/** \brief What slot the action uses*/
	CharacterSheet::ActionLength m_slot;

	/** \brief If the action provokes Attacks of Opportunity when taken*/
	bool m_provokes = false;	

	/** \brief If the action is currently legal*/
	bool m_legal = true;

	/** \brief The name of the action in string format (for printing to console)*/
	std::string m_stringName;
};


#endif