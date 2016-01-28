#ifndef _WEED_HPP
#define _WEED_HPP
#include "stdafx.h"
#include "Enemy.hpp"

class Weed : public Enemy {
private:
	sf::Vector2u m_text_size;
	float speedFactor;
	float m_speed;
public:
	enum AI { GREEN, BLUE, RED };
	AI ai;
	enum STATE { ATTACKING, IDLE, DEATH, EXCITED };
	STATE m_current_state;

	Weed();
	Weed(b2Body *b, sf::Vector2f pos, bool dir);
	~Weed();
	void init();

	void update(FTS fts);
	void render(sf::RenderWindow &w, sf::Time frames);
	void TakeDamage();
	void Die();
	void assignBody(b2Body *b) { e_box_body = b; }
	void attack();
	void alineSprite();
	void ChangeDirection();
	void setDirection(bool b);
	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }
	sf::Vector2u getTextureSize() { return m_text_size; }
};

#endif