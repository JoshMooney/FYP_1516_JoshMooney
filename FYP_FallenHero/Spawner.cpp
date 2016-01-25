#include "stdafx.h"
#include "Spawner.hpp"
#include "vHelper.hpp"

float Spawner::distanceToPlayer(sf::Vector2f entity, sf::Vector2f player) {
	return sqrt(pow(entity.x - player.x, 2) + pow(entity.x - player.x, 2));
}

Spawner::Spawner(b2World * world) {
	update_dist = 150;
	m_world = world;

	prototype_snake = new Snake();
}

Spawner::~Spawner() {

}

b2Body * Spawner::GenerateBody(SPAWN_TYPE type) {
	switch (type) {
	case SNAKE:
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position.Set(100, 100); //set the starting position
		myBodyDef.angle = 0; //set the starting angle

		b2Body* body = m_world->CreateBody(&myBodyDef);

		//Define the shape of the body
		b2PolygonShape shape;
		//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
		shape.SetAsBox(prototype_snake->getTextureSize().x / 2.0f, prototype_snake->getTextureSize().y / 2.0f);

		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.5f;
		myFixtureDef.shape = &shape;

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	}
}

void Spawner::SpawnSnake(sf::Vector2f pos) {
	b2Body* b  = GenerateBody(SNAKE);
	m_enemies.push_back(new Snake(b, pos, true));
}

void Spawner::CullInActiveEnemies() {
	//Loop through all of the Enemies
	for (auto it = m_enemies.begin(); it != m_enemies.end();) {
		//If the Enemy is not alive
		if (!(*it)->isAlive()) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			delete * it;				//delete the pointer
			it = m_enemies.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "Spawner", "Enemy Removed");
		}
		else ++it;
	}
}

void Spawner::update(FTS fts, Player * p) {
	for(Enemy* e : m_enemies) {
		if (update_dist < distanceToPlayer(vHelper::toSF(e->getCenter()), vHelper::toSF(p->getCenter()))) {
			e->update(fts);
		}
	}
}

void Spawner::render(sf::RenderWindow &w) {
	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies.at(i)->render(w);
		w.draw(*m_enemies[i]);
	}
}
