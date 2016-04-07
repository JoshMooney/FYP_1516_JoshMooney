#ifndef _ACHIEVEMENTS_HPP
#define _ACHIEVEMENTS_HPP
#include "Observer.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "SaveSlot.hpp"
#include <memory>

#include <iostream>

/**
*	@class Achievements
*	@brief
*/
class Achievements : public Observer {
public:
	/**
	*	@brief
	*/
	Achievements();
	/**
	*	@brief
	*/
	Achievements(SaveSlot *cur);

	/**
	*	@brief
	*/
	~Achievements();
	/**
	*	@brief
	*/
	void onNotify(Subject::EVENT evnt, Entity *entity);
	/**
	*	@brief
	*/
	void update();
private:
	SaveSlot *m_current_slot;
	void unlock(string s);

	//bool first_build;
};

#endif