#include "stdafx.h"
#include "Weed.hpp"

Weed::Weed() {

}
Weed::Weed(b2Body *b, sf::Vector2f pos, bool dir) {
	e_direction = dir;
	b->SetUserData(this);
	b->SetTransform(vHelper::toB2(pos), 0.0f);
	e_box_body = b;
	init();	
	alineSprite();
}
Weed::~Weed() {

}

void Weed::loadMedia() {
	e_texture = "Assets/Game/weed.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_text_size = sf::Vector2u(39, 37);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);
	setColor(sf::Color::Green);

	s_death = "Assets/Audio/Game/skeleton_kill.wav";
	m_death.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_death));

	if (e_direction)	setScale(-1, 1);
	else                setScale(1, 1);
}

void Weed::init() {
	e_sword_col = false;
	m_jump = 5.0f;
	e_body_active = true;
	e_can_despawn = false;

	loadMedia();
	e_hp = 10;
	m_current_state = IDLE;

}

void Weed::update(FTS fts) {
	checkAnimation();
	alineSprite();
	if (e_body_active) {

	}
	else {
		if (!m_animator.isPlayingAnimation())
			e_can_despawn = true;
	}
}

void Weed::render(sf::RenderWindow & w, sf::Time frames) {
	//m_animator.update(frames);
	//m_animator.animate(*this);
}

void Weed::TakeDamage() {
	e_hp -= 10;
	if (e_hp <= 0)
		Die();
}

void Weed::Die() {
	m_death.play();
	e_box_body->GetFixtureList()->SetSensor(true);
	e_body_active = false;
	e_can_despawn = true;
	//m_current_state = DEATH;
}

void Weed::checkAnimation() {
	/*if (m_previous_state != m_current_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}
	if (m_current_state == WALKING && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(WALKING);
	if (m_current_state == IDLE && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(IDLE);
	if (m_current_state == ATTACKING && !m_animator.isPlayingAnimation()) {
		m_current_state = WALKING;
		ChangeDirection();
		move();
	}*/
}

void Weed::addFrames(thor::FrameAnimation & animation, int x, int yFirst, int yLast, int xSep, int ySep, float duration) {
	/*if (y == 0)
		y = 0;
	else if (y == 1)
		y = 47;
	else if (y == 2)
		y = 91;
	else if (y == 3)
		y = 135;

	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));*/
}

void Weed::attack() {

}

void Weed::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}



