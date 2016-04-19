#include "stdafx.h"
#include "ProjectileManager.hpp"

ProjectileManager::ProjectileManager() {	}
ProjectileManager::ProjectileManager(b2World * world) {
	m_world = world;
}
ProjectileManager::~ProjectileManager() {	}

b2Body * ProjectileManager::GenerateBody(sf::Vector2f pos) {
	b2BodyDef pro_body_Def;
	pro_body_Def.type = b2_kinematicBody; //this will be a dynamic body

	sf::Vector2f size = sf::Vector2f(32, 32);
	sf::Vector2f pos_off = sf::Vector2f(pos.x - size.x / 2, pos.y - size.y / 2);
	pro_body_Def.position = vHelper::toB2(pos_off);

	//pro_body_Def.position = vHelper::toB2(pos); //set the starting position
	pro_body_Def.angle = 0; //set the starting angle
	pro_body_Def.fixedRotation = true;

	b2Body* body;
	m_world;
	body = m_world->CreateBody(&pro_body_Def);
	b2PolygonShape shape;
	shape.SetAsBox((16 / vHelper::B2_SCALE) / 2.0f, (16 / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.0f;
	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Projectile";

	myFixtureDef.filter.categoryBits = _filterCategory::BULLET;
	myFixtureDef.filter.maskBits = PLAYER | TERRAIN | PLATFORM;

	body->CreateFixture(&myFixtureDef);
	return body;
}

b2Body * ProjectileManager::GenerateBossBody(sf::Vector2f pos) {
	b2BodyDef bull_body_Def;
	bull_body_Def.type = b2_kinematicBody; //this will be a dynamic body
	bull_body_Def.position = vHelper::toB2(pos); //set the starting position
	bull_body_Def.angle = 0; //set the starting angle
	bull_body_Def.fixedRotation = true;

	b2Body* body;
	body = m_world->CreateBody(&bull_body_Def);
	b2PolygonShape shape;
	shape.SetAsBox((16 / vHelper::B2_SCALE) / 2.0f, (16 / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.0f;
	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Projectile";

	myFixtureDef.filter.categoryBits = _filterCategory::BULLET;
	myFixtureDef.filter.maskBits = PLAYER;
	body->CreateFixture(&myFixtureDef);
	return body;
}

void ProjectileManager::fireBullet(sf::Vector2f pos, sf::Vector2f dir) {
	m_projectiles.push_back(new Projectile(GenerateBody(pos), dir));
}
void ProjectileManager::fire(sf::Vector2f pos, sf::Vector2f dir, Projectile::STATE type) {
	m_projectiles.push_back(new Projectile(GenerateBody(pos), dir, type));
}

void ProjectileManager::shootBoss(sf::Vector2f pos, sf::Vector2f dir, string type) {
	if (type == "Directional") {
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(-1, 0), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(0, -1), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(1, 0), Projectile::STATE::BOSS, type));
	}
	if (type == "Directional-More") {
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(-1, 0), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(-0.5f, -0.5f), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(-0.5f, 0.5f), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(0, -1), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(0.5f, 0.5f), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(0.5f, -0.5f), Projectile::STATE::BOSS, type));
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), sf::Vector2f(1, 0), Projectile::STATE::BOSS, type));
	}
	else if (type == "At-Player") {
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), dir, Projectile::STATE::BOSS, type));
	}
	else if (type == "Up") {
		m_projectiles.push_back(new Projectile(GenerateBossBody(pos), dir, Projectile::STATE::BOSS, type));
	}	
}

void ProjectileManager::cull() {
	//Loop through all of the Projectiles
	for (auto it = m_projectiles.begin(); it != m_projectiles.end();) {
		//If the Projectile is not alive
		if (!(*it)->isAlive() && (*it)->canDespawn()) {
			m_world->DestroyBody((*it)->getBody());		//Destroy the b2body of the projectile
			delete * it;				//delete the pointer
			it = m_projectiles.erase(it);	//erase the object(calls the objects destructor)
			cLog::inst()->print(0, "ProjectileManager", "Projectile Deleted");
		}
		else ++it;
	}
}

void ProjectileManager::update(FTS fts) {
	for (Projectile* p : m_projectiles) {
		if (vHelper::distance(p->m_spawn_point, p->getPosition()) > 1000.0f && p->isAlive()) {
			p->Die();
			cLog::inst()->print(0, "ProjectileManager", "Bullet has gone too far and has been destructed.");
		}
		else
			p->update();
	}
}

void ProjectileManager::render(sf::RenderWindow & w, sf::Time frames) {
	for (Projectile* p : m_projectiles) {
		p->render(w, frames);
		w.draw(*p);
	}
}

void ProjectileManager::clear() {
	//Loop through all of the Projectiles
	for (auto it = m_projectiles.begin(); it != m_projectiles.end();) {
		m_world->DestroyBody((*it)->getBody());		//Destroy the b2body of the projectile
		delete * it;								//delete the pointer
		it = m_projectiles.erase(it);				//erase the object(calls the objects destructor)
	}
	cLog::inst()->print(0, "ProjectileManager", "Projectile Manager cleared.");
}
