#include "Console.h"
#include <time.h>
#include <fstream>


Console::Console()
{
	m_messageLog.clear();
	m_messageLog.resize(m_maxSize);
}

void Console::log(std::string _message)
{
	if (m_index < m_maxSize)
	{
		m_messageLog[m_index] = _message;		
	}
	else
	{
		m_messageLog.push_back(_message);
		//messageLog[index] = _message;
	}
	m_index++;

	if (m_output)
	{
		std::cout << _message << std::endl;
	}
}

void Console::secretLog(std::string _message)
{
	if (m_index < m_maxSize)
	{
		m_messageLog[m_index] = _message;
	}
	else
	{
		m_messageLog.push_back(_message);
		//messageLog[index] = _message;
	}
	m_index++;
}

void Console::clear()
{
	m_messageLog.clear();
	m_messageLog.resize(50);
	m_index = 0;
}

void Console::save(std::string _path)
{
	std::string directory =  _path;

	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%F--%H-%M-%S", &tstruct);
	std::string timeStamp = std::string(buf);
	std::string fullPath = directory + timeStamp + ".log";
	std::ofstream File(fullPath);

	if (!File)
	{
		throw std::exception();
	}

	std::string saveFile = "";
	for (int i = 0; i < m_messageLog.size(); i++)
	{
		saveFile += m_messageLog[i] + "\n";
	}
	File << saveFile;

	File.close();
}
