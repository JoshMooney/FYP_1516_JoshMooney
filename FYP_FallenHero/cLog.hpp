#pragma once
#ifndef CLOG_HPP
#define CLOG_HPP

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

/**
*	@class cLog
*	@brief This is the logger for printing the the screen on command. 
*/
class cLog {
private:
	cLog()	{	};
	static cLog* m_instance;

public:
	~cLog() { delete m_instance; };
	/**
	*	@brief This fetches the instance of the Logger
	*/
	static cLog* inst() {
		if (m_instance == NULL)
			m_instance = new cLog();
		return m_instance;
	}
	/**
	*	@brief Print message using the cLoggers cout function.
	*	@param message - the message being printed
	*/
	void print(string message) {
		cout << message << endl;
	}
	/**
	*	@brief
	*/
	void debug(string from, int i) {
		cout << from << ": " << i << endl;
	}
	/**
	*	@brief This prints a new line onto the cmd prompt
	*/
	void newline(){
		cout << endl;
	}
	/**
	*	@brief Print message using the cLoggers cout function.
	*	@param priority - between 1-3 how important the message 1 being urgent and 3 being meh
	*	@param from - the class or function the message came from
	*	@param message - the message being printed
	*/
	void print(int priority, string from, string message ) {
		cout << "| " << priority << " | " << from << " | " << message << " |" << endl;
	}
};

#endif
