#include "stdafx.h"
#include "EntityCreator.hpp"

EntityCreator::EntityCreator() {	}
EntityCreator::EntityCreator(b2World * world) : m_world(world){

}
EntityCreator::~EntityCreator() {	}

b2Body * EntityCreator::generateBody(SPAWN_TYPE type, sf::Vector2f pos) {
	b2BodyDef myBodyDef;
	b2PolygonShape shape;
	b2FixtureDef myFixtureDef;
	sf::Vector2f size;
	sf::Vector2f pos_off;
	b2Body *body;

	switch (type) {
	case KEY:
		myBodyDef.type = b2_staticBody; //this will be a dynamic body
		size = sf::Vector2f(32, 32);
		pos_off = sf::Vector2f(pos.x + size.x / 2, pos.y + size.y / 2);
		myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
		myBodyDef.angle = 0; //set the starting angle
		myBodyDef.fixedRotation = true;

		body = m_world->CreateBody(&myBodyDef);
		shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);
		body->SetGravityScale(0.0f);

		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.0f;
		myFixtureDef.shape = &shape;
		myFixtureDef.userData = "Key";

		myFixtureDef.filter.categoryBits = _filterCategory::ENTITY;
		myFixtureDef.filter.maskBits = PLAYER;

		body->CreateFixture(&myFixtureDef);
		return body;
		break;
	}
	return nullptr;
}

void EntityCreator::spawnKey(sf::Vector2f pos, string type, string id, string door) {
	Key::TYPE key_type;
	if (type == "gold")
		key_type = Key::TYPE::GOLD;
	if (type == "blue")
		key_type = Key::TYPE::BLU;
	if (type == "green")
		key_type = Key::TYPE::GRN;
	if (type == "silver")
		key_type = Key::TYPE::SIL;

	m_entities.push_back(new Key(generateBody(KEY, pos), key_type, door, id));
}

void EntityCreator::Cull() {
	//Loop through all of the Entities
	for (auto it = m_entities.begin(); it != m_entities.end();) {
		//If the Enemy is not alive
		if ((*it)->canDespawn()) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			cLog::inst()->print(0, "EntityCreator", "Entity Destroyed.");
			delete (*it);			//delete the pointer
			it = m_entities.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "EntityCreator", "Enemy removed from m_enemies list and put into m_remove_enemies");
		}
		else ++it;
	}
}

void EntityCreator::update(FTS fts, Player * p) {
	for (int i = 0; i < m_entities.size(); i++) {
		if (vHelper::distance(p->getPosition(), vHelper::toSF(m_entities[i]->e_box_body->GetPosition())) < update_dist) {
			m_entities[i]->update(fts);
		}
	}

	Cull();
}

void EntityCreator::render(sf::RenderWindow *w, sf::Time frames) {
	for (int i = 0; i < m_entities.size(); i++) {
		if(m_entities[i]->e_body_active)
			w->draw(*m_entities[i]);
	}
}

void EntityCreator::clear() {
	for (auto it = m_entities.begin(); it != m_entities.end();) {
		m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
		delete (*it);				//delete the pointer
		it = m_entities.erase(it);	//erase the object(calls the objects destructor)
		cLog::inst()->print(0, "EntityCreator", "Entities cleared from creator");
	}
}
