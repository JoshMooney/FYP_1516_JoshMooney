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
	m_shoot_dis = 600;

	can_fire = true;
	cooldown_time = 2.0f;
	m_fire_clock.restart();
}

void Weed::loadMedia() {
	e_texture = "Assets/Game/weed.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_text_size = sf::Vector2u(39, 37);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);
	//setColor(sf::Color::Green);
	
	addFrames(frame_idle,	0, 0, 4, 39, 37, 1.0f);
	addFrames(frame_death,	4, 0, 8, 42, 42, 1.0f);

	/*addFrames(frame_attack, 1, 0, 5, 40, 40, 1.0f);
	addFrames(frame_jump, 2, 0, 5, 40, 46, 1.0f);
	addFrames(frame_land,	3, 0, 4, 40, 46, 1.0f);
	addFrames(frame_death,	4, 0, 8, 42, 42, 1.0f);
	*/
	m_animator.addAnimation(IDLE,	frame_idle,		sf::seconds(0.4f));

	m_animator.addAnimation(DEATH,  frame_death,	sf::seconds(0.75f));
	
	/*m_animator.addAnimation(ATTACK, frame_attack,	sf::seconds(0.2f));
	m_animator.addAnimation(JUMP,	frame_jump,		sf::seconds(0.6f));
	m_animator.addAnimation(LAND,	frame_land,		sf::seconds(0.2f));
	m_animator.addAnimation(DEATH,	frame_death,	sf::seconds(0.5f));
	*/

	//s_death = "Assets/Audio/Game/skeleton_kill.wav";
	//m_death.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_death));

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
	m_previous_state = m_current_state;
}

void Weed::update(FTS fts, Player *p) {
	if(!e_can_despawn)
		checkAnimation();

	if (e_body_active) {
		alineSprite();
		if (vHelper::distance(getPosition(), p->getPosition()) < m_shoot_dis)
			attack();
	}
	else {
		if (!m_animator.isPlayingAnimation() /*&& m_death.getStatus() != sf::Sound::Playing*/)
			e_can_despawn = true;
	}
}

void Weed::render(sf::RenderWindow & w, sf::Time frames) {
	m_animator.update(frames);
	m_animator.animate(*this);
}

void Weed::TakeDamage() {
	if (e_body_active) {
		e_hp -= 10;
		if (e_hp <= 0)
			Die();
	}
}

void Weed::Die() {
	//m_death.play();
	e_box_body->GetFixtureList()->SetSensor(true);
	e_body_active = false;
	e_can_despawn = false;
	m_current_state = DEATH;
}

void Weed::checkAnimation() {
	if (m_previous_state != m_current_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}

	if (m_current_state == IDLE && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(IDLE);

}

void Weed::addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
	if (y == 0)
		y = 0;
	else if (y == 1)
		y = 39;
	else if (y == 2)
		y = 89;
	else if (y == 3)
		y = 129;
	else if (y == 4)
		y = 169;
	
	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));
}

void Weed::attack() {
	sf::Time elapsed = m_fire_clock.getElapsedTime();
	if(elapsed.asSeconds() > cooldown_time) {
		sf::Vector2f dir;
		if (e_direction)
			dir = sf::Vector2f(1, 0);
		else
			dir = sf::Vector2f(-1, 0);

		m_fire_clock.restart();
		//ProjectileHandler.SpawnBullet(getPosition(), dir);
	}
}

void Weed::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}



