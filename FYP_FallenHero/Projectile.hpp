#ifndef _PROJECTILE_HPP
#define _PROJECTILE_HPP
#include "stdafx.h"
#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include "ResourceManager.hpp"

/**
*	@class Projectile
*	@brief This is the main base class for the projectile type of entity.
*/
class Projectile : public sf::Sprite {
private:
	float m_speed;
	string s_texture;
	sf::Vector2f m_size;
	bool m_body_active;     
	b2Body *m_box_body;     
	sf::Vector2f m_direction;
	bool can_despawn;
	
public:
	sf::Vector2f m_spawn_point;

	Projectile();
	Projectile(b2Body* b, sf::Vector2f dir);
	~Projectile();

	void update();
	void render(sf::RenderWindow &w, sf::Time frames);
	void loadMedia();

	void Die();
	void alineSprite();

	bool isAlive() { return m_body_active; }
	bool canDespawn() { return can_despawn; }
	b2Body* getBody() { return m_box_body; }

	void applySpeed();
};

#endif