#include "stdafx.h"
#include "Projectile.hpp"

Projectile::Projectile() {		}

Projectile::Projectile(b2Body* b, sf::Vector2f dir) {
	b->SetUserData(this);
	m_box_body = b;
	m_body_active = true;
	can_despawn = false;
	m_direction = dir;

	m_speed = 15.0f;

	loadMedia();
	alineSprite();
	applySpeed();

	m_spawn_point = vHelper::toSF(getBody()->GetPosition());
}

Projectile::~Projectile() {		}

void Projectile::update() {
	alineSprite();
	if (m_body_active && !can_despawn)
		can_despawn = true;
}

void Projectile::render(sf::RenderWindow & w, sf::Time frames) {
	w.draw(*this);
}

void Projectile::loadMedia() {
	s_texture = "Assets/Game/projectile.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	m_size = sf::Vector2f(16, 16);
	setOrigin(m_size.x / 2, m_size.y / 2);
}

void Projectile::Die() {
	m_body_active = false;

}

void Projectile::alineSprite() {
	setPosition(vHelper::toSF(m_box_body->GetPosition()));
}

void Projectile::applySpeed() {
	sf::Vector2f force = m_direction * m_speed;
	m_box_body->SetLinearVelocity(vHelper::toB2(force));
}

bool Projectile::getBoolDirection() {
	if (m_direction == sf::Vector2f(1, 0))
		return true;
	if (m_direction == sf::Vector2f(-1, 0))
		return false;
	if (m_direction == sf::Vector2f(0, 1))
		return true;
	if (m_direction == sf::Vector2f(0, -1))
		return false;
}