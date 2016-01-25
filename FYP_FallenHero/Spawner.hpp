#ifndef _SPAWNER_HPP
#define _SPAWNER_HPP
#include "stdafx.h"

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"
#include "Enemy.hpp"
#include "Snake.hpp"

#include "Player.hpp"

class Spawner {
private:
	float distanceToPlayer(sf::Vector2f entity, sf::Vector2f player);
	float update_dist;
	b2World *m_world;

	Snake* prototype_snake;
	vector<Enemy *> m_enemies;

public:
	enum SPAWN_TYPE {SNAKE};
	Spawner()	{		}
	Spawner(b2World *world);
	~Spawner();

	b2Body* GenerateBody(SPAWN_TYPE type);

	void SpawnSnake(sf::Vector2f pos);

	void CullInActiveEnemies();

	void update(FTS fts, Player *p);
	void render(sf::RenderWindow &w);
};

#endif
