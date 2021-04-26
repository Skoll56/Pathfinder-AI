#pragma once
#include "ANN.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <SDL2/SDL.h>
#include "Sheet.h"
#include "Game.h"
#include <direct.h>

NeuralNetwork::NeuralNetwork(std::vector<std::vector<std::vector<float>>> _weights, float _activation)
{
	//Weights[0] <-- Layer Number
	//Weights[0][0] <-- Neuron number
	//Weights[0][0][0] <-- Connection number

	layers.clear();	
	layers.resize(_weights.size());
	activation = _activation;
	numInputs = _weights[0].size();

	for (int i = 0; i < layers.size(); i++)
	{
		layers[i].node.clear();
		layers[i].node.resize(_weights[i].size());

		for (int l = 0; l < _weights[i].size(); l++)
		{
			layers[i].node[l].inputWeights.clear();
			if (i != 0)
			{
				layers[i].node[l].inputWeights.resize(_weights[i - 1].size());
			}
			layers[i].node[l].activationThreshold = _activation + ((float)(rand() % 6) - 8.0f) / 10.0f;

			for (int j = 0; j < _weights[i][l].size(); j++)
			{
				layers[i].node[l].inputWeights[j] = _weights[i][l][j];
			}
		}	
	}
}

NeuralNetwork::NeuralNetwork(std::string _path)
{
	//Weights[0] <-- Layer Number
	//Weights[0][0] <-- Neuron number
	//Weights[0][0][0] <-- Connection number

	layers.clear();
	Load(_path);
}

