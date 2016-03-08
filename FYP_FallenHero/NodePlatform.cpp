#include "stdafx.h"
#include "NodePlatform.hpp"

NodePlatform::NodePlatform(b2Body * b, PointNode* n, bool d) : m_box_body(b), m_direction(d), m_nextNode(n) {
	m_body_active = true;
	s_texture = "Assets/Game/plat.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	m_size = sf::Vector2u(96, 32);
	setOrigin(m_size.x, m_size.y);
	m_is_moving = true;
	m_speed = 2;
}

NodePlatform::~NodePlatform() {

}

void NodePlatform::update(FTS fts) {
	if (m_is_moving) {
		if (vHelper::distance(getPosition(), m_nextNode->position()) < 5) {
			//Set the m_nextNode to the next node in the list
			//m_nextNode->getNext();
		}
		else {
			m_box_body->SetLinearVelocity(vHelper::toB2(calculateVelocity() * m_speed));
		}
	}
}

void NodePlatform::render(sf::RenderWindow & w, sf::Time frames) {

}

sf::Vector2f& NodePlatform::calculateVelocity() {
	sf::Vector2f position = vHelper::toSF(m_box_body->GetPosition());

	sf::Vector2f dir = sf::Vector2f(m_nextNode->position().x - position.x, m_nextNode->position().y - position.y);

	//Normalise direction Vector
	float mag = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (mag > 0)	dir = sf::Vector2f(dir.x / mag, dir.y / mag);
	else			dir = sf::Vector2f(0, 0);

	return dir;
}

void NodePlatform::alineSprite() {
	setPosition(vHelper::toSF(m_box_body->GetPosition()));
}
