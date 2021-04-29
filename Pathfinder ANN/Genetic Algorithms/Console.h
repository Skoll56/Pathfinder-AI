#pragma once

#include <string>
#include <iostream>
#include <vector>

struct Console
{
	Console();
	void Log(std::string _message);
	void SecretLog(std::string _message);
	void Clear();
	void Save(std::string _path);

	std::vector<std::string> messageLog;
	int index = 0;
	const int maxSize = 50;
	bool output = true;
};