std::vector<int> NeuralNetwork::makeDecision(Inputs* _input)
{
	layers[0].node[0].output = _input->AC;
	layers[0].node[1].output = _input->chargeLegal;
	layers[0].node[2].output = _input->distance;
	layers[0].node[3].output = _input->enemyAC;
	layers[0].node[4].output = _input->enemyMeleeAttBonus;
	layers[0].node[5].output = _input->enemyRangedAttBonus;
	layers[0].node[6].output = _input->meleeAttBonus;
	layers[0].node[7].output = _input->rangedAttBonus;
	layers[0].node[8].output = _input->rangedLegal;
	layers[0].node[9].output = _input->weapon;
	layers[0].node[10].output = _input->fiveFtBkLegal;
	
	float ErrorSum = 1.0f;
	int outLayer = layers.size() - 1;
	std::vector<int> output(layers[outLayer].node.size());
	int attempts = 0;

	/* THIS IS USED FOR TRAINING ONLY*/
	//This forces the AI to keep re-trying until it gets the perfect answer
	//while (fabs(ErrorSum) > 0.2f) 
	/* Comment out this line when training is finished */
	{
		attempts++;
		///Decision phase
		for (int i = 1; i < layers.size(); i++) //Only start the "web" from layer 1, not 0 (input layer)
		{
			for (int l = 0; l < layers[i].node.size(); l++)
			{
				float sumValue = 0.0f;
				for (int j = 0; j < layers[i].node[l].inputWeights.size(); j++)
				{
					float w = layers[i].node[l].inputWeights[j];
					float in = layers[i - 1].node[j].output;
					sumValue += w * in;
				}

				//float sigmoid = 1.0f / (1.0f + powf(1.71828f, -(sumValue - activation))); //WRONG
				float sigmoid = 1.0f / (1.0f + powf(1.71828f, -(sumValue - layers[i].node[l].activationThreshold)));

				layers[i].node[l].rawOutput = sumValue;
				layers[i].node[l].output = sigmoid;				
			}
		}
		for (int i = 0; i < output.size(); i++) 
		{
			if (layers[outLayer].node[i].output > 0.85f)
			{
				output[i] = 1;
			}
			else
			{
				output[i] = 0;
			}
		}
		std::vector<float> expectedOutput(output.size());

		///Determining the desired output
		//Determine the desired action in the current circumstance
		if (_input->distance <= 2.0f)
		{
			if (_input->weapon == CharacterSheet::Weapon::Longsword)
			{
				if (_input->enemyAC <= _input->meleeAttBonus + 7)
				{
					expectedOutput[CharacterSheet::AttackDefensively] = 1.0f;
					expectedOutput[CharacterSheet::FullAttackDefensively] = 1.0f;
				}
				else
				{
					expectedOutput[CharacterSheet::FullMeleeAttack] = 1.0f;
					expectedOutput[CharacterSheet::MeleeAttack] = 1.0f;
				}
			}
			else if (_input->weapon = CharacterSheet::Weapon::Longbow)
			{
				if (_input->distance <= 1.0f && _input->fiveFtBkLegal)
				{
					expectedOutput[CharacterSheet::RangedAttack] = 1.0f;
					expectedOutput[CharacterSheet::FullRangedAttack] = 1.0f;
				}
				else
				{
					expectedOutput[CharacterSheet::Draw] = 1.0f;
					if (_input->enemyAC <= _input->meleeAttBonus + 7)
					{
						expectedOutput[CharacterSheet::AttackDefensively] = 1.0f;
					}
					else
					{
						
						expectedOutput[CharacterSheet::MeleeAttack] = 1.0f;
					}
				}
			}

		}
		else
		{
			if (_input->chargeLegal && _input->weapon == CharacterSheet::Weapon::Longsword)
			{
				expectedOutput[CharacterSheet::Charge] = 1.0f;
			}
			else if (_input->weapon == CharacterSheet::Weapon::Longbow && _input->rangedLegal)
			{
				expectedOutput[CharacterSheet::RangedAttack] = 1.0f;
				expectedOutput[CharacterSheet::FullRangedAttack] = 1.0f;
			}
			else if (_input->weapon == CharacterSheet::Weapon::Longbow)
			{
				expectedOutput[CharacterSheet::MoveForRanged] = 1.0f;
			}
			else
			{
				expectedOutput[CharacterSheet::MoveForMelee] = 1.0f;
				if (_input->enemyAC <= _input->meleeAttBonus + 7)
				{
					expectedOutput[CharacterSheet::AttackDefensively] = 1.0f;
				}
				else
				{

					expectedOutput[CharacterSheet::MeleeAttack] = 1.0f;
				}
			}
		}

		///Begin Training
		//Reset all the error values
		for (int i = 0; i < layers.size(); i++)
		{
			for (int l = 0; l < layers[i].node.size(); l++)
			{
				layers[i].node[l].error = 0.0f;
			}
		}

		//Determine the error value of the output layer
		int outlayer = layers.size() - 1;
		ErrorSum = 0.0f;
		for (int i = 0; i < layers[outlayer].node.size(); i++)
		{
			float error = expectedOutput[i] - layers[outlayer].node[i].output;
			float sError = layers[outlayer].node[i].output * (1.0f - layers[outlayer].node[i].output) * error;
			if (fabs(error) > 0.05f && fabs(sError) < 0.05f)
			{
				if (sError < 0)
				{
					layers[outlayer].node[i].error = -0.05f;
				}
				else
				{
					layers[outlayer].node[i].error = 0.05f;
				}
			}
			else
			{
				layers[outlayer].node[i].error = sError;
			}				

			ErrorSum += fabs(error);
		}

		//Backpropogate and adjust all the weights
		for (int i = layers.size()-1; i > 0; i--)
		{
			for (int l = 0; l < layers[i].node.size(); l++)
			{
				layers[i].node[l].activationThreshold += alpha * -1.0f * layers[i].node[l].error;
				for (int j = 0; j < layers[i].node[l].inputWeights.size(); j++) //J also represents the output of the previous layer
				{
					layers[i].node[l].inputWeights[j] += alpha * layers[i - 1].node[j].output * layers[i].node[l].error;
					float error = layers[i].node[l].inputWeights[j] * layers[i].node[l].error;
					float sError = layers[i].node[l].output * (1.0f - layers[i].node[l].output) * error;
					layers[i - 1].node[j].error += sError;
				}
			}
		}

		///Count the ticks for saving the ANN
		tick++;
		if (tick == 1000 && !game->PlayerTesting)
		{
			Save();
			tick = 0;
		}
	}
	if (!game->PlayerTesting)
	{
		game->console.Log("(Attempts: " + std::to_string(attempts) + ")");
	}
	return output;	
}


