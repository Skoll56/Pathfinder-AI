#ifndef _ANN_H_
#define _ANN_H_

#include <vector>

class Game;

/**This struct represents one Neuron (node) */
struct Neuron
{
	/** \brief A list containing every input connection's weighting */
	std::vector<float> m_inputWeights;	
	float m_activationThreshold;

	/** \brief The output of this node after being modified by the sigmoid function */
	float m_output;

	/** \brief The output of this node before being modified by the sigmoid function */
	float m_rawOutput;

	/** \brief Holds the error value for this node during training*/
	float m_error;
};

/**This struct represents one Layer. It only holds a list of Neurons. */
struct Layer
{
	std::vector<Neuron> m_node;
};

/**This struct holds all of the input values that get fed to the ANN every time it needs to make a decision */
struct Inputs
{
	//Our stats
	/** \brief Distance to opponent*/
	int m_distance;
	/** \brief Weapon Held (Longsword 0, Longbow 1)*/
	int m_weapon;
	/** \brief Melee Weapon Attack Bonus*/
	int m_meleeAttBonus;
	/** \brief Ranged Weapon Attack Bonus*/
	int m_rangedAttBonus;
	/** \brief AC*/
	int m_AC;

	//Their stats
	int m_enemyMeleeAttBonus;
	int m_enemyRangedAttBonus;
	int m_enemyAC;

	//Legal action notation
	/** \brief Marks if a ranged attack is legal (0/1)*/
	int m_rangedLegal;
	/** \brief Marks if a charge is legal (0/1)*/
	int m_chargeLegal;	
	/** \brief Marks if there is an available square one can step to, outside of melee range (0/1)*/
	int m_fiveFtBkLegal;
};

/**This struct represents the entire Neural Network */
struct NeuralNetwork
{
	//Functions
	/** \brief Generates a new Neural Network*/
	NeuralNetwork(std::vector<std::vector<std::vector<float>>> _weights, float _activation);
	/** \brief Loads a Neural Network from file*/
	NeuralNetwork(std::string _path);
	NeuralNetwork() {};

	/** \brief Returns a list of outputs (0/1) representing which actions the ANN wants to take*/
	std::vector<int> makeDecision(Inputs* _inputs);	

	/** \brief Save the ANN to file*/
	void save();

	/** \brief Load the ANN to file*/
	void load(std::string _path);

	/** \brief Holds a reference to every layer in the ANN*/
	std::vector<Layer> m_layers;

	/** \brief A global activation value (no longer used)*/
	float m_activation;
	int m_numInputs = 0;

	/** \brief The learning rate of the ANN*/
	const float m_alpha = 0.11f;
	
	//Save variables
	bool m_player = false;

	/** \brief Tick is a counter of how many iterations the ANN does. After so many ticks, it saves.*/
	int m_tick = 999;	
	Game* m_game;
};

#endif