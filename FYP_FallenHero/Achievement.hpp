#ifndef _ACHIEVEMENTS_HPP
#define _ACHIEVEMENTS_HPP
#include "Observer.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"
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
	Achievements()	{	}
	/**
	*	@brief
	*/
	Achievements(std::vector<std::unique_ptr<Entity>> *el);

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
	std::vector<std::unique_ptr<Entity>> *entity_list;
	void unlock(string s);

	bool first_build;
	bool first_upgrade;
	bool built_ranged;
	bool built_power;
	bool varied_builder;

	bool first_spawn;
	bool fifth_spawn;
	int spawn_count;
	bool melee_spawn;
	bool archer_spawn;
	bool siege_spawn;
	bool varied_spawned;

	bool v1Overkill;
	bool v2Overkill;
	bool v3Overkill;

	bool first_kill;
	bool melee_kill;
	bool archer_kill;
	bool siege_kill;
	bool varied_kill;

	bool oppsCheevo;
};

#endif