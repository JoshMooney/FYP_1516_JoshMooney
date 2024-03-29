#include "stdafx.h"
#include "Weed.hpp"

Weed::Weed() {

}
Weed::Weed(b2Body *b, bool dir, ProjectileManager *gun) {
	m_ai = GREEN;
	m_gun = gun;
	e_direction = dir;
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	init();	
	alineSprite();
	m_shoot_dis = 600;

	can_fire = true;
	m_can_be_hurt = true;
	cooldown_time = 2.0f;
	m_fire_clock.restart();
}
Weed::Weed(b2Body * b, bool dir, ProjectileManager * g, AI type) {
	m_ai = type;
	m_gun = g;
	e_direction = dir;
	b->SetUserData(this);
	e_box_body = b;
	e_body_active = true;
	init();
	alineSprite();
	
	switch (m_ai) {
	case GREEN:
		setColor(sf::Color::Green);
		e_hp = 10;
		cooldown_time = 2.5f;
		m_shoot_dis = 500;
		break;
	case RED:
		setColor(sf::Color::Red);
		e_hp = 20;
		cooldown_time = 1.5f;
		m_shoot_dis = 450;
		break;
	case BLUE:
		setColor(sf::Color::Blue);
		cooldown_time = 0.9f;
		e_hp = 10;
		m_shoot_dis = 350;
		break;
	}

	can_fire = true;
	m_can_be_hurt = true;
	m_fire_clock.restart();
}

void Weed::loadMedia() {
	e_texture = "Assets/Game/weed.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_text_size = sf::Vector2u(39, 37);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);
	
	addFrames(frame_idle,	0, 0, 4, 39, 37, 1.0f);
	addFrames(frame_death,	4, 0, 8, 42, 42, 1.0f);
	addFrames(frame_attack, 1, 0, 5, 40, 40, 1.0f);
	/*addFrames(frame_attack, 1, 0, 5, 40, 40, 1.0f);
	addFrames(frame_jump, 2, 0, 5, 40, 46, 1.0f);
	addFrames(frame_land,	3, 0, 4, 40, 46, 1.0f);
	addFrames(frame_death,	4, 0, 8, 42, 42, 1.0f);
	*/
	m_animator.addAnimation(IDLE,	frame_idle,		sf::seconds(0.4f));
	m_animator.addAnimation(ATTACK, frame_attack,	sf::seconds(0.32f));
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
	//m_jump = 5.0f;
	e_body_active = true;
	e_can_despawn = false;
	e_sword_col = false;
	e_can_despawn = false;

	loadMedia();
	e_hp = 10;
	m_current_state = IDLE;
	m_previous_state = m_current_state;
	m_fire_clock.restart();
	cooldown_time = 3;
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
	if (e_body_active && !is_hit && m_can_be_hurt) {
		is_hit = true;
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

	if (!m_animator.isPlayingAnimation()) {
		if (m_current_state == IDLE)
			m_animator.playAnimation(IDLE);
		else if (m_current_state == ATTACK) {
			m_current_state = IDLE;
			m_can_be_hurt = true;
		}
	}

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
	if (elapsed.asSeconds() > cooldown_time) {
		sf::Vector2f dir;
		if (e_direction)
			dir = sf::Vector2f(1, 0);
		else
			dir = sf::Vector2f(-1, 0);

		m_can_be_hurt = false;
		m_current_state = ATTACK;
		m_fire_clock.restart();
		//m_fire.play();
		switch (m_ai) {
		case GREEN:
			m_gun->fire(getPosition(), dir, Projectile::WEED_L1);
			break;
		case RED:
			m_gun->fire(getPosition(), dir, Projectile::WEED_L2);
			break;
		case BLUE:
			m_gun->fire(getPosition(), dir, Projectile::WEED_L3);
			break;
		}
	}
}
void Weed::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}



