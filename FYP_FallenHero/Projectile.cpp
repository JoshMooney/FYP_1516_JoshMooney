#include "stdafx.h"
#include "Projectile.hpp"

Projectile::Projectile() {		}

Projectile::Projectile(b2Body* b, sf::Vector2f dir) {
	b->SetUserData(this);
	m_box_body = b;
	
	m_direction = dir;

	init();

	loadMedia();
	alineSprite();
	applySpeed();

	m_current_state = FIRE;
	m_animator.playAnimation(m_current_state);
}

Projectile::Projectile(b2Body* b, sf::Vector2f dir, STATE type) {
	b->SetUserData(this);
	m_box_body = b;

	m_direction = dir;

	init();

	loadMedia();
	alineSprite();
	applySpeed();

	m_current_state = type;
	m_animator.playAnimation(m_current_state);
}

Projectile::~Projectile() {		}

void Projectile::init() {
	m_body_active = true;
	can_despawn = false;
	m_speed = 15.0f;
	m_spawn_point = vHelper::toSF(getBody()->GetPosition());

	
	if (m_direction == sf::Vector2f(1, 0))	setScale(-1, 1);
	if (m_direction == sf::Vector2f(-1, 0)) setScale(1, 1);
	
}

void Projectile::update() {
	if(m_body_active)
		alineSprite();
	checkAnimation();
}

void Projectile::render(sf::RenderWindow & w, sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);
}

void Projectile::loadMedia() {
	s_texture = "Assets/Game/projectile.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(s_texture));
	m_size = sf::Vector2f(16, 16);
	setOrigin(m_size.x / 2, m_size.y / 2);

	addFrames(frame_fire,		2, 0, 1, 16, 16, 1.0f);
	addFrames(frame_fire_bu,	1, 0, 3, 28, 20, 1.0f);
	addFrames(frame_fire_rd,	0, 0, 3, 28, 20, 1.0f);
	addFrames(frame_explode,	3, 0, 5, 28, 29, 1.0f);

	m_animator.addAnimation(FIRE,		frame_fire,		sf::seconds(0.25f));
	m_animator.addAnimation(RED,		frame_fire_rd,	sf::seconds(0.25f));
	m_animator.addAnimation(BLUE,		frame_fire_bu,	sf::seconds(0.25f));
	m_animator.addAnimation(EXPLODE,	frame_explode,	sf::seconds(0.25f));

}

void Projectile::addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
	if (y == 0)
		y = 0;
	else if (y == 1)
		y = 20;
	else if (y == 2)
		y = 40;
	else if (y == 3)
		y = 56;

	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));
}
void Projectile::checkAnimation() {
	if (m_current_state != m_previous_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}
	if (m_current_state == EXPLODE && !m_animator.isPlayingAnimation())
		can_despawn = true;
	if (m_current_state != EXPLODE && !m_body_active) {
		m_current_state = EXPLODE;
	}
	if (m_current_state != EXPLODE && !m_animator.isPlayingAnimation()) {
		m_animator.playAnimation(m_current_state);
	}
}

void Projectile::Die() {
	m_body_active = false;
	getBody()->GetFixtureList()->SetSensor(true);
	setOrigin(28.0f / 2.0f, 28.0f / 2.0f); 
	alineSprite();
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