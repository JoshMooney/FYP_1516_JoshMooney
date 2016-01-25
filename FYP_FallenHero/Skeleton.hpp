#ifndef _SKELETON_HPP
#define _SKELETON_HPP
#include "stdafx.h"

#include "Terrain.hpp"
#include "Enemy.hpp"

class Skeleton : public Enemy {
private:
	sf::Vector2u m_text_size;
	float m_acceleration;
	float m_deceleration;
	float m_speed;
	Terrain* touching_terr;
	float speedFactor;
public:
	enum AI {GREEN};
	AI ai;
	enum STATE {WALKING, ATTACKING};
	STATE m_current_state;
	Skeleton();
	Skeleton(b2Body *b, sf::Vector2f pos, bool dir);
	Skeleton(b2World *world);
	void init();

	void update(FTS fts);
	void render(sf::RenderWindow &w);

	void TakeDamage();
	void Die();
	void assignBody(b2Body *b) { e_box_body = b; }
	void move();
	void attack();
	void alineSprite();
	sf::Vector2f getCenter() { return vHelper::toSF(e_box_body->GetPosition()); }
	sf::Vector2u getTextureSize() { return m_text_size; }
	void isTouching(Terrain* t) {	touching_terr = t;	}
	void ReachedEdge();
	void ReachPlayer();

};

#endif