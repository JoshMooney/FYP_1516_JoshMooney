#ifndef _CANNON_HPP
#define _CANNON_HPP
#include "stdafx.h"
#include "Enemy.hpp"
#include "ProjectileManager.hpp"

class Cannon : public Enemy {
private:
	sf::Clock m_fire_clock;
	sf::Vector2u m_size;
	float cooldown_time;

	string s_fire, s_hit;
	sf::Sound m_fire, m_hit;
	ProjectileManager* m_gun;
	Projectile::STATE m_level;
public:
	Cannon();
	Cannon(b2Body* b, bool dir, ProjectileManager* p);
	Cannon(b2Body* b, bool dir, ProjectileManager* p, float cooldown, Projectile::STATE type);
	~Cannon();

	void update(FTS fts, Player *p);
	void render(sf::RenderWindow &w, sf::Time frames);
	void loadMedia();

	sf::FloatRect getBounds();
	void alineSprite();
	void TakeDamage();
	void Die();

	void attack();
};

#endif