void NeuralNetwork::Save()
{
	int numLayers = layers.size() -1; //Don't count the input layer, there's no point in saving and loading that
	int nodesPerLayer = layers[1].node.size(); // We only want the number of middle nodes
	int numOutputs = layers[layers.size() - 1].node.size(); // Number of output nodes (the final layer)

	std::string saveFile = "";
	saveFile += std::to_string(numLayers) + "-";
	saveFile += std::to_string(nodesPerLayer) + "-";
	saveFile += std::to_string(numOutputs) + "-";
	saveFile += std::to_string(numInputs) + "-";
	saveFile += std::to_string(activation) + "-";


	for (int i = 1; i < layers.size(); i++)
	{
		for (int l = 0; l < layers[i].node.size(); l++)
		{
			saveFile += std::to_string(layers[i].node[l].activationThreshold) + ",";
			for (int j = 0; j < layers[i].node[l].inputWeights.size(); j++)
			{
				saveFile += std::to_string(layers[i].node[l].inputWeights[j]) + ",";
			}
		}
	}
	std::string folderTag;
	if (player) { folderTag = "/player/"; }
	else  { folderTag = "/npc/"; }

	std::string directory = "ANN Files";
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%F--%H-%M-%S", &tstruct);
	std::string timeStamp = std::string(buf);	
	_mkdir((directory + folderTag).c_str());
	std::string fullPath = directory + folderTag + timeStamp + ".ann";
	std::ofstream File(fullPath);

	if (!File)
	{
		throw std::exception();
	}

	File << saveFile;
	File.close();
}

std::string readUntil(std::string& _string, int &_i, char _delim)
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

void NeuralNetwork::Load(std::string _path)
{
	std::ifstream File(_path);
	if (!File)
	{
		throw std::exception();
	}
	std::string str((std::istreambuf_iterator<char>(File)),	std::istreambuf_iterator<char>());
	File.close();
	std::vector<std::vector<std::vector<float>>> weights;
	std::vector<std::vector<float>> activations;
	
	int it = 0;	
	int numLayers = std::stoi(readUntil(str, it, '-'));
	int nodesPerLayer = std::stoi(readUntil(str, it, '-'));
	int numOutputs = std::stoi(readUntil(str, it, '-'));
	numInputs = std::stoi(readUntil(str, it, '-'));
	activation = std::stof(readUntil(str, it, '-'));
	
	weights.resize(numLayers + 1);
	activations.resize(numLayers + 1);
	weights[0].resize(numInputs); //0 is the input layer, it has no inputs or weights of its own
	
	for (int i = 1; i < weights.size() - 1; i++) //This initialises all the middle layers
	{
		weights[i].resize(nodesPerLayer);
		activations[i].resize(nodesPerLayer);

		for (int l = 0; l < weights[i].size(); l++)
		{
			activations[i][l] = std::stof(readUntil(str, it, ','));
			weights[i][l].resize(weights[i - 1].size());
			for (int j = 0; j < weights[i][l].size(); j++)
			{
				weights[i][l][j] = std::stof(readUntil(str, it, ','));
			}
		}
	}

	int outLayer = weights.size() - 1;
	weights[outLayer].resize(numOutputs);
	activations[outLayer].resize(numOutputs);
	for (int l = 0; l < weights[outLayer].size(); l++)
	{
		weights[outLayer][l].resize(nodesPerLayer);
		for (int j = 0; j < weights[outLayer][l].size(); j++)
		{
			weights[outLayer][l][j] = std::stof(readUntil(str, it, ','));
		}
	}

	layers.resize(weights.size());
	for (int i = 0; i < layers.size(); i++)
	{
		layers[i].node.clear();
		layers[i].node.resize(weights[i].size());

		for (int l = 0; l < weights[i].size(); l++)
		{
			layers[i].node[l].inputWeights.clear();
			if (i != 0)
			{
				layers[i].node[l].inputWeights.resize(weights[i - 1].size());
				layers[i].node[l].activationThreshold = activations[i][l];
			}
			

			for (int j = 0; j < weights[i][l].size(); j++)
			{
				layers[i].node[l].inputWeights[j] = weights[i][l][j];
			}
		}
	}
}

