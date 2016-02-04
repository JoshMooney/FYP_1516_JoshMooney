#pragma once
#ifndef CLOG_HPP
#define CLOG_HPP

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class cLog {
private:
	cLog()	{	};
	static cLog* m_instance;

public:
	~cLog() { delete m_instance; };
	static cLog* inst() {
		if (m_instance == NULL)
			m_instance = new cLog();
		return m_instance;
	}
	/**
	Print message using the cLoggers cout function.
	@param message - the message being printed
	@return void
	*/
	void print(string message) {
		cout << message << endl;
	}
	void debug(string from, int i) {
		cout << from << ": " << i << endl;
	}
	void debug(string from, float i) {
		cout << from << ": " << i << endl;
	}
	void newline(){
		cout << endl;
	}
	/**
	Print message using the cLoggers cout function.
	@param priority - between 1-3 how important the message 1 being urgent and 3 being meh
	@param from - the class or function the message came from
	@param message - the message being printed
	@return void
	*/
	void print(int priority, string from, string message ) {
		cout << "| " << priority << " | " << from << " | " << message << " |" << endl;
	}
};

#endif
