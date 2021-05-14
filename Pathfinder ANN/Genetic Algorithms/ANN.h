#pragma once
#include <vector>
//#include "Game.h"

class Game;

struct Neuron
{
	std::vector<float> m_inputWeights;
	float m_activationThreshold;
	float m_output;
	float m_rawOutput;
	float m_error;
};

struct Layer
{
	std::vector<Neuron> m_node;
};

struct Inputs
{
	//Our stats
	int m_distance;
	int m_weapon;
	int m_meleeAttBonus;
	int m_rangedAttBonus;
	int m_AC;

	//Their stats
	int m_enemyMeleeAttBonus;
	int m_enemyRangedAttBonus;
	int m_enemyAC;

	//Legal action notation
	int m_rangedLegal;
	int m_chargeLegal;	
	int m_fiveFtBkLegal;
};

struct NeuralNetwork
{
	//Functions
	NeuralNetwork(std::vector<std::vector<std::vector<float>>> _weights, float _activation);
	NeuralNetwork(std::string _path);
	NeuralNetwork() {};
	std::vector<int> makeDecision(Inputs* _inputs);	
	void save();
	void load(std::string _path);

	//This is the whole network
	std::vector<Layer> m_layers;

	//A global activation threshold (used for testing mostly, not being used right now)
	float m_activation;
	int m_numInputs = 0;

	//The learning rate of the ANN
	const float m_alpha = 0.0001f;
	
	//Save variables
	bool m_player = false;
	int m_tick = 999;	
	Game* m_game;
};
