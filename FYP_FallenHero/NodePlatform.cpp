#include "stdafx.h"
#include "NodePlatform.hpp"

NodePlatform::NodePlatform(b2Body * b, string id, bool d) : m_direction(d) {
	m_node_id = id;
	m_box_body = b;
	m_box_body->SetUserData(this);
	m_body_active = true;

	loadMedia();

	//alineSprite();
	m_is_moving = true;
	m_speed = 8.0f;
	if(id != "")
		m_new_node = true;
}

NodePlatform::~NodePlatform() {

}

void NodePlatform::update(FTS fts) {
	if (m_is_moving && m_nextNode != nullptr) {
		if (vHelper::distance(getPosition(), m_nextNode->position()) < 4) {
			m_node_id = m_nextNode->getNext();
			m_new_node = true;
		}
		else {
			sf::Vector2f vel = calculateVelocity();
			sf::Vector2f direction = vel * m_speed;
			m_box_body->SetLinearVelocity(vHelper::toB2(direction));
		}
	}

	alineSprite();
}

void NodePlatform::loadMedia() {
	s_texture = "Assets/Game/node_platform.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	m_size = sf::Vector2u(160, 16);
	sf::Texture l_texture = ResourceManager<sf::Texture>::instance()->get(s_texture);
	setOrigin(m_size.x / 2, m_size.y / 2);

	int ySep = 16;
	for (int i = 0; i < 4; i++)
		frame_hover.addFrame(0.25f, sf::IntRect(0, ySep * i, 160, 16));

	m_animator.addAnimation("Hover", frame_hover, sf::seconds(0.15f));
	m_animator.playAnimation("Hover", true);
}

void NodePlatform::render(sf::RenderWindow & w, sf::Time frames) {
	w.draw(*this);

	m_animator.update(frames);
	m_animator.animate(*this);
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
