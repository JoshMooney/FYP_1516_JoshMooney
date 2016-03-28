#include "stdafx.h"
#include "ProjectileManager.hpp"

ProjectileManager::ProjectileManager() {	}
ProjectileManager::ProjectileManager(b2World * world) : m_world(world) {

}
ProjectileManager::~ProjectileManager() {	}

b2Body * ProjectileManager::GenerateBody(sf::Vector2f pos) {
	b2BodyDef pro_body_Def;
	pro_body_Def.type = b2_kinematicBody; //this will be a dynamic body
	pro_body_Def.position = vHelper::toB2(pos); //set the starting position
	pro_body_Def.angle = 0; //set the starting angle
	pro_body_Def.fixedRotation = true;

	b2Body* body = m_world->CreateBody(&pro_body_Def);
	b2PolygonShape shape;
	shape.SetAsBox((16 / vHelper::B2_SCALE) / 2.0f, (16 / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.0f;
	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Projectile";

	body->CreateFixture(&myFixtureDef);
	return body;
}

void ProjectileManager::spawnBullet(sf::Vector2f pos, sf::Vector2f dir) {
	m_projectiles.push_back(new Projectile(GenerateBody(pos), dir));
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
		if (vHelper::distance(p->m_spawn_point, p->getPosition()) > 5000.0f) {
			p->Die();
			cLog::inst()->print(0, "ProjectileManager", "Bullet has gone too far and has been destructed.");
		}
		else
			p->update();
	}
}

void ProjectileManager::render(sf::RenderWindow & w, sf::Time frames) {
	for (Projectile* p : m_projectiles) 
		p->render(w, frames);
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
