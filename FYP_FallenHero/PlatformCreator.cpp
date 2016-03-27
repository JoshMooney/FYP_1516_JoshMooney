#include "stdafx.h"
#include "PlatformCreator.hpp"

PlatformCreator::PlatformCreator(b2World * w) {
	m_world = w;
	
}

b2Body * PlatformCreator::generateBody(sf::Vector2f position, string type) {
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

	if(type == "Platform")
		myFixtureDef.userData = "Platform";
	else if(type == "OneWay-Platform")
		myFixtureDef.userData = "OneWay-Platform";

	body->CreateFixture(&myFixtureDef);
	return body;
}

void PlatformCreator::SpawnPlatform(sf::Vector2f pos) {
	m_platforms.push_back(std::make_shared<Platform>(generateBody(pos, "Platform")));
}
void PlatformCreator::SpawnNodePlatform(sf::Vector2f pos, string id_node, bool dir) {
	m_platforms_node.push_back(std::make_shared<NodePlatform>(generateBody(pos, "Platform"), id_node, dir));
	//cLog::inst()->print(0, "PlatformCreator", "Node Platform created.");
}

void PlatformCreator::SpawnOneWay(sf::Vector2f pos) {
	m_platforms.push_back(std::make_shared<OneWayPlatform>(generateBody(pos, "OneWay-Platform")));
}

void PlatformCreator::linkNodes(PointMap * map) {
	m_point_map = map;

	for (int i = 0; i < m_platforms_node.size(); i++) {
		if (m_platforms_node[i]->needsNode()) {
			PointNode* node = m_point_map->get(m_platforms_node[i]->getNodeID()).get();
			if(node != nullptr)
				m_platforms_node[i]->setNode(node);
		}
	}
}

void PlatformCreator::update(FTS fts) {
	for (int i = 0; i < m_platforms.size(); i++) 
		m_platforms[i]->update(fts);

	for (int i = 0; i < m_platforms_node.size(); i++) {
		m_platforms_node[i]->update(fts);
		if (m_platforms_node[i]->needsNode())
			m_platforms_node[i]->setNode(m_point_map->get(m_platforms_node[i]->getNodeID()).get());
	}
}

void PlatformCreator::render(sf::RenderWindow & w, sf::Time frames) {
	for (int i = 0; i < m_platforms.size(); i++)
		m_platforms[i]->render(w, frames);
	for (int i = 0; i < m_platforms_node.size(); i++)
		m_platforms_node[i]->render(w, frames);
}

void PlatformCreator::clear() {
	for (int i = 0; i < m_platforms.size(); i++)
		m_world->DestroyBody(m_platforms[i]->getBody());
	m_platforms.clear();
}
