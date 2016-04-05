#include "stdafx.h"
#include "PlatformCreator.hpp"

PlatformCreator::PlatformCreator(b2World * w) {
	m_world = w;
	
}

b2Body * PlatformCreator::generateBody(sf::Vector2f position, string type) {
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_kinematicBody;
	sf::Vector2f size = sf::Vector2f(160, 16);
	sf::Vector2f pos_off = sf::Vector2f(position.x + size.x/2, position.y + size.y / 2);
	myBodyDef.position = vHelper::toB2(pos_off); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	myBodyDef.fixedRotation = true;

	b2Body* body = m_world->CreateBody(&myBodyDef);

	//Define the shape of the body
	b2PolygonShape shape;
	//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
	shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 900.0f;
	myFixtureDef.shape = &shape;

	if(type == "Platform")
		myFixtureDef.userData = "Platform";
	else if (type == "Fade-Platform")
		myFixtureDef.userData = "Fade-Platform";
	else if(type == "OneWay-Platform")
		myFixtureDef.userData = "OneWay-Platform";

	myFixtureDef.filter.categoryBits = _filterCategory::PLATFORM;
	myFixtureDef.filter.maskBits = PLAYER | ENEMY | BULLET | TERRAIN | PLATFORM | GEM;

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
void PlatformCreator::SpawnXY(sf::Vector2f pos) {
	b2BodyDef xyDef;
	xyDef.type = b2_kinematicBody;
	sf::Vector2f size = sf::Vector2f(32, 32);
	sf::Vector2f pos_off = sf::Vector2f(pos.x + size.x / 2, pos.y + size.y / 2);
	xyDef.position = vHelper::toB2(pos_off); //set the starting position
	xyDef.angle = 0; //set the starting angle
	xyDef.fixedRotation = true;

	b2Body* body = m_world->CreateBody(&xyDef);

	//Define the shape of the body
	b2PolygonShape xy_shape;
	//shape.SetAsBox(m_text_size.x / 32.0f, m_text_size.y / 32.0f);
	xy_shape.SetAsBox((size.x / vHelper::B2_SCALE) / 2.0f, (size.y / vHelper::B2_SCALE) / 2.0f);

	b2FixtureDef xyFix;
	xyFix.density = 1.0f;
	xyFix.friction = 900.0f;
	xyFix.shape = &xy_shape;
	xyFix.userData = "XY-Platform";

	xyFix.filter.categoryBits = _filterCategory::PLATFORM;
	xyFix.filter.maskBits = PLAYER | ENEMY | BULLET | TERRAIN | GEM;

	body->CreateFixture(&xyFix);
	
	//m_platforms.push_back(std::make_shared<XYPlatform>(body));
	m_platforms.push_back(std::make_shared<XYPlatform>(body, vHelper::toSF(body->GetPosition()), xyDef, xy_shape, xyFix));
}
void PlatformCreator::SpawnOneWay(sf::Vector2f pos) {
	m_platforms.push_back(std::make_shared<OneWayPlatform>(generateBody(pos, "OneWay-Platform")));
}
void PlatformCreator::SpawnFade(sf::Vector2f pos) {
	m_platforms.push_back(std::make_shared<FadePlatform>(generateBody(pos, "Fade-Platform")));
}
void PlatformCreator::SpawnFade(sf::Vector2f pos, sf::Vector2f fade) {
	m_platforms.push_back(std::make_shared<FadePlatform>(generateBody(pos, "Fade-Platform"), fade.x, fade.y));
}
void PlatformCreator::SpawnFade(sf::Vector2f pos, sf::Vector2f fade, sf::Vector2f timing) {
	m_platforms.push_back(std::make_shared<FadePlatform>(generateBody(pos, "Fade-Platform"), fade.x, fade.y, timing.x, timing.y));
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
		m_platforms[i]->destroyBody();
	m_platforms.clear();
}
