#ifndef _SENSOR_POOL_HPP
#define _SENSOR_POOL_HPP
#include "stdafx.h"
#include "Sensor.hpp"
#include "Checkpoint.hpp"
#include <vector>

class SensorPool {
private:
	b2World *m_world;
	vector<Sensor *> m_list;
public:
	Sensor* m_end;
	vector<Checkpoint *> m_checkpts;

	SensorPool(b2World *world) : m_world(world){

	}
	~SensorPool() {

	}

	void push_back(Sensor* s) {
		m_list.push_back(s);
	}

	void cull() {
		for (auto it = m_list.begin(); it != m_list.end();) {
			//If the Enemy is not alive
			if (!(*it)->hasTripped() && (*it)->can_despawn) {
				m_world->DestroyBody((*it)->getBody());		//Destroy the b2body of the enemy
				cLog::inst()->print(0, "Sensor", "Sensor Body Destroyed");
				delete *it;				//delete the pointer
				it = m_list.erase(it);	//erase the object(calls the objects destructor)
				cLog::inst()->print(0, "Sensor", "Sensor removed from m_list");
			}
			else ++it;
		}
	}
	void clear() {
		for (auto it = m_list.begin(); it != m_list.end();) {
			m_world->DestroyBody((*it)->getBody());		//Destroy the b2body of the enemy
			delete *it;				//delete the pointer
			it = m_list.erase(it);	//erase the object(calls the objects destructor)
		}

		m_end = nullptr;
	}

	bool hasEnded() { return m_end->hasTripped(); }   //!<Bool check for if the level has ended or not

};

#endif