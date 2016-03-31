#include "stdafx.h"
#include "Spawner.hpp"
#include "vHelper.hpp"

float Spawner::distanceToPlayer(sf::Vector2f entity, sf::Vector2f player) {
	return sqrt(pow(entity.x - player.x, 2) + pow(entity.x - player.x, 2));
}

Spawner::Spawner(b2World * world) {
	update_dist = 1200;
	m_world = world;

	prototype_Skeleton = new Skeleton();
}

Spawner::~Spawner() {

}

b2Body * Spawner::GenerateBody(SPAWN_TYPE type) {
	b2BodyDef myBodyDef;
	b2PolygonShape shape;
	b2FixtureDef myFixtureDef;

	switch (type) {
	b2Body* body;
	case SKELETON:
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position = vHelper::toB2(sf::Vector2f(100,100)); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		body = m_world->CreateBody(&myBodyDef);
		shape.SetAsBox((prototype_Skeleton->getTextureSize().x / vHelper::B2_SCALE) / 2.0f, (prototype_Skeleton->getTextureSize().y / vHelper::B2_SCALE) / 2.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.5f;
		myFixtureDef.shape = &shape;
		myFixtureDef.userData = "Skeleton";

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	case WEED:
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		myBodyDef.position = vHelper::toB2(sf::Vector2f(100, 100)); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		body = m_world->CreateBody(&myBodyDef);
		shape.SetAsBox((39 / vHelper::B2_SCALE) / 2.0f, (37 / vHelper::B2_SCALE) / 2.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.5f;
		myFixtureDef.shape = &shape;
		//Left on purpose so all the collision detection is the same. For now...
		myFixtureDef.userData = "Skeleton";

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	case CANNON:
		myBodyDef.type = b2_staticBody; //this will be a dynamic body
		myBodyDef.position = vHelper::toB2(sf::Vector2f(100, 100)); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		body = m_world->CreateBody(&myBodyDef);
		shape.SetAsBox((32 / vHelper::B2_SCALE) / 2.0f, (32 / vHelper::B2_SCALE) / 2.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.0f;
		myFixtureDef.shape = &shape;
		myFixtureDef.userData = "Cannon";

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	}
}

void Spawner::SpawnWeed(sf::Vector2f pos, bool dir) {
	m_enemies.push_back(new Weed(GenerateBody(WEED), pos, dir));

	/*if (m_enemies.size() >= 2){
		for (auto it = m_enemies.begin(); it != m_enemies.end();) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			(*it)->e_box_body = nullptr;
			Enemy* e = *it;
			delete e;				//delete the pointer
			it = m_enemies.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "Spawner", "Enemy Removed");
		}
	}*/

}
void Spawner::SpawnSkeleton(sf::Vector2f pos) {
	m_enemies.push_back(new Skeleton(GenerateBody(SKELETON), pos, true));
}
void Spawner::SpawnBlock(sf::Vector2f pos, CrumbleBlock::TYPE t, CrumbleBlock::SIZE s) {
	b2BodyDef block_Def;
	block_Def.type = b2_staticBody;
	block_Def.position = vHelper::toB2(sf::Vector2f(-100, -100)); //set the starting position
	block_Def.angle = 0; //set the starting angle
	block_Def.fixedRotation = true;

	b2Body* body = m_world->CreateBody(&block_Def);

	//Define the shape of the body
	b2PolygonShape block_Shape;
	if (s == CrumbleBlock::LARGE)
		block_Shape.SetAsBox((64 / vHelper::B2_SCALE) / 2.0f, (64 / vHelper::B2_SCALE) / 2.0f);
	if(s == CrumbleBlock::SMALL)
		block_Shape.SetAsBox((32 / vHelper::B2_SCALE) / 2.0f, (32 / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef block_Fix;
	block_Fix.density = 1.0f;
	block_Fix.friction = 1.5f;
	block_Fix.shape = &block_Shape;
	block_Fix.userData = "Block";

	body->CreateFixture(&block_Fix);

	m_blocks.push_back(new CrumbleBlock(body, pos, t, s));
}
void Spawner::SpawnCannon(sf::Vector2f pos, bool dir) {
	b2Body* bod = GenerateBody(CANNON);
	bod->SetTransform(vHelper::toB2(sf::Vector2f(pos.x, pos.y + 16)), 0.0f);
	m_enemies.push_back(new Cannon(bod, dir));
}

/*
void Spawner::CullBodies() {
	//Delete any box bodies for the Blocks
	for (auto it = m_blocks.begin(); it != m_blocks.end();) {
		if (!(*it)->isAlive()) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			cLog::inst()->print(0, "Spawner", "Block Body Destroyed");
		}
		else ++it;
	}
}
void Spawner::DespawnObject() {
	//Despawn any Blocks
	for (auto it = m_blocks.begin(); it != m_blocks.end();) {
		if (!(*it)->isAlive() && (*it)->canDespawn()) {
			delete * it;				//delete the pointer
			it = m_blocks.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "Spawner", "Block Despawned");
		}
		else ++it;
	}
}*/

void Spawner::CullInActiveEnemies() {
	//Loop through all of the Enemies
	for (auto it = m_enemies.begin(); it != m_enemies.end();) {
		//If the Enemy is not alive
		if (!(*it)->isAlive() && (*it)->canDespawn()) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			//(*it)->e_box_body = nullptr;
			cLog::inst()->print(0, "Spawner", "Enemy Body Destroyed");
			Enemy* e = *it;
			//delete e;				//delete the pointer
			m_dead_enemies.push_back(e);
			it = m_enemies.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "Spawner", "Enemy removed from m_enemies list and put into m_remove_enemies");
		}
		else ++it;
	}

	//Loop through all of the Blocks
	for (auto it = m_blocks.begin(); it != m_blocks.end();) {
		//If the Block is not alive
		if (!(*it)->isAlive() && (*it)->canDespawn()) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			delete *it;				//delete the pointer
			it = m_blocks.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "Spawner", "Block Removed");
		}
		else ++it;
	}
}

void Spawner::update(FTS fts, Player * p) {
	for(Enemy* e : m_enemies) {
		//Check for collision before checking the distance
		if (e->isCollidingSword() && p->isAttacking() && p->getAttackBounds().intersects(e->getBounds())) {
			e->TakeDamage();
		}
		if (!p->isAttacking() && e->is_hit) {
			e->is_hit = false;
		}
		if (update_dist > distanceToPlayer(e->getCenter(), p->getCenter())) { 
			e->update(fts, p);
		}

	}

	//Check Swing of player against the Blocks
	for (int i = 0; i < m_blocks.size(); i++) {
		if (!p->isAttacking() && m_blocks[i]->is_hit) {
			m_blocks[i]->is_hit = false;
		}
		if (m_blocks[i]->isCollidingSword() && p->isAttacking() && !m_blocks[i]->is_hit &&p->getAttackBounds().intersects(m_blocks[i]->getBounds())) {
			m_blocks[i]->TakeDamage();
			m_blocks[i]->is_hit = true;
		}
		else {
			m_blocks[i]->update(fts, p);
		}

		if (m_blocks[i]->e_body_active == false && m_blocks[i]->canGemSpawn())
			m_mine->SpawnBlock(m_blocks[i]->m_type, m_blocks[i]->m_size, m_blocks[i]->getCenter());
	}

	//CullBodies();
	//DespawnObject();
}

void Spawner::render(sf::RenderWindow &w, sf::Time frames) {
	//Render Enemies
	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies.at(i)->render(w, frames);
		w.draw(*m_enemies[i]);
	}
	//Render Blocks
	for (int i = 0; i < m_blocks.size(); i++) {
		m_blocks.at(i)->render(w, frames);
		w.draw(*m_blocks[i]);
	}
}

void Spawner::clear() {
	for (auto it = m_enemies.begin(); it != m_enemies.end();) {
		m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
		delete *it;				//delete the pointer
		it = m_enemies.erase(it);	//erase the object(calls the objects destructor)
		//cLog::inst()->print(0, "Spawner", "Enemy cleared from spawner");
	}

	for (auto it = m_dead_enemies.begin(); it != m_dead_enemies.end();) {
		cLog::inst()->print(0, "Spawner", "Delete Enemy");
		delete *it;				//delete the pointer
		cLog::inst()->print(0, "Spawner", "Delete Successful");
		it = m_dead_enemies.erase(it);	//erase the object(calls the objects destructor)
	}

	for (auto it = m_blocks.begin(); it != m_blocks.end();) {
		m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
		delete * it;				//delete the pointer
		it = m_blocks.erase(it);	//erase the object(calls the objects destructor)
		//cLog::inst()->print(0, "Spawner", "Block cleared from spawner");
	}
}
