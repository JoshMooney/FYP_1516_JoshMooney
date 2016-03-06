#ifndef _SENSOR_HPP
#define _SENSOR_HPP
#include "stdafx.h"
#include "Box2D\Box2D.h"

/**
*	@class Sensor
*	@brief
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
	bool body_active;

	Sensor() {

	}
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*/
	Sensor(b2World *w, sf::Vector2f pos, sf::Vector2u size) {
		m_tripped = false;
		m_position = pos;
		m_body = createBody(w, pos, size);
		m_body->SetUserData(this);
	}
	/**
	*	@brief
	*	@param
	*	@param
	*	@param
	*	@param
	*/
	Sensor(b2World *w, sf::Vector2f pos, sf::Vector2u size, string id) : m_id(id) {
		m_tripped = false;
		m_position = pos;
		m_body = createBody(w, pos, size);
		m_body->SetUserData(this);
	}
	/**
	*	@brief
	*/
	virtual void trip() {
		m_tripped = true;
	}
	/**
	*	@brief
	*	@return
	*/
	bool hasTripped() const{
		return m_tripped;
	}
	/**
	*	@brief
	*	@return
	*/
	b2Body* getBody() {
		return m_body;
	}
	/**
	*	@brief
	*	@param
	*/
	void setBody(b2Body* b) {
		m_body = b;
	}
	/**
	*	@brief
	*	@return
	*/
	sf::Vector2f& position() { return m_position; }
};

#endif