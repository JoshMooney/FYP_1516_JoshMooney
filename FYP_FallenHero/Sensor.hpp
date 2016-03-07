#ifndef _SENSOR_HPP
#define _SENSOR_HPP
#include "stdafx.h"
#include "Box2D\Box2D.h"

/**
*	@class Sensor
*	@brief This class will be used as a trigger class to detect a trip in an area,
*	This has future applications such as trigger cutscenes or enemy spawning.
*/
class Sensor {
private:
	string m_id;
	b2Body *m_body;
	bool m_tripped;
	sf::Vector2f m_position;
protected:
	b2Body* createBody(b2World* w, sf::Vector2f pos, sf::Vector2u size) {
		body_active = true;

		b2BodyDef myBodyDef;
		myBodyDef.type = b2_staticBody; //this will be a dynamic body
		myBodyDef.position = vHelper::toB2(pos); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		b2Body* body = w->CreateBody(&myBodyDef);

		//Define the shape of the body
		b2PolygonShape shape;
		//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
		shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.0f;
		myFixtureDef.shape = &shape;
		myFixtureDef.userData = "Sensor";

		body->CreateFixture(&myFixtureDef);
		return body;
	}
	void setTrip(bool t) {
		m_tripped = t;
	}
public:
	//!Whether or not the body is active or not.
	bool body_active;
	//!Deprecated default constructor for the sensor class.
	Sensor() {		}
	/**
	*	@brief This is the overloaded constructor that creates and sets up the sensor.
	*	@param b2World The Box2D world used for creating bodies.
	*	@param pos The position of the senesor
	*	@param size A Vector2 of ints of the dimentions of the sensor.
	*/
	Sensor(b2World *w, sf::Vector2f pos, sf::Vector2u size) {
		m_tripped = false;
		m_position = pos;
		m_body = createBody(w, pos, size);
		m_body->SetUserData(this);
	}
	/**
	*	@brief This is the overloaded constructor that creates and sets up the sensor.
	*	@param b2World The Box2D world used for creating bodies.
	*	@param pos The position of the senesor
	*	@param size A Vector2 of ints of the dimentions of the sensor.
	*	@param string This is the ID string used for identifvstion of the sensor.
	*/
	Sensor(b2World *w, sf::Vector2f pos, sf::Vector2u size, string id) : m_id(id) {
		m_tripped = false;
		m_position = pos;
		m_body = createBody(w, pos, size);
		m_body->SetUserData(this);
	}
	/**
	*	@brief This is the main funtion of the class inheriting classes should overload
	*	this method as this is what will be called in the contact listener.
	*/
	virtual void trip() {
		m_tripped = true;
	}
	/**
	*	@brief Check for whether the sensor has been tripped or not.
	*	@return True or false if the sensor has been tripped.
	*/
	bool hasTripped() const{
		return m_tripped;
	}
	/**
	*	@brief Gets the body associated with the Sensor
	*	@return Apointer to the body of the sensor
	*/
	b2Body* getBody() {
		return m_body;
	}
	/**
	*	@brief
	*	@param
	*/
	//void setBody(b2Body* b) {
	//	m_body = b;
	//}
	/**
	*	@brief Returns the position of the sensor
	*	@return Vector2f of the position of the sensor
	*/
	sf::Vector2f& position() { return m_position; }
};

#endif