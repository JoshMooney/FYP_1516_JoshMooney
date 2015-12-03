#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "stdafx.h"
#include "Entity.hpp"

#include "Box2D\Box2D.h"
#include "vHelper.hpp"

class Player : public Entity {
private:
	bool m_is_moving, m_is_jumping;
	float m_speed;
	bool m_direction;
	sf::Vector2u m_text_size;
	float m_acceleration;
	float m_deceleration;
	float m_jump_force;
	float speedFactor;
public:
	Player(b2World &m_world);
	~Player();

	void update(FTS fts);
	void Idle();
	void moveLeft();
	void moveRight();
	void jump();
	void reset(sf::Vector2f pos);

	b2Body* getBody()	{ return e_box_body; }
	bool isMoving()	{ return m_is_moving; }
	float getSpeed()	{ return m_speed; }
	bool getDirection()	{ return m_direction; }
	void setDirection(float d)	{ m_direction = d; };
	bool isJumping()	{ return m_is_jumping; }
	b2Vec2 getCenter()	{ return e_box_body->GetPosition(); }
	void moveTo(sf::Vector2f p) {	e_box_body->SetTransform(vHelper::toB2(p), 0.0f);	}
	void Spawn(sf::Vector2f p);
	
	inline float clamp(float x, float min, float max);
	void alineSprite();
	void setIfMoving(bool b) { m_is_moving = b; }
};

#endif