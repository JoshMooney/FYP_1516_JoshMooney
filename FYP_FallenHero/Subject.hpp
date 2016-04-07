#ifndef SUBJECT_HPP
#define SUBJECT_HPP
#include <vector>
#include <algorithm>
#include <string>

class Observer;

class Subject {
public:
	enum EVENT{
		
	};
	static Subject* instance();

	void notify(EVENT e, Entity *entity_);
	void addObserver(Observer* o);
	void removeObserver(Observer *o);
	void update();

	~Subject();
private:
	std::vector<Observer*> observers_;
	static Subject* mInstance;
protected:
	Subject();
};

#include "Observer.hpp"
#endif