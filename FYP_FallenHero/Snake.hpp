#ifndef _SNAKE_HPP
#define _SNAKE_HPP
#include "stdafx.h"

#include "Enemy.hpp"

class Snake : public Enemy {
private:
	sf::Vector2u m_text_size;
	float m_acceleration;
	float m_deceleration;
	float m_speed;
	float speedFactor;
public:
	enum AI {GREEN};
	AI ai;
	enum STATE {WALKING, ATTACKING};
	STATE m_current_state;
	Snake();
	Snake(b2Body *b, sf::Vector2f pos, bool dir);
	Snake(b2World *world);
	void init();

	void update(FTS fts);
	void render(sf::RenderWindow &w);

	void assignBody(b2Body *b) { e_box_body = b; }
	void move();
	void attack();
	void alineSprite();
	b2Vec2 getCenter() { return e_box_body->GetPosition(); }
	sf::Vector2u getTextureSize() { return m_text_size; }
};

#endif