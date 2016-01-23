#ifndef _COMMAND_HPP
#define _COMMAND_HPP
#include "stdafx.h"
#include "cLog.hpp"
#include "Player.hpp"

class Command {
public:
	virtual ~Command()	{	}
	virtual void execute(Player* p) = 0;
protected:
	Command()	{	}
};

class JumpCommand : public Command {
public:
	void execute(Player* p) {
		p->jump();
		cLog::inst()->print(0, "Jump Command", "Jump was called using the command pattern");
	}
};

class FireCommand : public Command {
public:
	void execute(Player* p) {
		cLog::inst()->print(0, "Fire Command", "Fire was called using the command pattern");
	}
};

class SwapCommand : public Command {
public:
	void execute(Player* p) {
		cLog::inst()->print(0, "Swap Command", "Swap was called using the command pattern");
	}
};

class LurchCommand : public Command {
public:
	void execute(Player* p) {
		cLog::inst()->print(0, "Lurch Command", "Lurch was called using the command pattern");
	}
};

class NULLCommand : public Command {
public:
	void execute(Player* p) 	{	}
};

#endif