#pragma once

#include <string>
#include <iostream>
#include <vector>

struct Console
{
	Console();
	void log(std::string _message);
	void secretLog(std::string _message);
	void clear();
	void save(std::string _path);

	std::vector<std::string> m_messageLog;
	int m_index = 0;
	const int m_maxSize = 50;
	bool m_output = true;
};
