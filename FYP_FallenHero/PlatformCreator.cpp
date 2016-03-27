#include "stdafx.h"
#include "PlatformCreator.hpp"

PlatformCreator::PlatformCreator(b2World * w) {
	m_world = w;
	
}

b2Body * PlatformCreator::generateBody(sf::Vector2f position) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_kinematicBody;
	myBodyDef.position = vHelper::toB2(position); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.fixedRotation = true;

	b2Body* body = m_world->CreateBody(&myBodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
	shape.SetAsBox((160 / vHelper::B2_SCALE) / 2.0f, (16 / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 1.5f;
	myFixtureDef.shape = &shape;
	myFixtureDef.userData = "Platform";

	body->CreateFixture(&myFixtureDef);
	return body;
}
void PlatformCreator::SpawnPlatform(sf::Vector2f pos) {
	m_platforms.push_back(std::make_shared<Platform>(generateBody(pos)));
}
void PlatformCreator::SpawnNodePlatform(sf::Vector2f pos, std::pair<string, string> nodes, bool dir) {
	//m_platforms_node.push_back(std::make_shared<NodePlatform>(generateBody(), nodes, dir));
}

void PlatformCreator::linkNodes(PointMap * map) {

}

void PlatformCreator::update(FTS fts) {
	for (int i = 0; i < m_platforms.size(); i++)
		m_platforms[i]->update(fts);
}

void PlatformCreator::render(sf::RenderWindow & w, sf::Time frames) {
	for (int i = 0; i < m_platforms.size(); i++)
		m_platforms[i]->render(w, frames);
}

void PlatformCreator::clear() {
	for (int i = 0; i < m_platforms.size(); i++)
		m_world->DestroyBody(m_platforms[i]->getBody());
	m_platforms.clear();
}
