#ifndef SUBJECT_HPP
#define SUBJECT_HPP
#include "SFML\Graphics.hpp"
#include "Entity.hpp"
#include <vector>
#include <algorithm>
#include <string>

class Observer;

class Subject {
public:
	enum EVENT {
		FIRST_JUMP = 1,
		FIRST_ATTACK = 2,
		PICKUP_100 = 3,
		//General
		ELEVATOR_PITCH = 4,
		DEMO_DAY = 5,
		PROJECTILE_HITTER = 6,
		OUCH = 7,
		OUT_OF_CATS_LIVES = 8, 
		WILE_E_COYOTE = 9,
		//Level Achievements
		FINISH_LVL1 = 10,
		FINISH_LVL2 = 11,
		FINISH_LVL3A = 12,
		FINISH_LVL3B = 13,
		FINISH_LVL4 = 14,
		FINISH_LVL5 = 15,
		FINISH_LVL6 = 16,
		
		PICKUP_1000 = 17,
		ALL_SHAPES_SIZES = 18,
		LOCK_SMITH = 19,
		THIEF_OR_ADVENTURER = 20,
		MULTI_CHECKPOINT = 21,

		//Notifies for stat tracking in the Achievements Class
		GEM_PICK = 22,
		CB_DESTROY = 23,
		CP_TRIP = 24,
		BULLET_HIT = 25,

		DIRT_32 = 26,
		DIRT_64 = 27,
		SAND_32 = 28,
		SAND_64 = 29,
		ROCK_32 = 30,
		ROCK_64 = 31,

		CHEST_OPEN = 32,
	};
	static Subject* instance();

	void notify(EVENT e, Entity *entity_);
	void addObserver(Observer* o);
	void removeObserver(Observer *o);
	void update();
	void render(sf::RenderWindow *w);

	~Subject();
private:
	std::vector<Observer*> observers_;
	static Subject* mInstance;
protected:
	Subject();
};

#include "Observer.hpp"
#endif