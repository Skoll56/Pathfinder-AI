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

	m_layers.clear();	
	m_layers.resize(_weights.size());
	m_activation = _activation;
	m_numInputs = _weights[0].size();

	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i].m_node.clear();
		m_layers[i].m_node.resize(_weights[i].size());

		for (int l = 0; l < _weights[i].size(); l++)
		{
			m_layers[i].m_node[l].m_inputWeights.clear();
			if (i != 0)
			{
				m_layers[i].m_node[l].m_inputWeights.resize(_weights[i - 1].size());
			}
			m_layers[i].m_node[l].m_activationThreshold = _activation + ((float)(rand() % 6) - 8.0f) / 10.0f;

			for (int j = 0; j < _weights[i][l].size(); j++)
			{
				m_layers[i].m_node[l].m_inputWeights[j] = _weights[i][l][j];
			}
		}	
	}
}

NeuralNetwork::NeuralNetwork(std::string _path)
{
	//Weights[0] <-- Layer Number
	//Weights[0][0] <-- Neuron number
	//Weights[0][0][0] <-- Connection number

	m_layers.clear();
	load(_path);
}

std::vector<int> NeuralNetwork::makeDecision(Inputs* _input)
{
	m_layers[0].m_node[0].m_output = _input->m_AC;
	m_layers[0].m_node[1].m_output = _input->m_chargeLegal;
	m_layers[0].m_node[2].m_output = _input->m_distance;
	m_layers[0].m_node[3].m_output = _input->m_enemyAC;
	m_layers[0].m_node[4].m_output = _input->m_enemyMeleeAttBonus;
	m_layers[0].m_node[5].m_output = _input->m_enemyRangedAttBonus;
	m_layers[0].m_node[6].m_output = _input->m_meleeAttBonus;
	m_layers[0].m_node[7].m_output = _input->m_rangedAttBonus;
	m_layers[0].m_node[8].m_output = _input->m_rangedLegal;
	m_layers[0].m_node[9].m_output = _input->m_weapon;
	m_layers[0].m_node[10].m_output = _input->m_fiveFtBkLegal;
	
	float ErrorSum = 1.0f;
	int outLayer = m_layers.size() - 1;
	std::vector<int> output(m_layers[outLayer].m_node.size());
	int attempts = 0;

	/* THIS IS USED FOR TRAINING ONLY*/
	//This forces the AI to keep re-trying until it gets the perfect answer
	while (fabs(ErrorSum) > 0.2f) 
	/* Comment out this line when training is finished */
	{
		attempts++;
		///Decision phase
		for (int i = 1; i < m_layers.size(); i++) //Only start the "web" from layer 1, not 0 (input layer)
		{
			for (int l = 0; l < m_layers[i].m_node.size(); l++)
			{
				float sumValue = 0.0f;
				for (int j = 0; j < m_layers[i].m_node[l].m_inputWeights.size(); j++)
				{
					float w = m_layers[i].m_node[l].m_inputWeights[j];
					float in = m_layers[i - 1].m_node[j].m_output;
					sumValue += w * in;
				}

				//float sigmoid = 1.0f / (1.0f + powf(1.71828f, -(sumValue - activation))); //WRONG
				float sigmoid = 1.0f / (1.0f + powf(1.71828f, -(sumValue - m_layers[i].m_node[l].m_activationThreshold)));

				m_layers[i].m_node[l].m_rawOutput = sumValue;
				m_layers[i].m_node[l].m_output = sigmoid;				
			}
		}
		for (int i = 0; i < output.size(); i++) 
		{
			if (m_layers[outLayer].m_node[i].m_output > 0.85f)
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
		if (_input->m_distance <= 2.0f)
		{
			if (_input->m_weapon == CharacterSheet::Weapon::Longsword)
			{
				if (_input->m_enemyAC <= _input->m_meleeAttBonus + 7)
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
			else if (_input->m_weapon = CharacterSheet::Weapon::Longbow)
			{
				if (_input->m_distance <= 1.0f && _input->m_fiveFtBkLegal)
				{
					expectedOutput[CharacterSheet::RangedAttack] = 1.0f;
					expectedOutput[CharacterSheet::FullRangedAttack] = 1.0f;
				}
				else
				{
					expectedOutput[CharacterSheet::Draw] = 1.0f;
					if (_input->m_enemyAC <= _input->m_meleeAttBonus + 7)
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
			if (_input->m_chargeLegal && _input->m_weapon == CharacterSheet::Weapon::Longsword)
			{
				expectedOutput[CharacterSheet::Charge] = 1.0f;
			}
			else if (_input->m_weapon == CharacterSheet::Weapon::Longbow && _input->m_rangedLegal)
			{
				expectedOutput[CharacterSheet::RangedAttack] = 1.0f;
				expectedOutput[CharacterSheet::FullRangedAttack] = 1.0f;
			}
			else if (_input->m_weapon == CharacterSheet::Weapon::Longbow)
			{
				expectedOutput[CharacterSheet::MoveForRanged] = 1.0f;
			}
			else
			{
				expectedOutput[CharacterSheet::MoveForMelee] = 1.0f;
				if (_input->m_enemyAC <= _input->m_meleeAttBonus + 7)
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
		for (int i = 0; i < m_layers.size(); i++)
		{
			for (int l = 0; l < m_layers[i].m_node.size(); l++)
			{
				m_layers[i].m_node[l].m_error = 0.0f;
			}
		}

		//Determine the error value of the output layer
		int outlayer = m_layers.size() - 1;
		ErrorSum = 0.0f;
		for (int i = 0; i < m_layers[outlayer].m_node.size(); i++)
		{
			if (m_layers[outlayer].m_node[i].m_output == 1.0f || m_layers[outlayer].m_node[i].m_output == 0.0f || m_layers[outlayer].m_node[i].m_output == -1.0f)
			{
				m_layers[outlayer].m_node[i].m_output += 0.012564f;
			}

			float error = expectedOutput[i] - m_layers[outlayer].m_node[i].m_output;
			float sError = m_layers[outlayer].m_node[i].m_output * (1.0f - m_layers[outlayer].m_node[i].m_output) * error;
			if (fabs(error) > 0.05f && fabs(sError) < 0.05f)
			{
				if (sError < 0)
				{
					m_layers[outlayer].m_node[i].m_error = -0.05f;
				}
				else
				{
					m_layers[outlayer].m_node[i].m_error = 0.05f;
				}
			}
			else
			{
				m_layers[outlayer].m_node[i].m_error = sError;
			}				

			ErrorSum += fabs(error);
		}

		//Backpropogate and adjust all the weights
		for (int i = m_layers.size()-1; i > 0; i--)
		{
			for (int l = 0; l < m_layers[i].m_node.size(); l++)
			{
				m_layers[i].m_node[l].m_activationThreshold += m_alpha * -1.0f * m_layers[i].m_node[l].m_error;
				for (int j = 0; j < m_layers[i].m_node[l].m_inputWeights.size(); j++) //J also represents the output of the previous layer
				{
					m_layers[i].m_node[l].m_inputWeights[j] += m_alpha * m_layers[i - 1].m_node[j].m_output * m_layers[i].m_node[l].m_error;
					float error = m_layers[i].m_node[l].m_inputWeights[j] * m_layers[i].m_node[l].m_error;
					float sError = m_layers[i - 1].m_node[j].m_output * (1.0f - m_layers[i - 1].m_node[j].m_output) * error;
					m_layers[i - 1].m_node[j].m_error += sError;
				}
			}
		}

		///Count the ticks for saving the ANN
		m_tick++;
		if (m_tick > 500 && !m_game->m_playerTesting)
		{
			save();
			m_tick = 0;
		}
	}
	if (!m_game->m_playerTesting)
	{
		m_game->m_console.log("(Attempts: " + std::to_string(attempts) + ")");
	}
	return output;	
}


void NeuralNetwork::save()
{
	int numLayers = m_layers.size() -1; //Don't count the input layer, there's no point in saving and loading that
	int nodesPerLayer = m_layers[1].m_node.size(); // We only want the number of middle nodes
	int numOutputs = m_layers[m_layers.size() - 1].m_node.size(); // Number of output nodes (the final layer)

	std::string saveFile = "";
	saveFile += std::to_string(numLayers) + "-";
	saveFile += std::to_string(nodesPerLayer) + "-";
	saveFile += std::to_string(numOutputs) + "-";
	saveFile += std::to_string(m_numInputs) + "-";
	saveFile += std::to_string(m_activation) + "-";


	for (int i = 1; i < m_layers.size(); i++)
	{
		for (int l = 0; l < m_layers[i].m_node.size(); l++)
		{
			saveFile += std::to_string(m_layers[i].m_node[l].m_activationThreshold) + ",";
			for (int j = 0; j < m_layers[i].m_node[l].m_inputWeights.size(); j++)
			{
				saveFile += std::to_string(m_layers[i].m_node[l].m_inputWeights[j]) + ",";
			}
		}
	}
	std::string folderTag;
	if (m_player) { folderTag = "/player/"; }
	else  { folderTag = "/npc/"; }

	std::string directory = "Files";
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

void NeuralNetwork::load(std::string _path)
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
	m_numInputs = std::stoi(readUntil(str, it, '-'));
	m_activation = std::stof(readUntil(str, it, '-'));
	
	weights.resize(numLayers + 1);
	activations.resize(numLayers + 1);
	weights[0].resize(m_numInputs); //0 is the input layer, it has no inputs or weights of its own
	
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

	m_layers.resize(weights.size());
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i].m_node.clear();
		m_layers[i].m_node.resize(weights[i].size());

		for (int l = 0; l < weights[i].size(); l++)
		{
			m_layers[i].m_node[l].m_inputWeights.clear();
			if (i != 0)
			{
				m_layers[i].m_node[l].m_inputWeights.resize(weights[i - 1].size());
				m_layers[i].m_node[l].m_activationThreshold = activations[i][l];
			}
			

			for (int j = 0; j < weights[i][l].size(); j++)
			{
				m_layers[i].m_node[l].m_inputWeights[j] = weights[i][l][j];
			}
		}
	}
}

