#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <string>
#include <iostream>
#include <vector>

/** When writing messages to the console, it goes through this class first. Then messages are recorded, ready to be saved to file in a log. */
struct Console
{
	Console();
	/** \brief Logs a message to the console and outputs it*/
	void log(std::string _message);

	/** \brief Logs a message to the console but doesn't print it. Used to record the player's input in the log files during testing.*/
	void secretLog(std::string _message);

	/** \brief Wipes the array that holds all the log entries*/
	void clear();

	/** \brief Saves the current log entries to a file*/
	void save(std::string _path);

	/** \brief An array that holds all the console messages*/
	std::vector<std::string> m_messageLog;
	int m_index = 0;
	/** \brief Sets a max size for the message array to stop it re-allocating memory constantly*/
	const int m_maxSize = 50;

	/** \brief A manual override that disables printing any messages to console.*/
	bool m_output = true;
};

#endif
