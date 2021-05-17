#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "MapLoader.h"
#include "Entity.h"

BattleMap BattleMap::loadFromFile(std::string _path)
{
	std::vector<char> mapChars;
	std::vector<std::string> mapVals;
	std::ifstream file;
	std::vector<int> mapInt;
	file.open(_path);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string t;
			std::getline(file, t, ' '); 
			mapVals.push_back(t);
		}
	}
	else { throw std::exception(); }
	file.close();

	for (int i = 0; i < mapVals.size(); i++)
	{
		int t = cutString(mapVals[i]);
		mapInt.push_back(t);	
	}	
	
	BattleMap map(mapInt[0], mapInt[1]); //Create the map

	//Fill the map with walls
	int i = 2; // (Ignores the X and Y spaces on the map, saved in spaces 0-1 in the array)
	for (int y = 0; y < mapInt[1]; y++) 
	{
		for (int x = 0; x < mapInt[0]; x++) 
		{
			switch (mapInt[i])
			{
			case 1:
				map.m_block.push_back(new Entity(x, y)); //Create a new wall object
				break;			

			default:
				break;
			}
			i++;
		}
	}
	return map;
}

//Cuts any non-character values from the string, returns the int
int BattleMap::cutString(std::string _str)
{
	std::string num;	

	for (int i = 0; i < _str.size(); i++)
	{
		switch (_str[i])
		{
		case '1': 
			num.push_back(_str[i]);
			break;
		case '2':
			num.push_back(_str[i]);
			break;
		case '3':
			num.push_back(_str[i]);
			break;
		case '4':
			num.push_back(_str[i]);
			break;
		case '5':
			num.push_back(_str[i]);
			break;
		case '6':
			num.push_back(_str[i]);
			break;
		case '7':
			num.push_back(_str[i]);
			break;
		case '8':
			num.push_back(_str[i]);
			break;
		case '9':
			num.push_back(_str[i]);
			break;
		case '0':
			num.push_back(_str[i]);
			break;

		default: 
			break;
		}
	}
	
	return std::stoi(num);
}
