#include "stdafx.h"
#include "DarkDemon.hpp"

DarkDemon::DarkDemon() {

}
DarkDemon::DarkDemon(b2Body * b, ProjectileManager* pm, bool dir) : m_projectile_mgr(pm) {
	b->SetUserData(this);
	e_box_body = b;

	m_current_state = IDLE;
	m_previous_state = m_current_state;

	loadMedia();
	alineSprite();

	e_body_active = true;
	e_sword_col = false;
	e_can_despawn = false;
	setDirection(dir);
	e_direction = dir;

	m_speed = 0.35f;
	speedFactor = 0;
	e_hp = 100;
}
DarkDemon::~DarkDemon() {

}

void DarkDemon::ChangeState(STATE s) {
	
}
void DarkDemon::loadMedia() {
	e_texture = "Assets/Game/boss_temp.png";
	setTexture(ResourceManager<sf::Texture>::instance()->get(e_texture));
	m_text_size = sf::Vector2u(35, 44);
	setOrigin(m_text_size.x / 2, m_text_size.y / 2);
	/*
	addFrames(frame_death, 0, 0, 7, 38, 47, 1.0f);
	addFrames(frame_idle, 1, 0, 4, m_text_size.x, m_text_size.y, 1.0f);
	addFrames(frame_walk, 2, 0, 4, m_text_size.x, m_text_size.y, 1.0f);
	addFrames(frame_attack, 3, 0, 4, 29, m_text_size.y, 1.0f);

	m_animator.addAnimation(DEATH, frame_death, sf::seconds(0.5f));
	m_animator.addAnimation(IDLE, frame_idle, sf::seconds(0.5f));
	m_animator.addAnimation(WALKING, frame_walk, sf::seconds(0.5f));
	m_animator.addAnimation(ATTACKING, frame_attack, sf::seconds(0.15f));*/

	/*
	s_death = "Assets/Audio/Game/skeleton_kill.wav";
	m_death.setBuffer(ResourceManager<sf::SoundBuffer>::instance()->get(s_death));*/
}
void DarkDemon::checkAnimation() {
	/*if (m_previous_state != m_current_state) {
		m_previous_state = m_current_state;
		m_animator.playAnimation(m_current_state);
	}

	if (m_current_state == IDLE && !m_animator.isPlayingAnimation())
		m_animator.playAnimation(IDLE);*/
}
void DarkDemon::addFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, int xSep, int ySep, float duration) {
	if (y == 0)
		y = 0;
	else if (y == 1)
		y = 47;
	else if (y == 2)
		y = 91;
	else if (y == 3)
		y = 135;

	for (int x = xFirst; x != xLast; x += 1)
		animation.addFrame(duration, sf::IntRect(xSep * x, y, xSep, ySep));
}

void DarkDemon::update(FTS fts, Player * p) {
	checkAnimation();
	alineSprite();

}
void DarkDemon::render(sf::RenderWindow & w, sf::Time frames) {
	/*m_animator.update(frames);
	m_animator.animate(*this);*/
}

void DarkDemon::TakeDamage() {
	if (!is_hit) {
		is_hit = true;
		e_hp -= 10;
		if (e_hp <= 0)
			Die();
	}
}
void DarkDemon::Die() {
	e_box_body->GetFixtureList()->SetSensor(true);
	e_body_active = false;
}
void DarkDemon::move() {

}
void DarkDemon::attack() {

}
void DarkDemon::alineSprite() {
	setPosition(vHelper::toSF(e_box_body->GetPosition()));
}
void DarkDemon::ChangeDirection() {
	e_direction = !e_direction;
	if (e_direction)	setScale(1, 1);
	else setScale(-1, 1);
}
void DarkDemon::setDirection(bool dir) {
	e_direction = dir;
	if (e_direction)	setScale(1, 1);
	else setScale(-1, 1);
}
void DarkDemon::ReachedWall() {

}
void DarkDemon::ReachPlayer() {

}
