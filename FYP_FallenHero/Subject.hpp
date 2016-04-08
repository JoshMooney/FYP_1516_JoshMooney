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
	enum EVENT{
		P_JUMP = 1,
		P_ATTACK = 2,
		P_LVLFIN = 3,
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