#ifndef _COMMAND_HPP
#define _COMMAND_HPP
#include "stdafx.h"
#include "cLog.hpp"
#include "Player.hpp"

/**
*	@class Command
*	@brief This is the base command class that each of the sub commands 
*	should inherite from and each of which must overload the execute function. 
*/
class Command {
public:
	virtual ~Command()	{	}
	/**
	*	@brief This function executes the task issued to the command.
	*	@param Player This is the object to execute the command on
	*/
	virtual void execute(Player* p) = 0;
protected:
	Command()	{	}
};

/**
*	@class JumpCommand
*	@brief This is a sub class of the command base class. This class should
*	override the execute command and this command calls the Jump function.
*/
class JumpCommand : public Command {
public:
	/**
	*	@brief This function executes the task issued to the command.
	*	@param Player This is the object to execute the command on
	*/
	void execute(Player* p) {
		p->jump();
		cLog::inst()->print(0, "Jump Command", "Jump was called using the command pattern");
	}
};

/**
*	@class AttackCommand
*	@brief This is a sub class of the command base class. This class should
*	override the execute command and this command calls the Fire function.
*/
class AttackCommand : public Command {
public:
	/**
	*	@brief This function executes the task issued to the command.
	*	@param Player This is the object to execute the command on
	*/
	void execute(Player* p) {
		p->attack();
		cLog::inst()->print(0, "AttackCommand", "Fire was called using the command pattern");
	}
};

/**
*	@class InteractCommand
*	@brief This is a sub class of the command base class. This class should
*	override the execute command and this command calls the Swap function.
*/
class InteractCommand : public Command {
public:
	/**
	*	@brief This function executes the task issued to the command.
	*	@param Player This is the object to execute the command on
	*/
	void execute(Player* p) {
		//cLog::inst()->print(0, "InteractCommand", "Swap was called using the command pattern");
	}
};

/**
*	@class LurchCommand
*	@brief This is a sub class of the command base class. This class should
*	override the execute command and this command calls the Lurch function.
*/
class LurchCommand : public Command {
public:
	/**
	*	@brief This function executes the task issued to the command.
	*	@param Player This is the object to execute the command on
	*/
	void execute(Player* p) {
		cLog::inst()->print(0, "Lurch Command", "Lurch was called using the command pattern");
	}
};

/**
*	@class NULLCommand
*	@brief This is a sub class of the command base class. This class should
*	override the execute command and this command calls no function.
*/
class NULLCommand : public Command {
public:
	/**
	*	@brief This is a null command and should not execute anything
	*	@param Player This is the object to execute the command on
	*/
	void execute(Player* p) 	{	}
};

#endif