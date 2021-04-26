#pragma once
#include <vector>
//#include "Game.h"

class Game;

struct Neuron
{
	std::vector<float> inputWeights;
	float activationThreshold;
	float output;
	float rawOutput;

	float error;
};

struct Layer
{
	std::vector<Neuron> node;
};

struct Inputs
{
	//const int numInputs = 11;

	//Our stats
	int distance;
	int weapon;
	int meleeAttBonus;
	int rangedAttBonus;
	int AC;

	//Their stats
	int enemyMeleeAttBonus;
	int enemyRangedAttBonus;
	int enemyAC;

	//Legal action notation
	int rangedLegal;
	int chargeLegal;	
	int fiveFtBkLegal;
};

struct NeuralNetwork
{
	//Functions
	NeuralNetwork(std::vector<std::vector<std::vector<float>>> _weights, float _activation);
	NeuralNetwork(std::string _path);
	NeuralNetwork() {};
	std::vector<int> makeDecision(Inputs* _inputs);	
	void Save();

	void Load(std::string _path);

	//This is the whole network
	std::vector<Layer> layers;
	float activation;
	int numInputs = 0;
	
	//Save variables
	bool player = false;
	int tick = 999;
	const float alpha = 0.01f;
	Game* game;
};
