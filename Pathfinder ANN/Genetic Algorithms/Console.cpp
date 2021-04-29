#include "Console.h"
#include <time.h>
#include <fstream>


Console::Console()
{
	messageLog.clear();
	messageLog.resize(maxSize);
}

void Console::Log(std::string _message)
{
	if (index < maxSize)
	{
		messageLog[index] = _message;		
	}
	else
	{
		messageLog.push_back(_message);
		//messageLog[index] = _message;
	}
	index++;

	if (output)
	{
		std::cout << _message << std::endl;
	}
}

void Console::SecretLog(std::string _message)
{
	if (index < maxSize)
	{
		messageLog[index] = _message;
	}
	else
	{
		messageLog.push_back(_message);
		//messageLog[index] = _message;
	}
	index++;
}

void Console::Clear()
{
	messageLog.clear();
	messageLog.resize(50);
	index = 0;
}

void Console::Save(std::string _path)
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
	for (int i = 0; i < messageLog.size(); i++)
	{
		saveFile += messageLog[i] + "\n";
	}
	File << saveFile;

	File.close();
}
