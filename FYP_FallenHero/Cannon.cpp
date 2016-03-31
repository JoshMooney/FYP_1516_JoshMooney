#include "stdafx.h"
#include "Cannon.hpp"

Cannon::Cannon() {	}

Cannon::Cannon(b2Body * b, bool dir, ProjectileManager* p) {
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	m_level = Projectile::FIRE;

	e_direction = dir;
	e_sword_col = false;
	e_can_despawn = false;

	loadMedia();
	alineSprite();

	e_hp = 0;
	m_fire_clock.restart();
	cooldown_time = 3;
	m_gun = p;
}

Cannon::Cannon(b2Body* b, bool dir, ProjectileManager* p, Projectile::STATE type) {
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	m_level = type;

	e_direction = dir;
	e_sword_col = false;
	e_can_despawn = false;

	loadMedia();
	alineSprite();

	e_hp = 0;
	m_fire_clock.restart();
	cooldown_time = 3;
	m_gun = p;
}


Cannon::~Cannon()	{	
	cLog::inst()->print(0, "Cannon", "Cannon deconstructor called.");
}

void Cannon::update(FTS fts, Player * p) {
	attack();
	alineSprite();
}

void Cannon::render(sf::RenderWindow & w, sf::Time frames) {

}

void Cannon::loadMedia() {
	e_texture = "Assets/Game/cannon.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_size = sf::Vector2u(32, 32);
	setOrigin(m_size.x / 2, m_size.y / 2);

	s_fire = "Assets/Audio/Cannon/cannon_fire.wav";
	m_fire.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_fire));
	s_hit = "Assets/Audio/Cannon/cannon_tud.wav";
	m_hit.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_hit));
}

sf::FloatRect Cannon::getBounds() {
	sf::Vector2f position(getPosition().x - (m_size.x / 2), getPosition().y - (m_size.y / 2));
	return sf::FloatRect{ position.x, position.y, (float)m_size.x, (float)m_size.y };
}

void Cannon::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}

void Cannon::TakeDamage() {
	//Do nothing here but maybe play a noise so you can still hit 
	//Cannons but not actually do anything to it.

	if (!is_hit) {
		m_hit.play();
		is_hit = true;
	}
}

void Cannon::Die() {
	//Do nothing here this should never be called.
}

void Cannon::attack() {
	sf::Time elapsed = m_fire_clock.getElapsedTime();
	if (elapsed.asSeconds() > cooldown_time) {
		sf::Vector2f dir;
		if (e_direction)
			dir = sf::Vector2f(1, 0);
		else
			dir = sf::Vector2f(-1, 0);

		m_fire_clock.restart();
		m_fire.play();
		//m_gun->fireBullet(getPosition(), dir);
		m_gun->fire(getPosition(), dir, m_level);
	}
}
