#include "stdafx.h"
#include "GemMine.hpp"
#include "vHelper.hpp"

GemMine::GemMine(b2World *world) {
	m_world = world;

	m_gem_chart[Gem::TYPE::B_10] = sf::IntRect{ 7, 10, 6, 6 };
	m_gem_chart[Gem::TYPE::P_20] = sf::IntRect{ 27, 8, 8, 8 };
	m_gem_chart[Gem::TYPE::O_50] = sf::IntRect{ 48, 4, 9, 12 };
	m_gem_chart[Gem::TYPE::R_100] = sf::IntRect{ 67, 7, 13, 3 };
	m_gem_chart[Gem::TYPE::B_150] = sf::IntRect{ 86, 3, 17, 13 };
	m_gem_chart[Gem::TYPE::W_250] = sf::IntRect{ 105, 0, 21, 16 };

}

void GemMine::SpawnBlock(CrumbleBlock::TYPE type, CrumbleBlock::SIZE size, sf::Vector2f pos) {
	Gem::TYPE value;
	int prob = rand() % 10;
	switch (type) {
	case CrumbleBlock::TYPE::SAND:
		if (prob > 0 && prob < 3) {
			value = Gem::TYPE::B_10;
		}
		if (prob > 3 && prob < 6) {
			value = Gem::TYPE::P_20;
		}
		if (prob > 6 && prob < 9) {
			value = Gem::TYPE::O_50;
		}
		break; 
	case CrumbleBlock::TYPE::DIRT:
		if (prob > 0 && prob < 3) {
			value = Gem::TYPE::O_50;
		}
		if (prob > 3 && prob < 6) {
			value = Gem::TYPE::R_100;
		}
		if (prob > 6 && prob < 9) {
			value = Gem::TYPE::B_150;
		}
		break;
	case CrumbleBlock::TYPE::ROCK:
		if (prob > 0 && prob < 3) {
			value = Gem::TYPE::R_100;
		}
		if (prob > 3 && prob < 6) {
			value = Gem::TYPE::B_150;
		}
		if (prob > 6 && prob < 9) {
			value = Gem::TYPE::W_250;
		}
		break;
	}

	//Get Pop Angle
	sf::Vector2f direction(0, -1);
	float x = rand() % 200 + 1;
	if (x < 101)
		direction.x = -x / 100.0f;
	else
		direction.x = (x - 100.0f) / 100.0f;

	float speed = 10;
	b2Body* b = GenerateBody(value, true);
	b->GetFixtureList()->SetSensor(false);
	direction = sf::Vector2f(direction.x * speed, direction.y * speed);
	b->ApplyForce(b2Vec2(direction.x, direction.y), vHelper::toB2(pos), true);

	m_cart.push_back(new Gem(b, pos, value));
}

void GemMine::SpawnGem(Gem::TYPE type, sf::Vector2f pos, bool grav) {
	b2Body* b = GenerateBody(type, grav);
	m_cart.push_back(new Gem(b, pos, type));
}

b2Body* GemMine::GenerateBody(Gem::TYPE type, bool grav) {
	b2BodyDef gemBodyDef;
	if (grav)	gemBodyDef.type = b2_dynamicBody;
	else        gemBodyDef.type = b2_staticBody;

	gemBodyDef.position = vHelper::toB2(sf::Vector2f(50, 50)); //set the starting position
	gemBodyDef.angle = 0; //set the starting angle
	gemBodyDef.fixedRotation = true;

	b2Body* body;
	body = m_world->CreateBody(&gemBodyDef);
	b2PolygonShape shape;

	shape.SetAsBox((m_gem_chart[type].width / vHelper::B2_SCALE) / 2.0f, 
					(m_gem_chart[type].height / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.5f;
	myFixtureDef.isSensor = true;

	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Gem";
	body->CreateFixture(&myFixtureDef);
	return body;
}

void GemMine::DespawnObject() {
	//Loop through all of the Gems
	for (auto it = m_cart.begin(); it != m_cart.end();) {
		//If the Enemy is not alive
		if (!(*it)->e_body_active && (*it)->canDespawn()) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			delete * it;				//delete the pointer
			it = m_cart.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "GemMine", "Gem Removed");
		}
		else ++it;
	}
}

void GemMine::CullInActiveGems() {
	for (auto it = m_cart.begin(); it != m_cart.end();) {
		if (!(*it)->e_body_active && (*it)->canDespawn()) {
			m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
			cLog::inst()->print(0, "GemMine", "Gem Body Destroyed");
		}
		else ++it;
	}
}

void GemMine::update(FTS fts, Player *p) {
	for (Gem* g : m_cart) {
		g->update(fts);
	}

	//CullInActiveGems();
	DespawnObject();
}

void GemMine::render(sf::RenderWindow &w, sf::Time frames){
	//Render Gems
	for (int i = 0; i < m_cart.size(); i++) {
		//m_cart.at(i)->render(w, frames);
		if (m_cart[i]->e_body_active)
			w.draw(*m_cart[i]);
	}
}

void GemMine::clear() {
	for (auto it = m_cart.begin(); it != m_cart.end();) {
		m_world->DestroyBody((*it)->e_box_body);		//Destroy the b2body of the enemy
		delete * it;				//delete the pointer
		it = m_cart.erase(it);	//erase the object(calls the objects destructor)
	}
	cLog::inst()->print(0, "GemMine", "Gems cleared from mine");
}