#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "stdafx.h"
#include "Entity.hpp"

#include "Box2D\Box2D.h"

class Player : public Entity {
private:
	bool m_is_moving, m_is_jumping;
	float m_speed;
	bool m_direction;
	sf::Vector2u m_text_size;
	float m_acceleration;
	float m_deceleration;
	float m_jump_force;
public:
	Player(b2World &m_world);
	~Player();

	void update(sf::Time dt);
	void moveLeft();
	void moveRight();
	void jump();

	b2Body* getBody()	{ return e_box_body;; }
	bool isMoving()	{ return m_is_moving; }
	float getSpeed()	{ return m_speed; }
	bool getDirection()	{ return m_direction; }
	void setDirection(float d)	{ m_direction = d; };
	bool isJumping()	{ return m_is_jumping; }
	b2Vec2 getCenter()	{ return e_box_body->GetPosition(); }

	inline float clamp(float x, float min, float max);
	void alineSprite();
};

#endif