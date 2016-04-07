#ifndef _OBSERVER_HPP
#define _OBSERVER_HPP
#include "Subject.hpp"
#include "Entity.hpp"

/**
*	@class Observer
*	@brief This is the base observer class for the ObserverPattern to work. Any class that
*	inherites from this class will become an observer and must be pasted into the subject class
*	for notifications to work.
*	@see Subject
*/
class Observer {
public:
	Observer()	{}
	/**
	*	@brief
	*/
	virtual ~Observer()		{}
	/**
	*	@brief
	*/
	virtual void onNotify(Subject::EVENT evnt, Entity *entity) = 0;
	/**
	*	@brief
	*/
	virtual void update() = 0;
};

#endif