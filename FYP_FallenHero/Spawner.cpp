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

b2Body * Spawner::GenerateBody(SPAWN_TYPE type, sf::Vector2f pos) {
	b2BodyDef myBodyDef;
	b2PolygonShape shape;
	b2FixtureDef myFixtureDef;
	sf::Vector2f size;
	sf::Vector2f pos_off;

	switch (type) {
	b2Body* body;
	case SKELETON:
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		size = sf::Vector2f(27, 44);
		pos_off = sf::Vector2f(pos.x + size.x / 2, pos.y + size.y / 2);
		myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		body = m_world->CreateBody(&myBodyDef);
		shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.5f;
		myFixtureDef.shape = &shape;
		myFixtureDef.userData = "Skeleton";

		myFixtureDef.filter.categoryBits = _filterCategory::ENEMY;
		myFixtureDef.filter.maskBits = ENEMY | PLAYER | TERRAIN | PLATFORM;

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	case WEED:
		myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
		size = sf::Vector2f(39, 37);
		pos_off = sf::Vector2f(pos.x + size.x / 2, pos.y + size.y / 2);
		myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		body = m_world->CreateBody(&myBodyDef);
		shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.5f;
		myFixtureDef.shape = &shape;
		//Left on purpose so all the collision detection is the same. For now...
		myFixtureDef.userData = "Skeleton";

		myFixtureDef.filter.categoryBits = _filterCategory::ENEMY;
		myFixtureDef.filter.maskBits = ENEMY | PLAYER | TERRAIN | PLATFORM;

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	case CANNON:
		myBodyDef.type = b2_staticBody; //this will be a dynamic body
		size = sf::Vector2f(32, 32);
		pos_off = sf::Vector2f(pos.x + size.x/2, pos.y + size.y / 2);
		myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		body = m_world->CreateBody(&myBodyDef);
		shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.0f;
		myFixtureDef.shape = &shape;
		myFixtureDef.userData = "Cannon";

		myFixtureDef.filter.categoryBits = _filterCategory::ENEMY;
		myFixtureDef.filter.maskBits = ENEMY | PLAYER | TERRAIN | PLATFORM;

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	/*case CHEST:
		//Moved to SpawnChest Method
		return body;
		break;*/
	}
}

void Spawner::SpawnWeed(sf::Vector2f pos, bool dir) {
	m_enemies.push_back(new Weed(GenerateBody(WEED, pos), dir));

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
	m_enemies.push_back(new Skeleton(GenerateBody(SKELETON, pos), true));
}
void Spawner::SpawnBlock(sf::Vector2f pos, CrumbleBlock::TYPE t, CrumbleBlock::SIZE s) {
	sf::Vector2f size;
	b2PolygonShape block_Shape;
	if (s == CrumbleBlock::LARGE)
		size = sf::Vector2f(64, 64);
	if (s == CrumbleBlock::SMALL)
		size = sf::Vector2f(32, 32);

	b2BodyDef block_Def;
	block_Def.type = b2_dynamicBody;
	sf::Vector2f pos_off = sf::Vector2f(pos.x - size.x / 2, pos.y - size.y / 2);
	block_Def.position = vHelper::toB2(pos); //set the starting position
	block_Def.angle = 0; //set the starting angle
	block_Def.fixedRotation = true;

	b2Body* body = m_world->CreateBody(&block_Def);

	//Define the shape of the body
	block_Shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef block_Fix;
	block_Fix.density = 1000.0f;
	block_Fix.friction = 1.0f;
	block_Fix.shape = &block_Shape;
	block_Fix.userData = "Block";

	block_Fix.filter.categoryBits = _filterCategory::TERRAIN;
	block_Fix.filter.maskBits = PLAYER | ENEMY | BULLET | TERRAIN | PLATFORM | GEM;

	body->CreateFixture(&block_Fix);

	m_blocks.push_back(new CrumbleBlock(body, pos, t, s));
}
void Spawner::SpawnCannon(sf::Vector2f pos, bool dir) {
	b2Body* bod = GenerateBody(CANNON, pos);
	m_enemies.push_back(new Cannon(bod, dir, m_gun));
}
void Spawner::SpawnCannon(sf::Vector2f pos, bool dir, float cd, Projectile::STATE type) {
	b2Body* bod = GenerateBody(CANNON, pos);
	m_enemies.push_back(new Cannon(bod, dir, m_gun, cd, type));
}
void Spawner::SpawnChest(sf::Vector2f pos, bool dir, string type) {
	//b2Body* bod = GenerateBody(CHEST, pos);
	Chest::TYPE chest_type;

	b2BodyDef myBodyDef;
	b2PolygonShape shape;
	b2FixtureDef myFixtureDef;
	sf::Vector2f size;
	sf::Vector2f pos_off;

	if (type == "brown") {
		size = sf::Vector2f(27, 15);
		chest_type = Chest::TYPE::BROWN;
	}
	if (type == "green") {
		size = sf::Vector2f(37, 18);
		chest_type = Chest::TYPE::GREEN;
	}
	if (type == "purple") {
		size = sf::Vector2f(37, 18);
		chest_type = Chest::TYPE::PURPLE;
	}

	myBodyDef.type = b2_kinematicBody; //this will be a dynamic body
	pos_off = sf::Vector2f(pos.x + size.x / 2, pos.y + (size.y / 2) + 17);
	myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.fixedRotation = true;

	b2Body *body;
	body = m_world->CreateBody(&myBodyDef);
	shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

	myFixtureDef.density = 100.0f;
	myFixtureDef.friction = 1.5f;
	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Chest";
	//myFixtureDef.isSensor = true;

	myFixtureDef.filter.categoryBits = _filterCategory::ENEMY;
	myFixtureDef.filter.maskBits = ENEMY | PLAYER | TERRAIN | PLATFORM;

	body->CreateFixture(&myFixtureDef);

	m_enemies.push_back(new Chest(body, dir, m_mine, chest_type));
}
void Spawner::SpawnDoor(sf::Vector2f pos, string id) {
	b2BodyDef myBodyDef;
	b2PolygonShape shape;
	b2FixtureDef myFixtureDef;
	sf::Vector2f size;
	sf::Vector2f pos_off;

	size = sf::Vector2f(32, 160);

	myBodyDef.type = b2_kinematicBody; //this will be a dynamic body
	pos_off = sf::Vector2f(pos.x + size.x / 2, pos.y + (size.y / 2) + 17);
	myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.fixedRotation = true;

	b2Body *body;
	body = m_world->CreateBody(&myBodyDef);
	shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.0f;
	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Door";

	myFixtureDef.filter.categoryBits = _filterCategory::ENEMY;
	myFixtureDef.filter.maskBits = ENEMY | PLAYER | TERRAIN | PLATFORM;

	body->CreateFixture(&myFixtureDef);
	
	m_enemies.push_back(new Door(body, id));
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
